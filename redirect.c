#include "redirect.h"
#include "headers.h"
#include "cmdhandle.h"
#include "main.h"

int parseRedirect(char ** parsed, int args)
{   
    int i;

    for(i = 0; i < args; i++)
    {
        if(!strcmp(parsed[i], "<"))
        {
            return 1;
        }

        if(!strcmp(parsed[i], ">"))
        {
            return 2;
        }

        if(!strcmp(parsed[i], ">>"))
        {
            return 3;
        }
    }
}

void redirect(char ** parsed, int args)
{
    int i, stdoutSave = -1, stdinSave = -1, inFd = -1, outFd = -1, flag;

    flag = parseRedirect(parsed, args);

    if (flag == 1)
    {
        stdinSave = dup(STDIN_FILENO);
        inFd = open(parsed[0], O_RDONLY, 0644);

        if(inFd < 0)
            perror("Error opening input file");
        else
            dup2(inFd, STDIN_FILENO);
    }

    else if (flag == 2)
    {
        stdoutSave = dup(STDOUT_FILENO);

        outFd = open(parsed[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);

        if(outFd < 0)
            perror("Error opening output file");
        else
            dup2(outFd, STDOUT_FILENO);
    }

    else if (flag == 3)
    {
        stdoutSave = dup(STDOUT_FILENO);

        outFd = open(parsed[2], O_CREAT | O_WRONLY | O_APPEND, 0644);

        if(outFd < 0)
            perror("Error opening output file");
        else
            dup2(outFd, STDOUT_FILENO);
    }

    else
    {
        cmdhandle(parsed, args);
    }
    
}