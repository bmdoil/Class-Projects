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

void validateContents(char* contents, int size, char* seed, char* filename);
void sendFile(int sockfd, char* contents);
void recvFile(int sockfd);

int main(int argc, char* argv[])
{
    //argv[1] = plaintext
    //argv[2] = key
    //argv[3] = port
    
    if (argc < 4){fprintf(stderr, "USAGE: %s plaintext key port\n", argv[0]);exit(3);
    }
    char* handshake = "3Q9I6E";
    char buffer[MAX_LEN];
    struct addrinfo addr, *addrInfo, *p;
    char* plainName = argv[1];
    char* keyName = argv[2];
    char* hostname = "localhost";
    FILE* plainFile;
    FILE* keyFile;
    char* pfileContents = NULL;
    char* kfileContents = NULL;
    char* seed = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    char* port = NULL;
    //Convert port
    inet_pton(AF_INET, argv[3], port);
    int pSize = 0;
    int kSize = 0;
    int sock, sockFD;
    int yes = 1;
    //int i, j;
    
    
    plainFile = fopen(plainName, "r");
    if (plainFile < 0) {fprintf(stderr, "Error opening file: %s", plainName); exit(3);}
    
    keyFile = fopen(keyName, "r");
    if (keyFile < 0) {fprintf(stderr, "Error opening file: %s", keyName); exit(3);}
    
    //Get file sizes
    fseek(plainFile, 0L, SEEK_END);
    pSize = ftell(plainFile);
    rewind(plainFile);
    
    fseek(keyFile, 0L, SEEK_END);
    kSize = ftell(keyFile);
    rewind(keyFile);
    //printf("pSize: %d\nfSize: %d\n", pSize, kSize);
    //If plaintext size > key size, exit 1.
    if (pSize > kSize) {fprintf(stderr, "Error: KEY '%s' length must be longer than PLAINTEXT '%s' length.\n", keyName, plainName); exit(1);}
    
    pfileContents = malloc(sizeof(char*)*pSize);
    kfileContents = malloc(sizeof(char*)*kSize);
    fread(pfileContents, pSize, pSize, plainFile);
    
    fread(kfileContents, kSize, kSize, keyFile);
    
    validateContents(pfileContents, pSize, seed, plainName);
    validateContents(kfileContents, kSize, seed, keyName);
    
    memset((char*)&addr, '\0', sizeof(addr));
    addr.ai_family = AF_INET;
    addr.ai_socktype = SOCK_STREAM;
    addr.ai_flags = AI_PASSIVE;
    addr.ai_protocol = 0;
    
    if((getaddrinfo(hostname, port, &addr, &addrInfo)) != 0){fprintf(stderr, "Error creating socket %s\n",argv[3]); exit(2);}
    
    //Modified from Beej's guide to establish a connection
    //REF: http://beej.us/guide/bgnet/output/html/multipage/clientserver.html  
    for (p = addrInfo; p != NULL; p = p->ai_next)
    {
        if ((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {perror("Socket Setup"); continue;}
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {perror("setsockopt"); close(sock); exit(2);}
        if ((sockFD = connect(sock, p->ai_addr, p->ai_addrlen)) == -1) {fprintf(stderr, "Bad Port: %s\n", argv[3]); close(sock); exit(2);}
        break;
    }
    freeaddrinfo(addrInfo);
    memset(&buffer, '\0', sizeof(buffer));

    if (send(sockFD, handshake, strlen(handshake), 0) < 0) {perror("Handshake Error"); close(sock); close(sockFD); exit(2);}
    if (recv(sockFD, buffer, sizeof(buffer), 0) < 0) {perror("Data recv error"); close(sock); close(sockFD); exit(2);}
    if (strcmp(buffer, handshake) != 0)
    {
        fprintf(stderr, "Connection with %s:%s rejected. Closing connection.\n", hostname, argv[3]);
        close(sock);
        close(sockFD);
        exit(2);
    }

    sendFile(sockFD, pfileContents);   
    recvFile(sockFD)
    //printf("EOF\n");
    free(pfileContents);
    free(kfileContents);   
    return 0;    
}

void validateContents(char* contents, int size, char* seed, char* filename)
{
    int i, j;
    int good = 0;
    
    for (i = 0; i < size - 1; i++)
    {
        good = 0;
        for (j = 0; j < strlen(seed); j++)
        {
            if (contents[i] == seed[j])
            {
                good = 1;
            }
        }
        if (good == 0)
        {
            fprintf(stderr, "Error: Invalid character in %s: '%c' at location %d\n", filename, contents[i], i);
            exit(1);
        }
        else continue;
    }
}
//Strip newline
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
