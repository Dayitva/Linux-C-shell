#include "headers.h"
#include "cwd.h"

void pwd()
{
    char directory[1024];

    if(!getcwd(directory, sizeof(directory)))
    {
        perror("Error: Directory not fetched!");
    }

    else
    {
        printf("%s\n", directory);
    }
}