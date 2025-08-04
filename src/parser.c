#include "parser.h"

#include <string.h>

int get_exe_index_from_path(char* path)
{
    int last_index = -1;
    
    for (size_t i = 0; path[i] != '\0' ; ++i)
    {
        if (path[i] == '\\' || path[i] == '/')
        {
            last_index = i;
        }
    }

    return last_index + 1;
}


char* get_exe(char* path)
{
    return &path[get_exe_index_from_path(path)];
}
