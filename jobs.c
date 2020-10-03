#include "jobs.h"
#include "headers.h"
#include "list.h"
#include "main.h"

void jobs(int args)
{
    if (args > 1)
    {
        printf("Usage: jobs\n");
    }

    else
    {
        int index = 1, fd;
        Node * curr = procList;

        char * buf = (char*) malloc(1024);

        while(curr) 
        {
            sprintf(buf, "/proc/%d/stat", curr->pid);
            fd = open(buf, O_RDONLY);

            if(fd < 0) 
            {
                printf("Couldn't find relevant files for pid %d\n", curr->pid);
                perror("jobs");
                continue;
            }

            read(fd, buf, 1024);

            char * status;

            strtok(buf, " ");
            strtok(0, " ");
            char * procStat = strtok(0, " ");

            if(procStat[0] == 'T')
                status = "Stopped";
            else if(procStat[0] == 'Z')
                status = "Zombie";
            else
                status = "Running";

            printf("[%d] %s %s [%d]\n", index, status, curr->name, curr->pid);
            index++;
            curr = curr->next;

            close(fd);
        }

        free(buf);
    }
}