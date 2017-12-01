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
void recvFile(int sockfd, int outputfd, int newline);

int main(int argc, char* argv[])
{
    if (argc < 2) {fprintf(stderr,"USAGE: %s [listening port]\n", argv[0]); exit(1); }

    char* handshake = "3Q9I6E";
    char buffer[MAX_LEN];
    struct addrinfo addr, *addrInfo, *p;
    char* hostname = "localhost";
    
    char* port = argv[1];
    socklen_t addr_size;
    struct sockaddr_in clientAddr;
    //Convert port
    
    int sock, sockFD, status;
    int yes = 1;
    pid_t spawnPid = -5;

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
    printf("Listening on socket: %s:%s\n", hostname, argv[1]);
    while (1)
    {
        addr_size = sizeof(clientAddr);
        //int result = 0;
        sockFD = accept(sock, (struct sockaddr *)&clientAddr, &addr_size);
        if (sockFD < 0) {printf("error accepting connection"); close(sockFD);close(sock); exit(2);}
        printf("Connection accepted.\n");
        switch (spawnPid = fork())
        {
            case -1:
                perror("Server failed to create fork.\n");
                break;
            case 0:
                close(sock);
                memset(&buffer, '\0', sizeof(buffer));
                int checkConn = recv(sockFD, buffer, sizeof(buffer), 0);
                if (checkConn == 1) {perror("Handshake error");close(sockFD); exit(2);}       
                send(sockFD, handshake, strlen(handshake), 0);  
                if (strcmp(buffer, handshake) != 0)
                    {
                            fprintf(stderr, "Connection with %s:%s rejected. Closing connection.\n", hostname, argv[3]);
                            close(sock);
                            close(sockFD);
                            exit(2);
                    }
                else
                    { 
                        memset(&buffer, '\0', sizeof(buffer));
                        recv(sockFD, buffer, sizeof(buffer), 0);
                        printf("%s", buffer);
                        send(sockFD, "Begin upload", 14, 0);
                        //FILE* temp = open("recvd", 'w+');
                        recvFile(sockFD, STDOUT_FILENO, 1); //write to stdout
                        //close(temp);
                    }
            default:
                close(sockFD);
                waitpid(-1, &status, WNOHANG);
        
        }
        
    }
    

    /*while (1)
    {
        addr_size = sizeof(clientAddr);
        int result = 0;
        
        sockFD = accept(sock, (struct sockaddr *)&clientAddr, &addr_size);
        if (sockFD < 0) {printf("error accepting connection"); close(sockFD);close(sock); exit(2);}
        printf("Connection accepted.\n");
        switch (spawnPid = fork())
        {
            case -1:
                perror("Server failed to create fork.\n");
                break;
            case 0:              
            close(sock);
            memset(&buffer, '\0', sizeof(buffer));
            if ((recv(sockFD, buffer, strlen(handshake), 0)) < 0){perror("Handshake error");close(sockFD); exit(2);}
            printf("%s\n", buffer);
            send(sockFD, handshake, sizeof(handshake), 0);
            if (strcmp(buffer, handshake) == 0)
            {
                fprintf(stderr, "Connection with %s:%s rejected. Closing connection.\n", hostname, argv[3]);
                close(sock);
                close(sockFD);
                exit(2);
            }
            else
            {
               memset(&buffer, '\0', sizeof(buffer));
               recv(sockFD, buffer, sizeof(buffer), 0);
               printf("%s\n", buffer);
               send(sockFD, "Begin upload\n", 14, 0);
            }


        }
        else {close(sockFD); exit(0);}
        waitpid(-1, &status, WNOHANG);
    }  
    */
        
    return 0;
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
void recvFile(int sockfd, int outputfd, int newline)
{
    int bytesRecv = 0;
    char buff[MAX_LEN] = {0};   
    //Recv size of file to be sent
    while ((bytesRecv = recv(sockfd, buff, MAX_LEN, 0) > 0))
    {
        write(outputfd, buff, MAX_LEN);
    }
    if (newline == 1)
    {
        write(outputfd, "\n", 1);
    }
    
    //printf("\n");
}
