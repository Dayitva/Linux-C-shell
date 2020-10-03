#include "headers.h"
#include "piping.h"
#include "cmdhandle.h"

int countPipes(char ** parsed, int args)
{
    int i, counter = 0;
    for(i = 0; i < args; i++)
    {
        if(parsed[i] == "|")
        {
            counter++;
        }
    }

    return counter;
}

void piping(char ** parsed, char ** parsed2, int args)
{
    int numpipes = countPipes(parsed, args);

    if(numpipes == 0)
    {
        cmdhandle(parsed, args);
    }

    else
    {
        int pipefd[2];  
        pid_t p1, p2; 
    
        if (pipe(pipefd) < 0) 
        { 
            printf("\nPipe could not be initialized"); 
            return; 
        }

        p1 = fork(); 

        if (p1 < 0) 
        { 
            printf("\nCould not fork"); 
            return; 
        } 
    
        if (p1 == 0) 
        { 
            // Child 1 executing.. 
            // It only needs to write at the write end 
            close(pipefd[0]); 
            dup2(pipefd[1], STDOUT_FILENO); 
            close(pipefd[1]); 
    
            if (execvp(parsed[0], parsed) < 0) 
            { 
                printf("\nCould not execute command 1.."); 
                exit(0); 
            }
        } 
        
        else 
        { 
            // Parent executing 
            p2 = fork(); 
    
            if (p2 < 0) 
            { 
                printf("\nCould not fork"); 
                return; 
            } 
    
            // Child 2 executing.. 
            // It only needs to read at the read end 
            if (p2 == 0) 
            { 
                close(pipefd[1]); 
                dup2(pipefd[0], STDIN_FILENO); 
                close(pipefd[0]); 
                if (execvp(parsed2[0], parsed2) < 0) 
                { 
                    printf("\nCould not execute command 2.."); 
                    exit(0); 
                } 

            } 
            
            else 
            { 
                // parent executing, waiting for two children 
                wait(NULL); 
                wait(NULL); 
            }
        }
    }
}