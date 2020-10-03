#include "env.h"
#include "headers.h"

void setEnv(char **parsed, int args)
{    
    if(args == 2)
    {
        if(!parsed[1])
        {
            return;
        }

        if(setenv(parsed[1], "", 1))
        {
            perror("setenv");
        }
    }

    else if(args == 3)
    {
        if(!parsed[1] || !parsed[2])
        {
            return;
        }

        if(setenv(parsed[1], parsed[2], 1))
        {
            perror("setenv");
        }

        // printf("%s\n", getenv(parsed[1]));
    }

    else
    {
        printf("Usage: setenv var [value]\n");
    }
    
}

void unsetEnv(char **parsed, int args)
{
    if(args == 2)
    {
        if(unsetenv(parsed[1]))
        {
            perror("unsetenv");
        }
    }

    else
    {
        printf("Usage: unsetenv var\n");
    }
}