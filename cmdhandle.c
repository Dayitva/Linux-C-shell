#include "headers.h"
#include "cwd.h"
#include "cmdhandle.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
#include "echo.h"
#include "env.h"
#include "jobs.h"
#include "bg.h"
#include "fg.h"
#include "overkill.h"
#include "kjob.h"
#include "sighandle.h"
#include "main.h"

int cmdhandle(char **parsed, int args)
{
    if(!strcmp(parsed[0], "pwd"))
    {
        pwd();
        return 0;
    }

    else if(!strcmp(parsed[0], "cd"))
    {
        return 0;
    }

    else if(!strcmp(parsed[0], "echo"))
    {
        echo(parsed, args);
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

    else if(!strcmp(parsed[0], "setenv"))
    {
        setEnv(parsed, args);
        return 0;
    }

    else if(!strcmp(parsed[0], "unsetenv"))
    {
        unsetEnv(parsed, args);
        return 0;
    }

    else if(!strcmp(parsed[0], "jobs"))
    {
        jobs(args);
        return 0;
    }

    else if(!strcmp(parsed[0], "kjob"))
    {
        kjob(parsed, args);
        return 0;
    }

    else if(!strcmp(parsed[0], "overkill"))
    {
        overkill(args);
        return 0;
    }

    else if(!strcmp(parsed[0], "fg"))
    {
        fg(parsed, args);
        return 0;
    }

    else if(!strcmp(parsed[0], "bg"))
    {
        bg(parsed, args);
        return 0;
    }

    else if(!strcmp(parsed[0], "clear"))
    {
        printf("\e[1;1H\e[2J");
        return 0;
    }

    else
    {
        return 1;
    }
}