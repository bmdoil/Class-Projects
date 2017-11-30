#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define MAX_LEN 1024
void sendFile(int sockfd, char* contents);
void recvFile(int sockfd);

int main(int argc, char* argv[])
{
    if (argc < 2) {fprintf(stderr,"USAGE: %s [listening port]\n", argv[0]); exit(1); }

    char* handshake = "3Q9I6E";
    char buffer[MAX_LEN];
    struct addrinfo addr, *addrInfo, *p;
    char* hostname = "localhost"
    char* port = NULL;
    socklen_t addr_size;
    struct sockaddr_in clientAddr
    //Convert port
    inet_pton(AF_INET, argv[1], port);
    int sock, sockFD;
    int yes = 1;
    pid_t = spawnPid;

     memset((char*)&addr, '\0', sizeof(addr));
    addr.ai_family = AF_INET;
    addr.ai_socktype = SOCK_STREAM;
    addr.ai_flags = AI_PASSIVE;
    addr.ai_protocol = 0;
    
    if((getaddrinfo(hostname, port, &addr, &addrInfo)) != 0){fprintf(stderr, "Error creating socket %s\n",argv[3]); exit(2);}

    for (p = addrInfo; p != NULL; p = p->ai_next)
    {
        if ((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {perror("server: socket"); continue;}
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {perror("setsockopt"); exit(2);}
        if (bind(sock, p->ai_addr, p->ai_addrlen) == -1) {close(sock); perror("server: bind"); continue;}
        break;
    }
    if (p == NULL) {fprintf(stderr, "server failed to bind\n"); exit(2);}
    freeaddrinfo(addrInfo);
    if (listen(sock, 5) == -1) {perror("listen"); exit(1);}
    printf("server: waiting for connections...\n");
    fflush(stdout);

    //Spawn child process to do separate encryptions    
    while (sockFD = accept(sock, (struct sockaddr *)&clientAddr, &addr_size))
    {
        //Fork
        spawnPid = fork();
        //In child close listening socket, do stuff on accepted socket

        //In parent close accepted socket, resume accept loop
        addr_size = sizeof(struct sockaddr_in);
        
        if (sockFD < 0) {perror("accept"); printf("error accepting connection"); close(sock); close(sockFD); exit(2);}

        if (recv(sockFD, buffer, sizeof(buffer), 0) < 0){perror("Data recv error:"; close(sock); close(sockFD); exit(2);)}
        if (strcmp(buffer, handshake) != 0)
        {

        }
    }
    
}

void sendFile(int sockfd, char* contents)
{   
        int bytesSent = 0;
        FILE* tempFD = NULL;
        char* tempFile = contents;
        tempFile[strcspn(tempFile, "\n")] = 0;
        
        tempFD = fopen(tempFile, "r");
        //Transfer file while EOF has not been reached
        send(sockfd, tempFile, strlen(tempFile), 0);
        while(!(feof(tempFD)))
        {
            
            char* fileBuf[MAX_LEN] = {0};
            int n = fread(fileBuf, 1, MAX_LEN, tempFD);  
            bytesSent += n;          
            send(sockfd, fileBuf, n, 0);
        }     
         printf("File transfer complete. Sent %d bytes.\n", bytesSent); 
}
//Recv file and send to stdout
void recvFile(int sockfd)
{
    int bytesRecv = 0;
    char buff[MAX_LEN] = {0};   
    //Recv size of file to be sent
    while ((bytesRecv = recv(sockfd, buff, MAX_LEN, 0) > 0))
    {
        write(1, buff, MAX_LEN);
    }
    write(1, "\n", 1);
}
