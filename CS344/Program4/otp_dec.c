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
#define MAX_SIZE 1000000

void parseFiles(int sock, char* pName, char* kName, char* seed);
void validateContents(char* contents, int size, char* seed, char* filename);
void sendFile(int sockfd, int size, char* fCont);
void recvFile(int sockfd, int size, char* contents, int flag);
char buffer[MAX_SIZE];

int main(int argc, char* argv[])
{
    //argv[1] = plaintext
    //argv[2] = key
    //argv[3] = port
    
    if (argc < 4){fprintf(stderr, "USAGE: %s plaintext key port\n", argv[0]);exit(3);}
    char* handshake = "8T9GS1";
    
    struct addrinfo addr, *addrInfo, *p;
    char* plainName = argv[1];
    char* keyName = argv[2];
    char* hostname = "localhost";
    int sock;
  

    
    char* seed = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    char* port = argv[3];
    
        
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
        if (connect(sock, p->ai_addr, p->ai_addrlen) == -1) {fprintf(stderr, "Bad Port: %s\n", argv[3]); close(sock); exit(2);}
        break;
    }
    freeaddrinfo(addrInfo);
    if (p == NULL){perror("Connection failed\n"); exit(2);}
    memset(&buffer, '\0', sizeof(buffer));

    
    int checkConn = send(sock, handshake, strlen(handshake), 0);
    if (checkConn == -1) {perror("Handshake Error"); close(sock); exit(2);}
    
    if (recv(sock, buffer, sizeof(buffer), 0) < 0) {perror("Data recv error"); close(sock); exit(2);}
    
    if (strcmp(buffer, handshake) != 0)
    {
        fprintf(stderr, "Connection with %s:%s rejected. Closing connection.\n", hostname, argv[3]);
        close(sock);
        
        exit(2);
    }
    

    parseFiles(sock, plainName, keyName, seed);

    return 0;    
}
void parseFiles(int sock, char* pName, char* kName, char* seed)
{
    char plainBuf[MAX_SIZE];
    memset(plainBuf, '\0', MAX_SIZE);
    char keyBuf[MAX_SIZE];
    memset(keyBuf, '\0', MAX_SIZE);
    int pSize;
    int kSize;   
     
    
    //If plaintext size > key size, exit 1.
    if (pSize > kSize) {fprintf(stderr, "Error: KEY '%s' length must be longer than PLAINTEXT '%s' length.\n", kName, pName); exit(1);}
     else{
        kSize = pSize;
    }
    int pFile = open(pName, O_RDONLY);
    int kFile = open(kName, O_RDONLY);
    read(pFile, plainBuf, sizeof(plainBuf));
    pSize = strlen(plainBuf);

    read(kFile, keyBuf, sizeof(keyBuf));
    kSize = strlen(keyBuf);

    send(sock, &pSize, sizeof(pSize), 0); //Send pfile size
    send(sock, &kSize, sizeof(kSize), 0); //Send kfilesize
    
    validateContents(plainBuf, pSize, seed, pName);
    validateContents(keyBuf, kSize, seed, kName);
    //printf("%s", pfileContents);
    memset(&buffer, '\0', sizeof(buffer));
    sendFile(sock, pSize, plainBuf);    
    if (recv(sock, buffer, sizeof(buffer), 0) < 0) {perror("Data recv error"); close(sock); exit(2);}
    //printf("%s", buffer);
    memset(&buffer, '\0', sizeof(buffer));
    sendFile(sock, kSize, keyBuf);    
    if (recv(sock, buffer, sizeof(buffer), 0) < 0) {perror("Data recv error"); close(sock); exit(2);}
    //printf("%s", buffer);
    memset(&buffer, '\0', sizeof(buffer));
    recvFile(sock, pSize, buffer, 1);
    fflush(stdout);
    //send(sock, "E transfer: good\n", 17, 0);

    close(pFile);
    close(kFile);
    
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

void sendFile(int sockfd, int size, char* fCont)
{   
    fflush(stdout);
    int bytesSent = 0;
    int n;

    while (bytesSent < size)
    {   
        n = send(sockfd, &fCont, MAX_LEN, 0);
        bytesSent += n;
    }
    //printf("%d bytes sent\n", bytesSent);             
}
//Recv file
void recvFile(int sockfd, int size, char* contents, int flag)
{
    fflush(stdout);
    int bytesRecv = 0;
    char buff[MAX_LEN] = {0};
    int n = 0;
    if (flag == 1) 
    {
        // Recv file and Write to stdout
        while (bytesRecv < size)
        {
            n = recv(sockfd, buff, MAX_LEN, 0);
            write(STDOUT_FILENO, buff, MAX_LEN);
            bytesRecv += n;            
        }
        //write(STDOUT_FILENO, "\n", 1); 
        printf("%s", "\n");      
    }
    else
    {   
        while (bytesRecv < size)
        {
            n = recv(sockfd, &contents, MAX_LEN, 0);
            bytesRecv += n;
        }        
    }
    //printf("%d bytes recvd\n", bytesRecv);
    //printf("Received file: %s\n", recvdFile);
    
}

