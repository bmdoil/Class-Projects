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
void recvFile(int sockfd, FILE* output, int newline);
void encrypt(FILE* plainF, FILE* keyF, char* seed, char* res);

int main(int argc, char* argv[])
{
    if (argc < 2) {fprintf(stderr,"USAGE: %s [listening port]\n", argv[0]); exit(1); }

    char* handshake = "3Q9I6E";
    char buffer[MAX_LEN];
    struct addrinfo addr, *addrInfo, *p;
    char* hostname = "localhost";
    char* seed = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    char* port = argv[1];
    char* result;
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
                        //recvFile(sockFD, NULL, 1); //write to stdout and add newline
                        // Test
                        
                        FILE* plainFD = fopen("plainTemp", "w+");
                        FILE* keyFD = fopen("keyTemp", "w+");
                        recvFile(sockFD, plainFD, 1);
                        recvFile(sockFD, keyFD, 1);
                        encrypt(plainFD, keyFD, seed, result);
                        printf("%s", result);
                        //Endtest
                        remove("plainTemp");
                        remove("keyTemp");
                        free(result);
                        
                    }
            default:
                close(sockFD);
                waitpid(-1, &status, WNOHANG);
        
        }
        
    }
  
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
//Recv file
void recvFile(int sockfd, FILE* output, int newline)
{
    int bytesRecv = 0;
    char buff[MAX_LEN] = {0};
    if (output == NULL) 
    {
        // Recv file and Write to stdout
        while ((bytesRecv = recv(sockfd, buff, MAX_LEN, 0) > 0))
        {
            write(STDOUT_FILENO, buff, MAX_LEN);
        }
        if (newline == 1)
        {
            write(STDOUT_FILENO, "\n", 1);
        }
    }
    else
    {   //Recv file and write to FILE* output
        while ((bytesRecv = recv(sockfd, buff, MAX_LEN, 0) > 0))
        {
            fwrite(buff, MAX_LEN, MAX_LEN, output);
        }
    }
}


void encrypt(FILE* plainF, FILE* keyF, char* seed, char* res)
{
    char* pfileContents;
    char* kfileContents;
    char* result;
    int pSize, kSize;
    //char* encrypted;
    //char* numVal;
    int i, j;
    //Get file sizes
    fseek(plainF, 0L, SEEK_END);
    pSize = ftell(plainF);
    rewind(plainF);
    
    fseek(keyF, 0L, SEEK_END);
    kSize = ftell(keyF);
    rewind(keyF);
    
    pfileContents = malloc(sizeof(char)*pSize);
    kfileContents = malloc(sizeof(char)*kSize);
    result = malloc(sizeof(char)*pSize);
    //numVal = malloc(sizeof(char)* strlen(seed));
    //Read file stream into char* 
    fread(pfileContents, pSize, pSize, plainF);
    pfileContents[strcspn(pfileContents, "\n")] = 0;
    fread(kfileContents, kSize, kSize, keyF);
    kfileContents[strcspn(kfileContents, "\n")] = 0;
    
    //Convert plaintext to number 0 - 27 based on seed 
    for (i = 0; i < pSize; i++)
    {
        for (j = 0; j < strlen(seed); j++)
        {
            if (pfileContents[i] == seed[j])
            {
               snprintf(&pfileContents[i], 1, "%d", j);
            }
        }
    }
    //Convert key to number 0 - 27 based on seed
    for (i = 0; i < kSize; i++)
    {
        for (j = 0; j < strlen(seed); j++)
        {
            if (kfileContents[i] == seed[j])
            {
                snprintf(&pfileContents[i], 1, "%d", j);
            }
        }
    }
    
    for (i = 0; i < pSize; i++)
    {
        int temp = (pfileContents[i] + kfileContents[i]) % 27;
        result[i] = seed[temp];  
    }
}
