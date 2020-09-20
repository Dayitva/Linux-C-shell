#include "prompt.h"
#include "headers.h"
    
void init()
{
    printf("\e[1;1H\e[2J"); // for clearing screen using regex
    printf("Welcome to Dayitva's shell!\n\n");

    int i;

    ssize_t len = readlink("/proc/self/exe", HOME, 1024);

    for(i = len; HOME[i] != '/'; i--);
    HOME[i] = 0;
}

char *tilda(char *cwd)
{
    unsigned long lencwd = strlen(cwd), lenHome = strlen(HOME);
    int offset = -1;

    if(lencwd >= lenHome)
    {
        if(!strncmp(cwd, HOME, lenHome))
        {
            offset = lenHome;
        }
    }
    char * dir = (char*) malloc (1024);

    if(cwd[offset] && cwd[offset] != '/') 
    {
        strcpy(dir, cwd);
        return dir;
    }

    if(offset > 0) 
    {
        dir[0] = '~';
        strcpy(dir + 1, cwd + offset);
    }

    else
    {
        strcpy(dir, cwd);
    }

    return dir;
}

char *create_prompt() 
{
    char hostname[1024];
    gethostname(hostname, 1024);

    char *directory = (char *) malloc (1024);
    directory = getcwd(directory, 1024);
    directory = tilda(directory);

    char *shellprompt = (char *) malloc (1024);
    sprintf(shellprompt, COL_FG_GRN "<%s@%s:" COL_FG_BLU "%s" COL_FG_GRN "> " COL_RST, getlogin(), hostname, directory);

    return shellprompt;
}

void ask_prompt()
{
    printf("%s", create_prompt());
}