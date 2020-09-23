#include "ls.h"
#include "headers.h"

void print_ls(char *path, bool printhidden)
{
    struct dirent **namelist;
    int n;

    n = scandir(path, &namelist, NULL, alphasort);

    if(n < 0) 
    { 
        perror("ls");
    }
        
    else 
    { 
        while (n--) 
        {
            if(!printhidden)
            {
                if(!strncmp((namelist[n]->d_name), ".", 1))
                {
                    free(namelist[n]);
                    continue;
                }

                printf("%s\n",namelist[n]->d_name); 
                free(namelist[n]); 
            }

            else
            {
                printf("%s\n",namelist[n]->d_name); 
                free(namelist[n]);
            }
            
        } 
        
        free(namelist); 
    }
}

void ls(char **parsed)
{
    int args = 0, flag = 0;

    while(parsed[args] != NULL)
    {
        if(!strcmp(parsed[args], "-a"))
        {
            flag = 1;
        }

        // else if(!strcmp(parsed[args], "-l"))
        // {
        //     flag = 2;
        // }

        // else if(!strcmp(parsed[args], "-la") || !strcmp(parsed[args], "-al"))
        // {
        //     flag = 3;
        // }

        else if(!strcmp(parsed[args], "~"))
        {
            parsed[args] = HOME;
        }

        args++;
    }

    if(args == 1)
    {
        print_ls(".", false);
    }

    else if(args == 2 && flag == 0)
    {
        print_ls(parsed[1], false);
    }

    else if(flag == 0)
    {
        for(int i = 1; i < args; i++)
        {
            printf("%s:\n", parsed[i]);

            print_ls(parsed[i], false);

            printf("\n");
        }
    }

    else if(args == 2 && flag == 1)
    {
        print_ls(".", true);
    }

    else if(args == 3 && flag == 1)
    {
        for(int i = 1; i < args; i++)
        {
            if(!strcmp(parsed[i], "-a"))
            {
                continue;
            }

            print_ls(parsed[i], true);
        }
    }

    else if(flag == 1)
    {
        for(int i = 1; i < args; i++)
        {
            if(!strcmp(parsed[i], "-a"))
            {
                continue;
            }

            printf("%s:\n", parsed[i]);

            print_ls(parsed[i], true);

            printf("\n");
        }
    }
}