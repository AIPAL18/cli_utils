#ifndef CLI_UTILS_ARG
#define CLI_UTILS_ARG

#include <stdbool.h>

// Keyword argument
typedef struct
{
    char* name;                 //            | name used to call the argument
    char symbol;                //  optionnal | character used to call the argument
    char* description;          //            | text that describe the argument (for general help)
    char* long_description;     //            | text that describe the argument (for specialized help)
} Flag;

// Keyword argument
typedef struct
{
    char* name;                 //            | name used to call the argument
    char symbol;                //  optionnal | character used to call the argument
    char* description;          //            | text that describe the argument (for general help)
    char* long_description;     //            | text that describe the argument (for specialized help)
    char* value_name;           //  optionnal | name that describe the value passed to the argument (for help)
    bool required;              //  optionnal | specify if the kwarg is required to run the app
} KWArg;

// Non-keyword argument
typedef struct
{
    char* name;                 //            | name that describe the value passed
    char* description;          //            | text that describe the argument (for help)
} Arg;

// add aliases (for help: -?)

#endif // CLI_UTILS_ARG