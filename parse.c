#include "parse.h"
#include "headers.h"

char **parse(char *input)
{
    int buffer = 64, i = 0;
    char **tokens = malloc(buffer * sizeof(char*));
    char *tokenised;

    tokenised = strtok(input, " \t\r\n\a");

    while(tokenised != NULL)
    {
        tokens[i++] = tokenised;

        if (i >= buffer) 
        {
            buffer += 64;
            tokens = realloc(tokens, buffer * sizeof(char*));
        }

        tokenised = strtok(NULL, " \t\r\n\a");
    }

    tokens[i] = NULL;
    return tokens;
}