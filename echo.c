#include "echo.h"
#include "headers.h"
#include "env.h"

void echo(char **parsed, int args)
{
    char temp[1024];

    if(args == 1)
    {
        printf("\n");
        return;
    }

    else
    {
        int i;

        for(i = 1; i < args; i++)
        {
            // if(parsed[i][0] == '$')
            // {
            //     strcpy(temp, &parsed[i][1]);
            //     printf("%s ", temp);
            //     printf("%s ", getenv(temp));
            // }

            if(parsed[i])
            {
                printf("%s ", parsed[i]);
            }
        }
        printf("\n");    
    }   
}