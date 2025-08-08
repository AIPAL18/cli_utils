#include "message_handler.h"

#include <stdarg.h>
#include <stdio.h>
#include "color.h"


void debug(const char *_Format, ...)
{
    va_list args;

    printf(COLOR_GREEN "\nDEBUG - ");
    
    va_start(args, _Format);
    vfprintf(stdout, _Format, args);
    va_end(args);
    
    printf(COLOR_RESET);
}

void warning(const char *_Format, ...)
{
    va_list args;

    printf(COLOR_YELLOW "\nWARNING - ");
    
    va_start(args, _Format);
    vfprintf(stdout, _Format, args);
    va_end(args);
    
    printf(COLOR_RESET);
}

void forward_error(
    char const* error_name,
    const char* file,
    unsigned int   line, 
    const char* description,
    char const* format, 
    va_list args
    )
{
    printf(COLOR_MAGENTA "\n%s (File <%s:%d>): ", error_name, file, line);
    printf(COLOR_RESET "%s\n\n" COLOR_RED, description);
    
    vfprintf(stdout, format, args);

    printf(COLOR_RESET);
    exit(EXIT_FAILURE);
}

/*
void error(
    char const* error_name,
    const char* file,
    unsigned int line, 
    const char* description,
    char const* format, 
    ...
    )
{
    printf(COLOR_MAGENTA "\n%s (File <%s:%d>): ", error_name, file, line);
    printf(COLOR_RESET "%s\n\n" COLOR_RED, description);

    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);

    printf(COLOR_RESET);
    exit(EXIT_FAILURE);
}

#define raise(error_name, _Format, ...) ((void)(                                                                                    \
    error(#error_name, _CRT_WIDE(__FILE__), (unsigned)(__LINE__), _CRT_WIDE(FUNC_SIG), _CRT_WIDE(_Format), __VA_ARGS__))  \
    )
*/