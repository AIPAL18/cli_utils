#ifndef CLI_UTILS_APP
#define CLI_UTILS_APP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "pprint.h"

typedef struct
{
    char* name;                 //            | name of the app
    char* exe_name;             //            | name of the app's executable
    char* version;              //            | version of the app
    Flag_ll* flag_head;         //            | list of flags
    KWArg_ll* kwarg_head;       //            | list of keyword arguments
    Arg_ll* arg_head;           //            | list of arguments
    int _arg_nb;                //            | minimal number of arg required (updates itself)
    // void (*process)(char*, ...);//            | function that do the work (first argument->argv[0], then TODO: format)
} App_t;

App_t* new_app(
    char* _name,
    char* _exe_name,
    char* _version
    )
{
    App_t* app = malloc(sizeof(App_t));
    app->name = _name;
    app->exe_name = _exe_name;
    app->version = _version;
    app->flag_head = malloc(sizeof(Flag_ll));
    app->flag_head = NULL;
    app->kwarg_head = default_head;
    app->arg_head = default_head;
    
    return app;
}

// push flag into app
void push_flag(App_t* app, Flag* arg)
{
    pushr_flag(&app->flag_head, arg);
}
// push keyword arg into app
void push_kwarg(App_t* app, KWArg* arg)
{
    if (arg->required) ++app->_arg_nb;
    pushr_kwarg(&app->kwarg_head, arg);
}
// push arg into app
void push_arg(App_t* app, Arg* arg)
{
    ++app->_arg_nb;
    pushr_arg(&app->arg_head, arg);
}

void add_default_arg(App_t* app)
{
    (void)app;
    /*
    YOU FUKING BASTARD **MUST** MALLOC THE DAMN STRUCT INSTEAD OF HAVING ANONYMUS SHITY THINGS ALL AROUD §§§ LEARN FROM YOU4RE MISTAKES ASSHOLE
    */
    
    // // add help, verbose (accessible by the user), version

    // KWArg* _help = &(KWArg){
    //     .name = "help",
    //     .description = "Print help",
    //     .long_description = "Print help",
    //     .value_name = "argument",
    //     .required = false,
    // };

    // Flag* _h = &(Flag){
    //     .name = "h",
    //     .symbol = '?',
    //     .description = "Print help",
    //     .long_description = "Print help",
    // };
    
    // Flag* _version = &(Flag){
    //     .name = "version",
    //     .symbol = 'v',
    //     .description = "print the version of the app",
    //     .long_description = "print the version of the app",
    // };

    // push_kwarg(app, _help);
    // push_flag(app, _h);
    // push_flag(app, _version);
}

void free_app(App_t* app)
{
    free_list_flag(app->flag_head);
    free_list_kwarg(app->kwarg_head);
    free_list_arg(app->arg_head);
    free(app);
}

// print usage for app
void usage(App_t* app)
{
    char* message = format("usage: %s", app->exe_name);
    
    if (!message) {
        free(message);
        return;
    }

    size_t buffer_size = 32;
    char* buffer;

    size_t options_capacity = buffer_size;
    char* options = (char*)malloc(options_capacity);
    if (!options) {
        free(message);
        return;
    }
    options[0] = '\0';  // initialise la chaîne vide

    // Flags
    while (app->flag_head != NULL) {
        Flag* flag = pop_flag(&app->flag_head);
        if (flag->symbol) {
            buffer = format(" [-%c --%s]", flag->symbol, flag->name);
        }
        else {
            buffer = format(" [--%s]", flag->name);
        }

        // Calcule la nouvelle longueur requise
        size_t new_len = strlen(options) + strlen(buffer) + 1;

        if (new_len > options_capacity) {
            options_capacity = new_len * 2; // double la capacité pour éviter des reallocs fréquents
            char* temp = realloc(options, options_capacity);
            if (!temp) {
                free(message);
                free(options);
                free(buffer);
                return;
            }
            options = temp;
        }
        strcat(options, buffer);
        free(buffer);
    }
    // KWarg
    while (seek_kwarg(&app->kwarg_head)) {
        KWArg* kwarg = pop_kwarg(&app->kwarg_head);
        if (kwarg->symbol) {
            buffer = format(" [-%c --%s `%s`]", kwarg->symbol, kwarg->name, kwarg->value_name);
        }
        else {
            buffer = format(" [--%s `%s`]", kwarg->name, kwarg->value_name);
        }

        // Calcule la nouvelle longueur requise
        size_t new_len = strlen(options) + strlen(buffer) + 1;

        if (new_len > options_capacity) {
            options_capacity = new_len * 2; // double la capacité pour éviter des reallocs fréquents
            char* temp = realloc(options, options_capacity);
            if (!temp) {
                free(message);
                free(options);
                free(buffer);
                return;
            }
            options = temp;
        }
        strcat(options, buffer);
        free(buffer);
    }
    // Arg
    while (seek_arg(&app->arg_head)) {
        Arg* arg = pop_arg(&app->arg_head);
        buffer = format(" %s", arg->name);

        // Calcule la nouvelle longueur requise
        size_t new_len = strlen(options) + strlen(buffer) + 1;

        if (new_len > options_capacity) {
            options_capacity = new_len * 2; // double la capacité pour éviter des reallocs fréquents
            char* temp = realloc(options, options_capacity);
            if (!temp) {
                free(message);
                free(options);
                free(buffer);
                return;
            }
            options = temp;
        }
        strcat(options, buffer);
        free(buffer);
    }

    printf("%s", message);
    pprint_usage(options, 50, strlen(message));
    free(message);
    free(options);
    fflush(stdout);
}

// print help for app
void general_help(App_t* app)
{
    printf("%s (version: %s)\n\n", app->name, app->version);

    usage(app);
    printf("\n");
}


// print help for an KWArg
// void help_kwarg(const App_t app)
// {
//     printf("%s (version: %s)\n\n", app.name, app.version);

//     usage(app);
//     printf("\n");
// }



void parse(App_t* app, const int argc, char** argv)
{
    (void)argv;
    if (argc <= app->_arg_nb)
    {
        printf("Not enough arguments\n\n");
        usage(app);
    }
    
    // app->process(argv[0], ???)  // TODO: format
}

#endif // CLI_UTILS_APP