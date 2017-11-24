#ifndef FTSERVER_H
#define FTSERVER_H

#include <pthread.h>
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
#include <dirent.h>


#define MAX_CLIENTS 10
#define MAX_DIR 1024
#define PENDING 5
#define MAX_LEN INET6_ADDRSTRLEN

struct THREAD{
    pthread_t threadID;
    int sockFD;
    char currentDir[MAX_DIR];
};

struct NODE{
    struct THREAD cliThread;
    struct NODE* next;
};

struct CLIENTLIST{
    struct NODE *first, *last;
    int size;
};



void sigchld_handler(int signo);
void sigpipe_handler(int signo);
void* get_in_addr(struct sockaddr *sa);
void getDirList(char* buf, char* path);
void clientInit(struct CLIENTLIST*);
int clientAdd(struct CLIENTLIST*, struct THREAD*);
int clientRemove(struct CLIENTLIST*, struct THREAD*);
int clientCompare(struct THREAD*, struct THREAD*);
void dataConn(void* fd);
void sendFile();
#endif