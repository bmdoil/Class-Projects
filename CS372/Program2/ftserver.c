
#include "ftserver.h"

int main(int argc, char *argv[])
{
    /*The framework for creating the server is adapted from OSU CSS 344 - Brewster's server.c
    REF: https://oregonstate.instructure.com/courses/1648339/pages/block-4
    Lecture 4.3 - Network Servers
    */
    int controlSockFD, connectionSockFD, status;
    int yes = 1;
    struct addrinfo servAddr, *servInfo, *p;
    char buffer[MAX_LEN];

    pthread_mutex_t clientMutex;
    struct CLIENTLIST clientList;
    struct NODE* curClient;
    struct THREAD threads[MAX_CLIENTS];  
    struct sockaddr_storage clientAddr;
    
    socklen_t sizeOfClientInfo;
    size_t ssize = MAX_DIR;   
    struct sigaction sigCld;  
    
    clientInit(&clientList);
    pthread_mutex_init(&clientMutex, NULL);
        
    if (argc < 2) { fprintf(stderr,"USAGE: %s [hostname] [port]\n", argv[0]); exit(1); }

    //Set up address struct
    //REF: http://beej.us/guide/bgnet/output/html/multipage/syscalls.html#getaddrinfo
    memset((char *)&servAddr, '\0', sizeof(servAddr));
    servAddr.ai_family = AF_UNSPEC;
    servAddr.ai_socktype = SOCK_STREAM;
    servAddr.ai_flags = AI_PASSIVE;
    servAddr.ai_protocol = 0;

    if (((status) = getaddrinfo(NULL, argv[2], &servAddr, &servInfo)) != 0)
    {fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status)); exit(1);}

    //Loop through results of gettaddrinfo and bind to first valid one
    //REF: http://beej.us/guide/bgnet/output/html/multipage/clientserver.html
    for (p = servInfo; p != NULL; p = p->ai_next)
    {
        if ((controlSockFD = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            {perror("server: socket"); continue;}

        if (setsockopt(controlSockFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
            {perror("setsockopt"); exit(1);}

        if (bind(controlSockFD, p->ai_addr, p->ai_addrlen) == -1)
            {close(controlSockFD); perror("server: bind"); continue;}

        break;
    }

    freeaddrinfo(servInfo);

    if (p == NULL) {fprintf(stderr, "server failed to bind\n"); exit(1);}
    //Block?
    if (listen(controlSockFD, PENDING) == -1) {perror("listen"); exit(1);}

    sigCld.sa_handler = sigchld_handler;
    sigemptyset(&sigCld.sa_mask);
    sigCld.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sigCld, NULL) == -1) {perror("sigaction"); exit(1);}

    printf("server: waiting for connections...\n");

    while (1)
    {
               
        sizeOfClientInfo = sizeof(clientAddr);

        connectionSockFD = accept(controlSockFD, (struct sockaddr *)&clientAddr, &sizeOfClientInfo);
        if (connectionSockFD == -1) {perror("accept"); continue;}
        if(clientList.size == MAX_CLIENTS){fprintf(stderr, "Connections full.\n"); continue;}
        inet_ntop(clientAddr.ss_family, get_in_addr((struct sockaddr *)&clientAddr), buffer, sizeof(buffer));

        printf("Connection received from:[%d]\n",connectionSockFD);
        fflush(stdout);

        struct THREAD thread;
        thread.sockFD = connectionSockFD;
        char cwd[MAX_LEN];
        getcwd(cwd,MAX_LEN);
        strcpy(thread.currentDir,cwd);
        pthread_mutex_lock(&clientMutex);
        clientAdd(&clientList, &thread);
        pthread_mutex_unlock(&clientMutex);

        pthread_create(&thread.threadID, NULL, dataConn, (void*)&thread);
        
    return 0;    
}

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
    if (compare(thr, &list->first->cliThread) == 0)
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
        if (compare(thr, &curr->next->cliThread) == 0)
        {
            curr->next = curr->next->next;
            free(temp);
            list->size--;
            return 0;
        }
    }
    return -1;
}

}
void dataConn(void* fileDesc)
{
    int byteNum;
    //Cast fileDesc to thread struct
    struct THREAD thread = *(struct THREAD*)fileDesc;

    while (1)
    {
        //byteNum = recv(thread.sockFD, )
    }
}