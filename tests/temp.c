#include <stdio.h>

#include "meta_ll.h"

typedef enum
{
    Invalid = 0x000,
    Unknown,
    
    Identifier = 0x010,
    Litteral,
} TokenType;

typedef struct
{
    char* value;                //            | Token's value
    TokenType type;
} Token;

NEW_LL(Token, value, 1)

int main(void)
{
    Token_ll* tokens = Token_ll_new();

    char* input[] = {
        "-c", 
        "red", 
        "--output", 
        "stdout", 
        "text"
    };

    for (int i = 0; i < 5; ++i) // NOTE: you MUST free() every token
    {
        Token* tmp = calloc(1, sizeof(Token));
        tmp->value = input[i];
        if (input[i][0] == '-')  // TODO: check for valid identifier
        {
            tmp->type = Identifier;
        }
        else {
            tmp->type = Litteral;
        }
        Token_ll_push(&tokens, tmp);
    }

    Token_ll_free(tokens);
    
    return 0;
}