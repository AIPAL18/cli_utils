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
// when processing
    char* value;                //            | value given by the user (overwritten by parse)
} KWArg;

// Non-keyword argument
typedef struct
{
    char* name;                 //            | name that describe the value passed
    char* description;          //            | text that describe the argument (for help)
// when processing
    char* value;                //            | value given by the user (overwritten by parse)
} Arg;

// TODO:
//  add aliases (for help: -?)
//  add names to flags (--reverse <=> -r) to allow user be clear when setting flags
//       for the parser check if its a kwarg or a flag or unknown, if it's a kwarg, THEN you expect a value

#endif // CLI_UTILS_ARG