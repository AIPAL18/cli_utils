#ifndef CLI_UTILS_PPRINT
#define CLI_UTILS_PPRINT

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

int is_break_char(char c) {
    return c == ' ' || c == '-' || c == '_';
}

int is_soft_break(char c) {
    return c == ' ' || c == '\t';
}

void pprint_wrap(const char *input, int width, ...) {
    int len = strlen(input);
    int start = 0;

    // Dans l'ordre:
    va_list args;

    va_start(args, width);
    char* temp;
    while (true)
    {
        temp = va_arg(args, char*);
        if (!temp) {
            break;
        }
        else {
            printf("%s", temp);
        }
    }
    va_end(args);

    while (start < len) { // Chat-GPT
        if (start >= len) break;

        int end = start + width;

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
        }
    }
}

char* format(const char* format, ...)  // you must free the return pointer !
{
    char* string = NULL;
    va_list args;

    va_start(args, format);
    if (vsprintf_s(string, format, args) < 0) { //this is for logging, so failed allocation is not fatal
        printf("Error while formating a message: Memory allocation failed.\n");
    }
    va_end(args);
    
    return string;
}

// int main() {
//     const char *text = "Ceci-est_un_exemple_de_chaine_tres-longue sans interruption notable mais avec quelques separateurs_intelligents.";
//     int largeur = 20;
//     printf("                    |\n");
//     pprint_wrap(text, largeur);
//     return 0;
// }

#endif // CLI_UTILS_PPRINT