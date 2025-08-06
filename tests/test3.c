#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_break_char(char c) {
    return c == ' ' || c == '-' || c == '_';
}

int is_soft_break(char c) {
    return c == ' '; // seuls les espaces peuvent être supprimés
}

void pprint_wrap(const char *input, int width) {
    // Chat-GPT
    int len = strlen(input);
    int start = 0;

    while (start < len) {
        // Ignorer les espaces initiaux
        while (start < len && isspace(input[start])) {
            start++;
        }

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

int main() {
    const char *text = "Ceci-est_un_exemple_de_chaine_tres-longue sans interruption notable mais avec quelques separateurs_intelligents.";
    int largeur = 20;
    printf("                    |\n");
    pprint_wrap(text, largeur);
    return 0;
}
