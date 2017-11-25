
#include "server.h"

//SIGCHLD handler 
//REF: http://beej.us/guide/bgnet/output/html/multipage/clientserver.html
void sigchld_handler(int s)
{
    
    int saved_errno = errno;
    while(waitpid(-1, NULL, WNOHANG) > 0);
    errno = saved_errno;
}
//Get correct sockaddr. Handles IPv4 and IPv6 
//REF: http://beej.us/guide/bgnet/output/html/multipage/clientserver.html
void *get_in_addr(struct sockaddr *sa)
{
    return sa->sa_family == AF_INET
      ? (void *) &(((struct sockaddr_in*)sa)->sin_addr)
      : (void *) &(((struct sockaddr_in6*)sa)->sin6_addr);
}
//List files in directory 'path'
//REF:https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
void clientLS(char* buf, char* path)
{
    DIR* d;
    d = opendir(path);
    struct dirent* dir;
    if (d)
    {
        while (dir = readdir(d) != NULL)
        {
            if (dir->d_type == DT_REG)
            {                                
                snprintf(buf, sizeof(buf) - 1, "%s\n", dir->d_name);
            }
        }
    }
    closedir(d);
    //Make sure all data is sent                 
}
void clientInit(struct CLIENTLIST* list)
{
    list->first = list->last = NULL;
    list->size = 0;
}
//TODO
int clientCompare(struct THREAD* thr1, struct THREAD* thr2)
{
    return 0;
}
//Add client to client list. Using Circular Linked List structure adapted from OSU CS 261 Lecture Slides
int clientAdd(struct CLIENTLIST* list, struct THREAD* thr)
{
    if(list->size == MAX_CLIENTS) return -1;
    //If list empty
    if(list->first == NULL)
    {
        list->first = (struct NODE*)malloc(sizeof(struct NODE));
        list->first->cliThread = *thr;
        list->first->next = NULL;
        list->last = list->first;
    }
    //If list not empty
    {
        list->last->next = (struct NODE*)malloc(sizeof(struct NODE));
        list->last->next->cliThread = *thr;
        list->last->next->next = NULL;
        list->last = list->last->next;
    }
    list->size++;
    return 0;
}
int clientRemove(struct CLIENTLIST* list, struct THREAD* thr)
{
    struct NODE *curr, *temp;
    if (list->first == NULL) return -1;
    if ((clientCompare(thr, &list->first->cliThread)) == 0)
    {
        temp = list->first;
        list->first = list->first->next;
        if (list->first == NULL) list->last = list->first;
        free(temp);
        list->size--;
        return 0;
    }
    for (curr = list->first; curr->next != NULL; curr = curr->next)
    {
        if ((clientCompare(thr, &curr->next->cliThread)) == 0)
        {
            curr->next = curr->next->next;
            free(temp);
            list->size--;
            return 0;
        }
    }
    return -1;
}
void dataConn(void* fileDesc)
{
    int byteNum;
    //Cast fileDesc to thread struct
    struct THREAD thread = *(struct THREAD*)fileDesc;

    while (1)
    {
        byteNum = recv(thread.sockFD, )
    }
}