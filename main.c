#include "headers.h"
#include "cd.h"
#include "cmdhandle.h"
#include "cwd.h"
#include "echo.h"
#include "ls.h"
#include "parse.h"
#include "pinfo.h"
#include "prompt.h"

int main(int argc, char *argv[])
{
    init();

    size_t buffer = 32, input;
    char *str = (char *) malloc (buffer * sizeof(char));
    char *processName = (char *) malloc (buffer * sizeof(char));
    char **parsed;
    int flag = 0, stat_loc, args = 0, bg = 0;
    pid_t child_pid;

    signal(SIGINT, SIG_IGN);

    while (1)
    {
        ask_prompt();

        input = getline(&str, &buffer, stdin);
        parsed = parse(str);

        if(parsed[0] == NULL)
        {
            continue;
        }

        flag = cmdhandle(parsed);

        while(parsed[args] != NULL)
        {
            args++;
        }

        if(!strcmp(parsed[args-1], "&"))
        {
            bg = 1;
            processName = parsed[0];
            parsed[args-1] = NULL;
        }

        if(flag == 1)
        {
            break;
        }

        else if(flag == 2)
        {
            child_pid = fork();

            if (child_pid < 0) 
            {
                perror("Fork failed");
                exit(1);
            }

            if (child_pid == 0) 
            {
                //setpgid(0, 0);
                signal(SIGINT, SIG_DFL);
                
                if(execvp(parsed[0], parsed) < 0)
                {
                    printf("Command '%s' not found!\n", parsed[0]);
                }
            }  
            
            else 
            {
                if(bg == 0)
                {
                    waitpid(child_pid, &stat_loc, WUNTRACED);
                }    
            }
        }
    }

    free(str);
    free(input);
    free(processName);
    exit(0);

    return 0;
}