#ifndef CLI_UTILS_GLOBALS
#define CLI_UTILS_GLOBALS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "app.h"

// print usage for app
void usage(App_t* app) // FIXME: make it non destructive for LLs (using the same principle as display) => remove all pop functions
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
    while (!Flag_ll_empty(&app->flag_head)) {
        Flag* flag = Flag_ll_pop(&app->flag_head);
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
    while (!KWArg_ll_empty(&app->kwarg_head)) {
        KWArg* kwarg = KWArg_ll_pop(&app->kwarg_head);
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
    // TODO: new line here
    // Required KWarg
    while (!KWArg_ll_empty(&app->rkwarg_head)) {
        KWArg* kwarg = KWArg_ll_pop(&app->rkwarg_head);
        if (kwarg->symbol) {
            buffer = format(" (-%c --%s `%s`)", kwarg->symbol, kwarg->name, kwarg->value_name);
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
    // TODO: new line here
    // Arg
    while (!Arg_ll_empty(&app->arg_head)) {
        Arg* arg = Arg_ll_pop(&app->arg_head);
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

#endif // CLI_UTILS_GLOBALS