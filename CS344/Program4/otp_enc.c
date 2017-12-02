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

//Ref: https://stackoverflow.com/questions/8236/how-do-you-determine-the-size-of-a-file-in-c
off_t fsize(const char *filename);

void validateContents(char* contents, int size, char* seed, char* filename);
void sendFile(int sockfd, char* file);
void recvFile(int sockfd, char* contents, int flag);

int main(int argc, char* argv[])
{
    //argv[1] = plaintext
    //argv[2] = key
    //argv[3] = port
    
    if (argc < 4){fprintf(stderr, "USAGE: %s plaintext key port\n", argv[0]);exit(3);}
    char* handshake = "3Q9I6E";
    char buffer[MAX_LEN];
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
    send(sock, &pSize, sizeof(pSize), 0); //Send pfile size
    send(sock, &kSize, sizeof(kSize), 0); //Send kfilesize

    parseFiles(sock, plainName, keyName, seed);
    
    return 0;    
}
void parseFiles(int sockFD, char* pName, char* kName, char* seed)
{
    off_t pSize = 0;
    off_t kSize = 0;
    
    pSize = fsize(pName);
    kSize = fsize(kName);  
    FILE* pFile = fopen(pName, "r");
    FILE* kFile = fopen(kName, "r");
    //If plaintext size > key size, exit 1.
    if (pSize > kSize) {fprintf(stderr, "Error: KEY '%s' length must be longer than PLAINTEXT '%s' length.\n", keyName, plainName); exit(1);}
    
    char* pfileContents = malloc(sizeof(char)*pSize);
    char* kfileContents = malloc(sizeof(char)*kSize);

    fread(pfileContents, 1, pSize, pFile);
    fread(kfileContents, 1, kSize, kFile);
    
    validateContents(pfileContents, pSize, seed, plainName);
    validateContents(kfileContents, kSize, seed, keyName);

    sendFile(sockFD, pSize, pFile, pfileContents);
    sendFile(sockFD, kSize, kFile, kfileContents);
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

void sendFile(int sockfd, off_t size, FILE* file, char* fileName);
{   
    int bytesSent = 0;

        //Transfer file while EOF has not been reached
       
    while(!(feof(file)))
    {
            
        char* fileBuf[MAX_LEN] = {0};
        int n = fread(fileBuf, 1, size, file);  
        bytesSent += n;          
        send(sockfd, fileBuf, n, 0);
    }     
    //printf("File transfer complete. Sent %d bytes.\n", bytesSent);     
     
      
}
//Recv file
char* recvFile(int sockfd, off_t size, int flag)
{
    char* recvdFile = malloc(sizeof(char*)*size);
    int bytesRecv = 0;
    char buff[MAX_LEN] = {0};
    int n = 0;
    if (flag == 1) 
    {
        // Recv file and Write to stdout
        while ((n = recv(sockfd, buff, MAX_LEN, 0) > 0))
        {
            write(STDOUT_FILENO, buff, MAX_LEN);
            bytesRecv += n;
            return NULL;
        }        
    }
    else
    {   //Recv file and write to FILE* output
        while ((n = recv(sockfd, buff, MAX_LEN, 0 ) > 0)
        {
            write(recvdFile, buff, MAX_LEN);
            bytesRecv += n;
        }        
    }
    return recvdFile;
}
off_t fsize(const char* filename)
{
    struct stat st;

    if(stat(filename, &st) == 0)
        return st.st_size;
    fprintf(stderr, "Can't determine size of %s: %s\n", filename, strerror(errno));
        return -1;
}

