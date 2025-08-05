#ifndef CLI_UTILS
#define CLI_UTILS

#include <stdbool.h>

#include "../src/app.h"
#include "../src/arg.h"
#include "../src/linked_list.h"

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

char* get_app_name(char* path)
{
    return &path[get_exe_index_from_path(path)];
}

#endif // CLI_UTILS