#ifndef CLI_UTILS_app
#define CLI_UTILS_app

#include <stdio.h>
#include <stdlib.h>

#include "ll/linked_list.h"
#include "display/pprint.h"

typedef struct
{
    int argc;
    char** argv;
    char* exe_path;
    Flag_ll* flag_head;         //            | list of flags
    KWArg_ll* kwarg_head;       //            | list of keyword arguments
    Arg_ll* arg_head;           //            | list of arguments
} ParsedArgs;

typedef struct
{
    char* name;                 //            | name of the app
    char* exe_name;             //            | name of the app's executable
    char* version;              //            | version of the app
    Flag_ll* flag_head;         //            | list of flags
    KWArg_ll* kwarg_head;       //            | list of keyword arguments
    KWArg_ll* rkwarg_head;      //            | list of required keyword arguments
    Arg_ll* arg_head;           //            | list of arguments
    int _arg_nb;                //            | minimal number of arg required (updates itself)
    void (*prcs)(ParsedArgs*);  //            | function that do the work
} App_t;


App_t* new_app(
    char* _name,
    char* _exe_name,
    char* _version,
    void (*process)(ParsedArgs*)
    )
{
    App_t* app = calloc(1, sizeof(App_t));
    app->name = _name;
    app->exe_name = _exe_name;
    app->version = _version;
    app->flag_head = Flag_ll_new();
    app->kwarg_head = KWArg_ll_new();
    app->arg_head = Arg_ll_new();
    app->prcs = process;
    
    return app;
}

// push flag into app
void push_flag(App_t* app, Flag* arg)
{
    // symbol can be already used by a flag
    // symbol can be already used by a kwarg
    // isalpha()
    Flag_ll_push(&app->flag_head, arg);
}
// push keyword arg into app
void push_kwarg(App_t* app, KWArg* arg)
{
    // symbol can be already used by a flag
    // symbol can be already used by a kwarg
    // is_valid_identifer() for its name
    KWArg_ll_push(&app->kwarg_head, arg);
}
// push required keyword arg into app
void push_rkwarg(App_t* app, KWArg* arg)
{
    // symbol can be already used by a flag
    // symbol can be already used by a kwarg
    // is_valid_identifer() for its name
    ++app->_arg_nb;
    KWArg_ll_push(&app->rkwarg_head, arg);
}
// push arg into app
void push_arg(App_t* app, Arg* arg)
{
    ++app->_arg_nb;
    Arg_ll_push(&app->arg_head, arg);
}

void free_app(App_t* app)
{
    Flag_ll_free(app->flag_head);
    KWArg_ll_free(app->kwarg_head);
    Arg_ll_free(app->arg_head);
    free(app);
}

#endif // CLI_UTILS_app