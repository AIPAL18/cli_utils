#ifndef CLI_UTILS_APP
#define CLI_UTILS_APP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "pprint.h"

typedef struct
{
    char* app_name;             //            | name of the app
    char* app_exe;              //            | name of the app's executable
    char* version;              //            | version of the app
    Flag_ll* flag_head;         //            | list of flags
    KWArg_ll* kwarg_head;       //            | list of keyword arguments
    Arg_ll* arg_head;           //            | list of arguments
    int _arg_nb;                //            | minimal number of arg required (updates itself)
    void (*process)(char*, ...);//            | function that do the work (first argument->argv[0], then TODO: format)
} App_t;

// push flag into app
void push_flag(App_t* app, Flag* arg)
{
    return pushr_flag(&app->flag_head, arg);
}
// push keyword arg into app
void push_kwarg(App_t* app, KWArg* arg)
{
    if (arg->required) ++app->_arg_nb;
    return pushr_kwarg(&app->kwarg_head, arg);
}
// push arg into app
void push_arg(App_t* app, Arg* arg)
{
    ++app->_arg_nb;
    return pushr_arg(&app->arg_head, arg);
}

void add_default_arg(App_t* app)
{
    (void)app;
    // add help, verbose (accessible by the user), version

    KWArg* _help = &(KWArg){
        .name = "help",
        .description = "Print help",
        .long_description = "Print help",
        .value_name = "argument",
        .required = false,
    };

    Flag* _h = &(Flag){
        .name = "h",
        .symbol = '?',
        .description = "Print help",
        .long_description = "Print help",
    };
    
    Flag* _version = &(Flag){
        .name = "version",
        .symbol = 'v',
        .description = "print the version of the app",
        .long_description = "print the version of the app",
    };

    push_kwarg(app, _help);
    push_flag(app, _h);
    push_flag(app, _version);
}

void free_app(App_t app)
{
    free_list_flag(app.flag_head);
    free_list_kwarg(app.kwarg_head);
    free_list_arg(app.arg_head);
}

// print usage for app
void usage(const App_t* app)
{
    char* message = format("usage: %s[.exe]", app->app_exe);
    if (!message) {
        free(message);
        return;
    }
    pprint_wrap(message, 30, '\n');
}

// print help for app
void general_help(const App_t* app)
{
    printf("%s (version: %s)\n\n", app->app_name, app->version);

    usage(app);
    printf("\n");
}


// print help for an KWArg
// void help_kwarg(const App_t app)
// {
//     printf("%s (version: %s)\n\n", app.app_name, app.version);

//     usage(app);
//     printf("\n");
// }



void parse(const App_t* app, const int argc, char** argv)
{
    (void)app;
    (void)argc;
    (void)argv;

    if (argc <= app->_arg_nb)
    {
        printf("Not enough arguments\n\n");
        usage(app);
    }
    
    // app->process(argv[0], ???)  // TODO: format
}

#endif // CLI_UTILS_APP