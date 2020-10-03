#ifndef __SIGHANDLE_H
#define __SIGHANDLE_H

void ctrlC(int sig);
void ctrlZ(int sig);
void bgProcessExit(int sig);

#endif