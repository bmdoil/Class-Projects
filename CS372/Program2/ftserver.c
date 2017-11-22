/*
1. ftserver starts on Host A, and validates command-line parameters
(<SERVER_PORT>).
2. ftserver waits on <PORTNUM> for a client request.
3. ftclient starts on Host B, and validates any pertinent command-line parameters.
(<SERVER_HOST>, <SERVER_PORT>, <COMMAND>, <FILENAME>,
<DATA_PORT>, etc…)
4. ftserver and ftclient establish a TCP control connection on <SERVER_PORT>. (For
the remainder of this description, call this connection P)
5. ftserver waits on connection P for ftclient to send a command.
6. ftclient sends a command (-l (list) or -g <FILENAME> (get)) on connection P.
7. ftserver receives command on connection P.
If ftclient sent an invalid command
• ftserver sends an error message to ftclient on connection P, and ftclient
displays the message on-screen.
otherwise
• ftserver initiates a TCP data connection with ftclient on <DATA_PORT>.
(Call this connection Q)
• If ftclient has sent the -l command, ftserver sends its directory to ftclient
on connection Q, and ftclient displays the directory on-screen.
• If ftclient has sent -g <FILENAME>, ftserver validates FILENAME, and
either
- sends the contents of FILENAME on connection Q. ftclient saves the
file in the current default directory (handling "duplicate file name" error
if necessary), and displays a "transfer complete" message on-screen
or
- sends an appropriate error message (“File not found”, etc.) to ftclient on
connection P, and ftclient displays the message on-screen.
• ftserver closes connection Q (don’t leave open sockets!).
8. ftclient closes connection P (don’t leave open sockets!) and terminates.
9. ftserver repeats from 2 (above) until terminated by a supervisor (SIGINT).
*/

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

#define PENDING 5
#define MAX_DIR 1024

//SIGCHLD handler 
//REF: http://beej.us/guide/bgnet/output/html/multipage/clientserver.html
void sigchld_handler(int s)
{
    
    int saved_errno = errno;
    while(waitpid(-1, NULL, WNOHANG) > 0);
    errno = saved_errno;
}

void *get_in_addr(struct sockaddr *sa) {
    return sa->sa_family == AF_INET
      ? (void *) &(((struct sockaddr_in*)sa)->sin_addr)
      : (void *) &(((struct sockaddr_in6*)sa)->sin6_addr);
  }
  
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
    struct sockaddr_storage clientAddress;
    struct sigaction sigCld;
    char buffer[INET6_ADDRSTRLEN];
    char fileName[INET6_ADDRSTRLEN];
    struct addrinfo serverAddress, *servInfo, *p;
    char* token = NULL;
    char* commands[50];
    int commandCount = 0;
    char* directory = NULL;
    
    if (argc < 2) { fprintf(stderr,"USAGE: %s [hostname] [port]\n", argv[0]); exit(1); }

    //Set up address struct
    //REF: http://beej.us/guide/bgnet/output/html/multipage/syscalls.html#getaddrinfo
    memset((char *)&serverAddress, '\0', sizeof(serverAddress));
    serverAddress.ai_family = AF_UNSPEC;
    serverAddress.ai_socktype = SOCK_STREAM;
    serverAddress.ai_flags = AI_PASSIVE;
    serverAddress.ai_protocol = 0;

    if (((status) = getaddrinfo(NULL, argv[1], &serverAddress, &servInfo)) != 0)
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

        memset(&buffer, '\0', sizeof(buffer));

        if (recv(newConnFD, buffer, sizeof(buffer) - 1, 0) == -1)
        {
            //Invalid command, send error message
        }
        
         //Tokenize buffer
        token = strtok(buffer, " ");
        while (token != NULL)
        {   
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

        
        //Reimplement this as a thread?
        spawnPid = fork();
        switch (spawnPid)
        {
            case 0: //Child proc begins
                //Open 2nd TCP connection on DATA PORT commands[0]
                close(listenSocketFD);
                if (sendDir == 1)
                {
                    //memset(&directory, '\0', sizeof(directory));
                    getcwd(directory, ssize);
                    if (directory == NULL){perror("set cwd"); exit(1);}
                   
                    if (send(newConnFD, directory, sizeof(directory) - 1, 0) == -1)
                    {perror("send dir"); exit(1);}
                }
                else if (sendFile == 1)
                {

                }
            




            close(newConnFD);
            exit(0);
        }
        close(newConnFD);
    }
    return 0;
    
}
