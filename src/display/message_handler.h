#ifndef MESSAGE_HANDLER_DECLARATION
#define MESSAGE_HANDLER_DECLARATION

#include <stdlib.h>

void debug(const char *_Format, ...);

void warning(const char *_Format, ...);

void forward_error(
    char const* error_name,
    const char* file,
    unsigned int   line, 
    const char* description,
    char const* format, 
    va_list args
    );

// void error(
//     char const* error_name,
//     const char* file,
//     unsigned int line, 
//     const char* description,
//     char const* format, 
//     ...
//     );

#endif // MESSAGE_HANDLER_DECLARATION