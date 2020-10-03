#include "headers.h"
#include "sighandle.h"
#include "prompt.h"
#include "main.h"
#include "list.h"

void ctrlC(int sig) 
{
    printf("\n");
    ask_prompt();
    fflush(stdout);
}

void ctrlZ(int sig) 
{
    printf("\n");
    ask_prompt();
    fflush(stdout);
}

void bgProcessExit(int sig) 
{
    int stat_loc;

    pid_t pid = waitpid(-1, &stat_loc, WNOHANG);

    if(pid > 0) 
    {
        if(WIFEXITED(stat_loc) && WEXITSTATUS(stat_loc) == EXIT_SUCCESS)
        {
            fprintf(stderr, COL_FG_YLW "\r%s with pid %d exited normally\n" COL_RST, "Process", pid);
        }

        else
        {
            fprintf(stderr, COL_FG_RED "\r%s with pid %d exited abnormally\n" COL_RST, "Process", pid);
        }

        if(pid >= 0)
        {
            procList = delete(procList, pid, "po");
        }

        ask_prompt();
        fflush(stdout);
    }
}