#include "headers.h"
#include "cwd.h"
#include "cmdhandle.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
#include "echo.h"

int cmdhandle(char **parsed)
{
    if(!strcmp(parsed[0], "quit"))
    {
        printf("You have exited the shell.\n");
        exit(0);
        return 1;
    }

    else if(!strcmp(parsed[0], "pwd"))
    {
        pwd();
        return 0;
    }

    else if(!strcmp(parsed[0], "cd"))
    {
        cd(parsed);
        return 0;
    }

    else if(!strcmp(parsed[0], "echo"))
    {
        echo(parsed);
        return 0;
    }

    else if(!strcmp(parsed[0], "ls"))
    {
        ls(parsed);
        return 0;
    }

    else if(!strcmp(parsed[0], "pinfo"))
    {
        pinfo(parsed);
        return 0;
    }

    else if(!strcmp(parsed[0], "clear"))
    {
        printf("\e[1;1H\e[2J");
        return 0;
    }

    else
    {
        return 2;
    }
}