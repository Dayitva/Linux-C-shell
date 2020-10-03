#include "fg.h"
#include "list.h"
#include "main.h"
#include "headers.h"

void fg(char ** parsed, int args)
{
    if(args != 2)
    {
        printf("Usage: fg <job number>");
    }

    else
    {
        pid_t fgPid;
        char * procName;
        
        fgPid = get_Pid(procList, atoi(parsed[1]) - 1);
        procName = get_procname(procList, atoi(parsed[1]) - 1);

        if(fgPid == -1)
        {
            printf("Error: No job with the given job number found\n");
        }

        else
        {
            setpgid(fgPid, getpgid(0));

            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);

            tcsetpgrp(0, fgPid);

            if(kill(fgPid, SIGCONT))
                perror("fg");

            int status;
            waitpid(fgPid, &status, WUNTRACED);

            tcsetpgrp(0, getpgid(0));

            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);

            if(WIFSTOPPED(status)) 
            {
                printf("\nSuspended\t%s [%d]\n", procName, fgPid);

                procList = insert(procList, fgPid, procName);

                fgPid = -1;
            }

            fgPid = -1;

            procList = delete(procList, fgPid, procName);
        }
        
    }
    
}