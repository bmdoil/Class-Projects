#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <signal.h>
#include "ftserver.h"

#define PENDING 5
#define MAX_DIR 1024


void sigchld_handler(int s);
void* get_in_addr(struct sockaddr *sa);
void getDirList(char* buf, char* path);

int main(int argc, char *argv[])
{
    /*The framework for creating the server is adapted from OSU CSS 344 - Brewster's server.c
    REF: https://oregonstate.instructure.com/courses/1648339/pages/block-4
    Lecture 4.3 - Network Servers
    */
    int sendDir = 0;
    int sendFile = 0;
    int listenSocketFD, newConnFD, status;
    int yes = 1;
    socklen_t sizeOfClientInfo;
    size_t ssize = MAX_DIR;
    pid_t spawnPid = -5;
    FILE* outputFile = NULL;
    struct sockaddr_storage clientAddress;
    struct sigaction sigCld;
    char buffer[INET6_ADDRSTRLEN];
    char fileName[INET6_ADDRSTRLEN];
    struct addrinfo serverAddress, *servInfo, *p;
    char* token = NULL;
    char* commands[50];
    int commandCount = 0;
        
    if (argc < 2) { fprintf(stderr,"USAGE: %s [hostname] [port]\n", argv[0]); exit(1); }

    //Set up address struct
    //REF: http://beej.us/guide/bgnet/output/html/multipage/syscalls.html#getaddrinfo
    memset((char *)&serverAddress, '\0', sizeof(serverAddress));
    serverAddress.ai_family = AF_UNSPEC;
    serverAddress.ai_socktype = SOCK_STREAM;
    serverAddress.ai_flags = AI_PASSIVE;
    serverAddress.ai_protocol = 0;

    if (((status) = getaddrinfo(NULL, argv[2], &serverAddress, &servInfo)) != 0)
    {fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status)); exit(1);}

    //Loop through results of gettaddrinfo and bind to first valid one
    //REF: http://beej.us/guide/bgnet/output/html/multipage/clientserver.html
    for (p = servInfo; p != NULL; p = p->ai_next)
    {
        if ((listenSocketFD = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            {perror("server: socket"); continue;}

        if (setsockopt(listenSocketFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
            {perror("setsockopt"); exit(1);}

        if (bind(listenSocketFD, p->ai_addr, p->ai_addrlen) == -1)
            {close(listenSocketFD); perror("server: bind"); continue;}

        break;
    }

    freeaddrinfo(servInfo);

    if (p == NULL) {fprintf(stderr, "server failed to bind\n"); exit(1);}
    //Block?
    if (listen(listenSocketFD, PENDING) == -1) {perror("listen"); exit(1);}

    sigCld.sa_handler = sigchld_handler;
    sigemptyset(&sigCld.sa_mask);
    sigCld.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sigCld, NULL) == -1) {perror("sigaction"); exit(1);}

    printf("server: waiting for connections...\n");

    while (1)
    {
        sendDir = 0;
        sendFile = 0;
        commandCount = 0;        
        sizeOfClientInfo = sizeof(clientAddress);

        newConnFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo);
        if (newConnFD == -1) {perror("accept"); continue;}
        inet_ntop(clientAddress.ss_family, get_in_addr((struct sockaddr *)&clientAddress), buffer, sizeof(buffer));

        fflush(stdout);
        memset(&buffer, '\0', sizeof(buffer));

        if (recv(newConnFD, buffer, sizeof(buffer) - 1, 0) == -1)
        {
            //Invalid command, send error message
        }
        
         //Do I need to tokenize?
         /*
        token = strtok(buffer, " ");
        while (token != NULL)
        {   
            //Rethink this
            if ((strcmp(token, "-l") && strcmp(token, "-g")) || commandCount > 5)
            {
                //Invalid command, send error message
                break;
            }
            if (strcmp(token, "-l") == 0)
            {
                sendDir = 1;
                token = strtok(NULL, " ");                
            }
            else if (strcmp(token, "-g") == 0)
            {
                sendFile = 1;
                memset(&fileName, '\0', sizeof(fileName));
                strcpy(fileName, token);
                token = strtok(NULL, " ");                
            }   
            else 
            {
                commands[commandCount] = token;
                commandCount++;
            }          
        }        
        commands[commandCount] = NULL;
        //Reset buffer
        memset(&buffer, '\0', sizeof(buffer))
        */
        //Reimplement this as a thread
        spawnPid = fork();
        if (spawnPid)
        {
            close(listenSocketFD);
            //Open 2nd TCP connection on DATA PORT using commands array  
            
            if (sendDir == 1)
            {                    
                   getDirList(buffer, ".");                           
            }
            else if (sendFile == 1)
            {
                outputFile = fopen(fileName, "wb")
                if (outputFile == NULL){fprintf(stderr, "Unable to open file %s\n", fileName);}
                int bytesSent = (send(newConnFD, outputFile, sizeof(outputFile), 0));
                if (bytesSent < 0){perror("send"); exit(1);}
            }
            
           
        }
        sendDir = 0;
        sendFile = 0;
        close(newConnFD);
    }
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
    DIR* d
    d = opendir(path);
    struct dirent* dir;
    if (d)
    {
        while (dir = readdir(d) != NULL)
        {
            if (dir->d_type == DT_REG)
            {                                
                snprintf(buf, sizeof(buf) - 1, "%s\n", dir->dname);
            }
        }
    }
    closedir(d);
    //Make sure all data is sent                 
}

