#include "cd.h"
#include "prompt.h"
#include "headers.h"

void cd(char **path)
{
    if(path[1] == NULL)
    {
        printf("No argument for cd provided!\n");
    }

    else if(path[2] != NULL)
    {
        printf("cd: too many arguments!\n");
    }

    else if(!strcmp(path[1], "~"))
    {
        if(chdir(HOME) != 0)
        {
            perror("Error");
        }
    }

    else
    {
        if(chdir(path[1]) != 0)
        {
            perror("Error");
        }
    } 
}