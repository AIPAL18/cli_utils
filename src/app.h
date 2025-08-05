#ifndef CLI_UTILS_APP
#define CLI_UTILS_APP

#include <stdio.h>

#include "linked_list.h"

typedef struct
{
    char* app_name;             //            | name of the app
    char* app_exe;              //            | name of the app's executable
    char* version;              //            | version of the app
    KWArg_ll* kwarg_head;       //            | list of keyword arguments
    Arg_ll* arg_head;           //            | list of arguments
    void (*process)(char*, ...) //            | function that do the work (first argument->argv[0], then TODO: format)
} App_t;

void parse(const App_t* app, const int argc, const char** argv)
{
    (void)app;
    (void)argc;
    (void)argv;
    // app->process(argv[0], ???)  // TODO: format
}

// push arg into app
void push_kwarg(App_t* app, KWArg* arg)
{
    return pushr_kwarg(&app->kwarg_head, arg);
}

//
void push_arg(App_t* app, Arg* arg)
{
    return pushr_arg(&app->arg_head, arg);
}

// print usage for app
void usage(const App_t app)
{
    printf("usage: %s ", app.app_exe);
}

// print help for app
void general_help(const App_t app)
{
    printf("%s (version: %s)\n\n", app.app_name, app.version);

    usage(app);
    printf("\n");
}


// print help for an KWArg
void general_help(const App_t app)
{
    printf("%s (version: %s)\n\n", app.app_name, app.version);

    usage(app);
    printf("\n");
}

#endif // CLI_UTILS_APP