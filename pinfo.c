#include "pinfo.h"
#include "prompt.h"
#include "headers.h"

int join_open(char * dir, char * file)
{
    char * processFile = (char*) malloc(1024);
    processFile[0] = 0;

    strcat(processFile, dir);
    strcat(processFile, file);

    int fd = open(processFile, O_RDONLY);

    free(processFile);

    return fd;
}

void pinfo(char **parsed)
{
    if(parsed[2] != NULL)
    {
        printf("pinfo: too many arguments!\n");
    }

    else if(parsed[1] == NULL)
    {
        pid_info("self");
    }

    else
    {
        pid_info(parsed[1]);
    }
}

void pid_info(char *pid)
{
    char *processDir = (char*) malloc(1024);
    char *buffer = (char*) malloc(1024);

    int fd;

    sprintf(processDir, "/proc/%s/", pid);

    // Process State
    fd = join_open(processDir, "stat");
    read(fd, buffer, 1024);

    if(fd < 0) 
    {
        printf("Process with pid %s not found\n", pid);
        return;
    }

    if(!strcmp(pid, "self")) 
    {
        printf("pid -- %d\n", getpid());
    }

    else 
    {
        printf("pid -- %s\n", pid);
    }

    strtok(buffer, " ");
    strtok(NULL, " ");
    char * status = strtok(NULL, " ");

    printf("Process status: %s\n", status);

    close(fd);

    // Memory
    fd = join_open(processDir, "statm");
    read(fd, buffer, 1024);

    char * memory = strtok(buffer, " ");
    printf("Memory -- %s\n", memory);

    close(fd);

    // Executable Path
    strcat(processDir, "exe");

    int l = readlink(processDir, buffer, 1024);
    buffer[l] = 0;

    char * path = tilda(buffer);

    printf("Executable path -- %s\n", path);

    free(path);
    free(buffer);
    free(processDir);
}