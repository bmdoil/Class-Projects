#include "server.h"

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

    
    struct sockaddr_storage clientAddr;
    
    socklen_t sizeOfClientInfo;
    size_t ssize = MAX_DIR;   
    struct sigaction sigCld;    
    
        
    if (argc < 2) { fprintf(stderr,"USAGE: %s [hostname] [port]\n", argv[0]); exit(1); }

    //Set up address struct
    //REF: http://beej.us/guide/bgnet/output/html/multipage/syscalls.html#getaddrinfo
    memset((char *)&servAddr, '\0', sizeof(servAddr));
    servAddr.ai_family = AF_UNSPEC;
    servAddr.ai_socktype = SOCK_STREAM;
    servAddr.ai_flags = AI_PASSIVE;
    servAddr.ai_protocol = 0;

    if ((getaddrinfo(NULL, argv[2], &servAddr, &servInfo)) != 0)
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
    //Waiting on client connection
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
         
         //Receive data port

         //Receive command

         //Depending on command, send dir list or file
        
        
    return 0;    
    }
    close(connectionSockFD);
    close(controlSockFD)
}
