#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

char fmt1 [] = "%d %s  %s  %s  %s\n";

char* vout(char *fmt, ...)
{
    va_list arg_ptr;
    
    va_start(arg_ptr, fmt);
    printf("%llu\n", sizeof(arg_ptr));
    // char* string = malloc();
    // vsprintf(string, fmt, arg_ptr);
    va_end(arg_ptr);
    // return string;
    return "coucou";
}

char* format(int n, const char* format, ...)  // you must free the return pointer !
{
    va_list args1, args2;

    va_start(args1, format); // only char arguments to be able to compute the total size !
    va_copy(args2, args1);  // Make a copy BEFORE consuming args1

    size_t length = strlen(format);
    for (int i = 0; i < n; ++i)
    {
        length += strlen(va_arg(args1, char*));
    }
    
    printf("total length: %llu\n", length);
    char* string = (char*)malloc(length * sizeof(char));

    if (vsprintf(string, format, args2) < 0) { //this is for logging, so failed allocation is not fatal
        printf("Error while formating a message: Memory allocation failed.\n");
    }

    va_end(args1);
    va_end(args2);  // Always call va_end on copied va_list

    return string;
}

int main(void)
{
    char* string = format(2, "coucou %s", "Elie");
    printf("%s", string);
    free(string);
    return 0;
}