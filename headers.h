#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>
#include <stdbool.h>

#define COL_FG_BLK "\033[30;1m"
#define COL_FG_RED "\033[31;1m"
#define COL_FG_GRN "\033[32;1m"
#define COL_FG_YLW "\033[33;1m"
#define COL_FG_BLU "\033[34;1m"
#define COL_FG_MGN "\033[35;1m"
#define COL_FG_CYN "\033[36;1m"
#define COL_FG_WHT "\033[37;1m"

#define COL_BG_BLK "\033[40;1m"
#define COL_BG_RED "\033[41;1m"
#define COL_BG_GRN "\033[42;1m"
#define COL_BG_YLW "\033[43;1m"
#define COL_BG_BLU "\033[44;1m"
#define COL_BG_MGN "\033[45;1m"
#define COL_BG_CYN "\033[46;1m"
#define COL_BG_WHT "\033[47;1m"

#define COL_RST "\033[0m"

char HOME[1024];