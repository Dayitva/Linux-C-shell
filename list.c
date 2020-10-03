#include "list.h"
#include "main.h"

Node * newNode(pid_t pid, char * name) 
{
    Node * ret = (Node *) malloc(sizeof(Node));
    ret->next = 0;
    ret->pid = pid;
    ret->name = name;

    return ret;
}

Node * insert(Node * root, pid_t pid, char * name) 
{
    if(!root)
    {
        return newNode(pid, name);
    }

    Node * ret = root;
    Node * curr = root;

    while(curr->next)
    {
        curr = curr->next;
    }

    curr->next = newNode(pid, name);

    return ret;
}

Node * delete(Node * root, pid_t pid, char * name) 
{
    if(!root)
        return 0;

    Node * ret = root,
         *curr = root,
         *prev = 0;

    if(curr->pid == pid) 
    {
        ret = curr->next;
        free(curr);

        return ret;
    }

    while(curr && curr->pid != pid) 
    {
        prev = curr;
        curr = curr->next;
    }

    if(!curr)
        return 0;

    prev->next = curr->next;

    if(curr->name)
        free(curr->name);

    free(curr);

    return ret;
}

pid_t get_Pid(Node * root, int i) 
{
    pid_t pid = -1;

    Node * curr = root;

    if(!root)
        return pid;

    for(int j = 0; j < i; j++) 
    {
        if(!curr)
            return pid;

        curr = curr->next;
    }

    if(curr)
        return curr->pid;
    else
        return pid;
}

char * get_procname(Node * root, int i) 
{
    char * name = 0;

    Node * curr = root;

    if(!root)
        return name;

    for(int j = 0; j < i; j++) 
    {
        if(!curr)
            return name;

        curr = curr->next;
    }

    if(curr)
        return curr->name;
    else
        return name;
}