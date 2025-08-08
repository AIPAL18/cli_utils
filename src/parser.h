#ifndef CLI_UTILS_PARSER
#define CLI_UTILS_PARSER

#include <ctype.h>
#include <string.h>

#include "globals.h"
#include "display/color.h"

typedef struct
{
    char **content;
    size_t row;
    size_t rowc;  // row count
} CharGrouper;

bool eol(char* text, size_t i)
{
    return i > strlen(text); // i == strlen(text) + 1 <=> text[i] == '\0'
}

bool eof(CharGrouper* cg)
{
    return cg->row == cg->rowc - 1;
}

bool is_valid_identifer(const char* text)
{
    if (!(isalpha(text[0]) || text[0] == '_')) return false;
    for (int i = 0; text[i] != '\0'; ++i)
    {
        if (!(isalnum(text[i]) || text[i] == '_' || text[i] == '-')) return false;
    }
    return true;
}

Flag* get_flag(App_t* app, const char sym)
{
    Flag_ll* current = app->flag_head;
    while (current != end_node && current->val->symbol != sym)
    {
        current = current->next;
    }
    if (current == end_node) return NULL;
    return current->val;
}

KWArg* get_kwarg_from_symbol(App_t* app, const char sym)
{
    KWArg_ll* current = app->kwarg_head;
    while (current != end_node && current->val->symbol != sym)
    {
        current = current->next;
    }
    if (current == end_node)
    {
        current = app->rkwarg_head;
        while (current != end_node && current->val->symbol != sym)
        {
            current = current->next;
        }
        if (current == end_node) return NULL;
    }
    return current->val;
}

KWArg* get_kwarg_from_name(App_t* app, const char* text)
{
    KWArg_ll* current = app->kwarg_head;
    while (current != end_node && strcmp(current->val->name, text))
    {
        current = current->next;
    }
    if (current == end_node) {
        current = app->rkwarg_head;
        while (current != end_node && strcmp(current->val->name, text))
        {
            current = current->next;
        }
        if (current == end_node) return NULL;
    }
    return current->val;
}

bool token_text_equal(const char* a, const char* b)
{
    return strcmp(a, b) == 0;
}

bool is_value_next(CharGrouper* cg)
{
    if (eof(cg)) return false;
    return cg->content[cg->row + 1][0] != '-';
}

void parse(App_t* app, const int argc, char** argv) // FIXME: make it non destructive for LLs (using the same principle as display) => remove all pop functions
{
    // init

    ParsedArgs pa = {
        .argc = argc,
        .argv = argv,
        .flag_head = Flag_ll_new(),
        .kwarg_head = KWArg_ll_new(),
        .arg_head = Arg_ll_new(),
    };

    if (app->_arg_nb == 0) 
    {
        app->prcs(&pa);
        return;
    }

    // basics (help, version)

    // TODO: basics
    
    // gather every arg required

    Arg_ll* next_pos_arg = app->arg_head;
    KWArg_ll* rkwargs = KWArg_ll_copy(app->rkwarg_head);

    // character grouper / lexer

    CharGrouper cg = {
        .content = &argv[1],
        .row = 0,
        .rowc = argc -1, // argv[0] -> path
    };

    char* arg;
    bool error = false;
    for (int i = 1; i < argc; ++i, ++cg.row)
    {
        arg = argv[i];
        if (arg[0] == '-') { // flag or kwarg
            // TODO: for the parser check if its a kwarg or a flag or unknown, if it's a kwarg, THEN you expect a value
            // kwarg
            if (!eol(arg, 2) && arg[1] == '-') { // !eol(arg, 2) <=> has at least 2 chars ('-' + any char)
                KWArg* a;
                if (!(
                        is_valid_identifer(&arg[2])
                        && (a = get_kwarg_from_name(app, &arg[2]))
                )) {
                    error = true;
                    printf(MAGENTA("Unknown argument: ") "%s\n\n", &arg[2]);
                    continue;
                }
                if (!is_value_next(&cg))
                {
                    error = true;
                    printf(MAGENTA("%s expects a value\n\n"), a->name);
                    break;
                }
                a->value = argv[++i];
                ++cg.row;
                KWArg_ll_push(&pa.kwarg_head, a);
            }
            // flag or kwarg's symbol
            else if (!eol(arg, 1) && strlen(&arg[1]) == 1) { // !eol(arg, 1) <=> has at least 1 chars
                if(is_value_next(&cg)) // (kwarg) or (flag + arg)
                {
                    KWArg* a;
                    if (
                        isalpha(arg[1])
                        && (a = get_kwarg_from_symbol(app, arg[1]))
                    ) {
                        a->value = argv[++i];
                        ++cg.row;
                        KWArg_ll_push(&pa.kwarg_head, a);
                        KWArg_ll_pop_by_value(&rkwargs, a);
                        continue; // it's not a flag
                    }
                }
                // flag
                Flag* f;
                if (!(
                    isalpha(arg[1])
                    && (f = get_flag(app, arg[1]))
                )) {
                    error = true;
                    printf(MAGENTA("Unknown flag: ") "%c\n\n", arg[1]);
                    continue;
                }
                else {
                    Flag_ll_push(&pa.flag_head, f);
                    continue;
                }
            }
            else if (!eol(arg, 1)) {  // single dash and multiple chars
                error = true;
                printf(MAGENTA("Unknown argument:") "%s\n", &arg[2]);
                printf(CYAN("Hint: ") "try -%s\n\n", arg);
                continue;
            }
            else { // empty
                printf(YELLOW("Warning: ") "empty argument\n\n");
                continue;
            }
        }
        else { // positionnal argument
            if (Arg_ll_empty(&next_pos_arg))
            {
                error = true;
                printf(MAGENTA("Too many positionnal arguments: %s\n\n"), arg);
                continue;
            }
            Arg* a = Arg_ll_peek(&next_pos_arg);
            next_pos_arg = next_pos_arg->next;
            a->value = arg;
            Arg_ll_push(&pa.arg_head, a);
        }
    }
    
    // check that every arg required has been provided

    if (!(KWArg_ll_empty(&rkwargs) && Arg_ll_empty(&next_pos_arg)))
    {
        error = true;
        printf(MAGENTA("Argument(s) missing ! ") "Please provide:\n");

        while (!KWArg_ll_empty(&rkwargs))
        {
            KWArg* kwarg = KWArg_ll_peek(&rkwargs);
            rkwargs = rkwargs->next;
            printf("  * %s\n", kwarg->name);
        }
        while (!Arg_ll_empty(&next_pos_arg))
        {
            Arg* arg = Arg_ll_peek(&next_pos_arg);
            next_pos_arg = next_pos_arg->next;
            printf("  * %s\n", arg->name);
        }
        printf("\n");
    }

    // launch process if possible
    
    if (error) {
        usage(app);
    }
    else {
        // call process
        app->prcs(&pa);
    }

    // clean variables
    
    // NOTE: Both rkwargs and next_pos_arg should be empty by now
    KWArg_ll_free(rkwargs);
    Arg_ll_free(next_pos_arg);

    KWArg_ll_free(pa.kwarg_head);
    Arg_ll_free(pa.arg_head);
    Flag_ll_free(pa.flag_head);
}

#endif //CLI_UTILS_PARSER