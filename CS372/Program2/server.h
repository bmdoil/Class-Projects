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
#define MAX_LEN 1024
#define PENDING 5


void* get_in_addr(struct sockaddr *sa);
void getDir(char* buf, char* path);

//void dataConn(struct THREAD*);
void sendFile();

#endif