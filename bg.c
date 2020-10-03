#include "bg.h"
#include "list.h"
#include "main.h"
#include "headers.h"

void bg(char ** parsed, int args)
{
    if(args != 2)
    {
        printf("Usage: bg <job number>\n");
    }

    else
    {
        pid_t bgPid;
        bgPid = get_Pid(procList, atoi(parsed[1]) - 1);

        if(bgPid == -1)
        {
            printf("Error: No job with the given job number found\n");
        }

        if(kill(bgPid, SIGCONT))
        {
            perror("bg");
        }
    }
    
}