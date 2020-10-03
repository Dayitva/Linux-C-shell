#include "headers.h"
#include "bg.h"
#include "cd.h"
#include "cmdhandle.h"
#include "cwd.h"
#include "echo.h"
#include "env.h"
#include "fg.h"
#include "jobs.h"
#include "kjob.h"
#include "list.h"
#include "ls.h"
#include "main.h"
#include "overkill.h"
#include "parse.h"
#include "pinfo.h"
#include "piping.h"
#include "prompt.h"
#include "redirect.h"
#include "sighandle.h"

char * procName;
char prev1[1024];

int main(int argc, char *argv[])
{
    init();

    size_t buffer = 32, input;
    char *str = (char *) malloc (buffer * sizeof(char));
    char *processName = (char *) malloc (buffer * sizeof(char));
    char **parsed;
    int stat_loc;
    pid_t child_pid, fgpid;
    bool prevset = false;

    while (1)
    {
        int bg = 0, args = 0, flag = 0, counter = 0;

        ask_prompt();

        input = getline(&str, &buffer, stdin);
        parsed = parse(str);

        procName = parsed[0];

        if(input == -1)
        {
            printf("\n");
            exit(0);
            break;
        }

        if(parsed[0] == NULL)
        {
            continue;
        }
        
        else if(parsed[0][0] == '&')
        {
            printf("Error: syntax error near unexpected token '&'\n");
            continue;
        }

        else if(parsed[0][0] == ';')
        {
            printf("Error: syntax error near unexpected token ';'\n");
            continue;
        }

        else if(!strcmp(parsed[0], "quit"))
        {
            printf("You have exited the shell. Goodbye!\n\n");
            exit(0);
            break;
        }

        while(parsed[args] != NULL)
        {
            args++;
        }

        // processName = parsed[0];

        if(!strcmp(parsed[args-1], "&"))
        {
            bg = 1;
            processName = parsed[0];
            args -= 1;
            parsed[args] = NULL;
        }  

        child_pid = fork();

        if (child_pid < 0) 
        {
            perror("Fork failed");
            exit(1);
        }

        if (child_pid == 0) 
        {
            setpgid(0, 0);
            // signal(SIGINT, SIG_DFL);
            // signal(SIGTSTP, SIG_DFL);

            flag = cmdhandle(parsed, args);

            if(flag == 1)
            {
                if(execvp(parsed[0], parsed) < 0)
                {
                    printf("Error: Command '%s' not found!\n", parsed[0]);
                }

                exit(EXIT_FAILURE);
            }

            exit(0);
        }  
        
        else 
        {
            if(!strcmp(parsed[0], "cd"))
            {
                if(parsed[1] != NULL && strcmp(parsed[1], "-"))
                {
                    getcwd(prev1, sizeof(prev1));
                    prevset = true;
                }

                cd(parsed, prev1, prevset);
            }

            if(bg == 1)
            {
                procList = insert(procList, child_pid, processName);
            }

            if(bg == 0)
            {                
                // printf("%s\n", prev);
                fgpid = child_pid;

                signal(SIGTTIN, SIG_IGN);
                signal(SIGTTOU, SIG_IGN);

                tcsetpgrp(0, fgpid);

                waitpid(fgpid, &stat_loc, WUNTRACED);

                tcsetpgrp(0, getpgid(0));

                signal(SIGTTIN, SIG_DFL);
                signal(SIGTTOU, SIG_DFL);
            }

            if(WIFSTOPPED(stat_loc)) 
            {
                printf("\nSuspended\t%s [%d]\n", processName, fgpid);
                
                procList = insert(procList, fgpid, processName);

                fgpid = -1;
            }

            fgpid = -1;
        }
    }

    free(str);
    free(processName);
    exit(0);

    return 0;
}