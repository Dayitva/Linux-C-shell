#ifndef __PINFO_H
#define __PINFO_H

int openFile(char * dir, char * file);
char *getArg(char * buf, int n);
void pinfo(char **parsed);
void pid_info(char *pid);

#endif