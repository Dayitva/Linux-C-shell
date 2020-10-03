#include "headers.h"

#ifndef __LIST_H
#define __LIST_H

typedef struct Node 
{
    struct Node * next;
    pid_t pid;
    char * name;
} Node;

Node * insert(Node * root, pid_t pid, char * name);

Node * delete(Node * root, pid_t pid, char * name);

pid_t get_Pid(Node * root, int i);

char * get_procname(Node * root, int i);

#endif