#include "echo.h"
#include "headers.h"

void echo(char **parsed)
{  
    if(parsed[1] == NULL)
    {
        printf("\n");
    }

    else
    {
        int i = 1;

        while(parsed[i] != NULL)
        {
            printf("%s ", parsed[i]);
            i++;
        }
        printf("\n");    
    }   
}