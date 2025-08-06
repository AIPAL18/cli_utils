#ifndef CLI_UTILS_PPRINT
#define CLI_UTILS_PPRINT

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

int is_break_char(char c) { // break on them
    return c == ' ';
}

int is_soft_break(char c) { // will be deleted if we break on them
    return c == ' ';
}

void pprint_usage(const char *input, int _width, size_t indent)
{
    int width = _width - indent;
    if (width <= 10) {
        printf("%s", input);
        return;
    }
    int len = strlen(input);
    int start = 0;
    bool just_break = false;

    while (start < len) { // Chat-GPT
        int end = start + width;

        if (just_break)
        {
            just_break = !just_break;
            for (size_t i = 0; i <= indent; ++i) printf(" ");
        }

        if (end >= len) {
            // Fin de texte : on imprime tout le reste
            printf("%s\n", input + start);
            break;
        }

        // Chercher le dernier séparateur dans la fenêtre
        int split = end;
        while (split > start && !is_break_char(input[split])) {
            split--;
        }

        if (split == start) {
            // Aucun séparateur trouvé dans la fenêtre : le mot est plus long que width
            // On cherche la fin du mot pour l'imprimer en entier
            int word_end = start;
            while (word_end < len && !is_break_char(input[word_end])) {
                word_end++;
            }
            printf("%.*s\n", word_end - start, input + start);
            start = word_end;
            just_break = true;
        } else {
            // Trouvé un séparateur : on imprime jusqu'à ce point
            // On exclut les espaces en fin de ligne
            int print_len = split - start;

            // Inclure les dash/underscore à la fin (si présent)
            if (input[split] == '-' || input[split] == '_') {
                print_len++;
            }

            printf("%.*s\n", print_len, input + start);
            start = split + 1; // saut du séparateur
            just_break = true;
        }
    }
}

char* format(const char* _format, ...)
// you must free the return pointer !
// only char arguments to be able to compute the total size !
{
    va_list args, args_copy;

    va_start(args, _format);
    va_copy(args_copy, args);

    // compute length for malloc
    size_t length = strlen(_format) + 1; // for /0

    for (int i = 0; _format[i] != '\0'; ++i)
    {
        if (_format[i] == '%' && _format[i + 1] != '\0')
        {
            ++i;
            switch (_format[i])
            {
            case 'c':
                (void)va_arg(args, int);
                ++length;
                break;
            case 's':
                char* arg = va_arg(args, char*);
                length += strlen(arg);
                break;
            default:
                break;
            }
        }
    }

    char* string = malloc(length);

    // actual formating
    if (vsprintf(string, _format, args_copy) < 0) {
        printf("Error while formating a message: Memory allocation failed.\n");
    }
    va_end(args);
    va_end(args_copy);
    
    return string;
}

// int main() {
//     const char *text = "Ceci-est_un_exemple_de_chaine_tres-longue sans interruption notable mais avec quelques separateurs_intelligents.";
//     int largeur = 20;
//     printf("                    |\n");
//     pprint(text, largeur);
//     return 0;
// }

#endif // CLI_UTILS_PPRINT