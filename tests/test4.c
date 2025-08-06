#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_break_char(char c) {
    return c == ' ' || c == '-' || c == '_';
}

char **smart_word_wrap(const char *input, int width, int *line_count) {
    int len = strlen(input);
    int start = 0;
    int capacity = 10;
    int count = 0;

    char **lines = malloc(capacity * sizeof(char *));
    if (!lines) return NULL;

    while (start < len) {
        // Skip leading spaces
        while (start < len && isspace(input[start])) {
            start++;
        }

        if (start >= len) break;

        int end = start + width;
        if (end >= len) end = len;

        // Find split point
        int split = end;
        while (split > start && !is_break_char(input[split])) {
            split--;
        }

        int print_len = 0;

        if (split == start) {
            // No break char found — print full word even if it exceeds width
            int word_end = start;
            while (word_end < len && !is_break_char(input[word_end])) {
                word_end++;
            }
            print_len = word_end - start;
            split = word_end;
        } else {
            // Found break char
            print_len = split - start;
            if (input[split] == '-' || input[split] == '_') {
                print_len++; // keep dash or underscore
            }
        }

        // Allocate line string
        char *line = malloc(print_len + 1);
        if (!line) {
            // Free already allocated lines in case of error
            for (int i = 0; i < count; i++) {
                free(lines[i]);
            }
            free(lines);
            return NULL;
        }
        strncpy(line, input + start, print_len);
        line[print_len] = '\0';

        // Add to array
        if (count >= capacity) {
            capacity *= 2;
            char **temp = realloc(lines, capacity * sizeof(char *));
            if (!temp) {
                for (int i = 0; i < count; i++) free(lines[i]);
                free(line);
                free(lines);
                return NULL;
            }
            lines = temp;
        }
        lines[count++] = line;

        start = split;
        // Skip following space
        if (input[start] == ' ') start++;
        else if (input[start] == '-' || input[start] == '_') start++; // already included
    }

    *line_count = count;
    return lines;
}

int main() {
    const char *text = "Ceci-est_un_exemple de chaîne très-longue sans interruption notable mais avec quelques séparateurs_intelligents.";
    int width = 20;
    int count = 0;

    char **wrapped = smart_word_wrap(text, width, &count);

    printf("                    |\n");
    if (wrapped) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", wrapped[i]);
            free(wrapped[i]); // Libération ligne par ligne
        }
        free(wrapped); // Libération du tableau
    } else {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
    }

    return 0;
}
