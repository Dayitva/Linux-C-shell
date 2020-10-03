#include "kjob.h"
#include "list.h"
#include "main.h"
#include "headers.h"

void kjob(char ** parsed, int args)
{
    if (args != 3)
    {
        printf("Usage: kjob <job number> <signal number>\n");
    }

    else
    {
        
        pid_t pid;

        pid = get_Pid(procList, atoi(parsed[1]) - 1);

        if(pid < 0)
        {
            printf("An error occured while sending signal to the job requested\n");
        }

        else 
        {
            if(kill(pid, atoi(parsed[2])))
            {
                perror("kjob");
            }
        }
    }
    
}