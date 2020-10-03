#include "parse.h"
#include "headers.h"

char **parse(char *input)
{
    int buffer = 32, i = 0;
    char **tokens = malloc(buffer * sizeof(char*));
    char *tokenised;

    tokenised = strtok(input, " \t\r\n\a");

    while(tokenised != NULL)
    {
        tokens[i++] = tokenised;

        if (i >= buffer) 
        {
            buffer += 32;
            tokens = realloc(tokens, buffer * sizeof(char*));
        }

        tokenised = strtok(NULL, " \t\r\n\a");
    }

    tokens[i] = NULL;
    return tokens;
}

int parsePipe(char* input, char** strpiped) 
{ 
    int i; 
    for (i = 0; i < 2; i++) 
    { 
        strpiped[i] = strsep(&input, "|"); 
        if (strpiped[i] == NULL) 
            break; 
    } 
  
    if (strpiped[1] == NULL) 
        return 0; // returns zero if no pipe is found. 
    else { 
        return 1; 
    } 
}