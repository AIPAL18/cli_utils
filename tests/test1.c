#include <stdio.h>

#include "../includes/cli_utils.h"

int main(int argc, char** argv)
{
    Flag reverse = {
        .name = "reverse",
        .symbol = 'r',
        .description = "Reverse `text`",
        .long_description = "Reverse the text provided\nExamples:\n>>> eko -r coucou\nuocuoc",
    };

    KWArg color = {
        .name = "color",
        .symbol = 'c',
        .description = "Print `text` with the given colors",
        .long_description = "Print `text` with the given colors.\nAccepted colors: red, green.\nExamples:\n>>> eko -c red coucou\ncoucou",
        .value_name = "color",
    };

    Arg text = {
        .name = "text",
        .description = "Text that is going to be print out",
    };

    App_t app = {
        .app_name = "Super printer (eko)", 
        .app_exe = "eko", 
        .version = "0.0.1", default_head
    };

    push_flag(&app, &reverse);
    push_kwarg(&app, &color);
    push_arg(&app, &text);
    add_default_arg(&app);
    
    parse(&app, argc, argv);
    
    free_app(app);

    return 0;
}
