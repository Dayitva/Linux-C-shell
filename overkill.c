#include "headers.h"
#include "overkill.h"
#include "list.h"
#include "main.h"

void overkill(int args)
{
    if(args > 1)
    {
        printf("Usage: overkill\n");
    }

    else
    {
        pid_t pid;
        char * procName;
        
        pid = get_Pid(procList, 0);
        procName = get_procname(procList, 0);

        while(pid > 0) 
        {
            procList = delete(procList, pid, procName);

            if(kill(pid, SIGKILL))
            {
                perror("overkill");
            }
            
            pid = get_Pid(procList, 0);
            procName = get_procname(procList, 0);
        }
    }
    
}