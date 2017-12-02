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

off_t fsize(const char *filename);
void recvFile(int sockfd, off_t size, char* contents, int flag);
void sendFile(int sockfd, off_t size, char* fCont);
void crypto(char* cCont, char* kCont, off_t cSize, off_t kSize, char* res);

int main(int argc, char* argv[])
{
    if (argc < 2) {fprintf(stderr,"USAGE: %s [listening port]\n", argv[0]); exit(1); }

    char* handshake = "8T9GS1";
    char buffer[MAX_LEN];
    struct addrinfo addr, *addrInfo, *p;
    char* hostname = "localhost";    
    char* port = argv[1];   
    socklen_t addr_size;
    struct sockaddr_in clientAddr;
    
    
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
    //printf("Listening on socket: %s:%s\n", hostname, argv[1]);
    while (1)
    {
        addr_size = sizeof(clientAddr);
        
        sockFD = accept(sock, (struct sockaddr *)&clientAddr, &addr_size);
        if (sockFD < 0) {continue;} //Keep listening
        //printf("Connection accepted.\n");
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
                        off_t cSize = 0;
                        off_t kSize = 0;
                        
                        memset(&buffer, '\0', sizeof(buffer));
                        fflush(stdout);
                        recv(sockFD, &cSize, sizeof(cSize), 0);
                        //printf("%d\n", (int)cSize);
                        fflush(stdout);       
                        recv(sockFD, &kSize, sizeof(kSize), 0);
                        //printf("%d\n", (int)kSize);

                        char* cfileContents = malloc(sizeof(char)*cSize);
                        char* kfileContents = malloc(sizeof(char)*kSize);
                        char* decrypted = malloc(sizeof(char)*cSize);
                        
                        recvFile(sockFD, cSize, cfileContents, 0);                        
                        //printf("%s\n", cfileContents);

                        send(sockFD, "PT transfer: good\n", 18, 0);
                        
                        recvFile(sockFD, kSize, kfileContents, 0); 
                                            
                        //printf("%s\n", kfileContents);
                        send(sockFD, "K transfer: good\n", 17, 0);

                        crypto(cfileContents, kfileContents, cSize, kSize, decrypted);
                        //printf("%s\n", decrypted);
                        //printf("%d\n", (int)strlen(decrypted));
                        sendFile(sockFD, cSize, decrypted);
                        //if (recv(sockFD, buffer, sizeof(buffer), 0) < 0) {perror("Data recv error"); exit(2);}

                        free(cfileContents);
                        free(kfileContents);
                        free(decrypted);
                        
                    }
            default:
                close(sockFD);
                waitpid(-1, &status, WNOHANG);
        
        }
        
    }
  
   return 0;
}


void sendFile(int sockfd, off_t size, char* fCont)
{   
    fflush(stdout);
    int bytesSent = 0;
    int n;
    
        //Transfer file while EOF has not been reached
       
    while (bytesSent < size)
    {   n = send(sockfd, fCont, size, 0);
        bytesSent += n;
    }
    //printf("%d bytes sent\n", bytesSent);             
}
//Recv file
void recvFile(int sockfd, off_t size, char* contents, int flag)
{
    
    int bytesRecv = 0;
    char buff[MAX_LEN] = {0};
    int n = 0;
    if (flag == 1) 
    {
        // Recv file and Write to stdout
        while (bytesRecv < size)
        {
            write(STDOUT_FILENO, buff, MAX_LEN);
            bytesRecv += n;            
        }        
    }
    else
    {   //Recv file and write to FILE* output
        while (bytesRecv < size)
        {
            n = recv(sockfd, contents, MAX_LEN, 0);
            bytesRecv += n;
        }        
    }
    //printf("%d bytes recvd\n", bytesRecv);
    //printf("Received file: %s\n", recvdFile);
    
}
off_t fsize(const char* filename)
{
    struct stat st;

    if(stat(filename, &st) == 0)
        return st.st_size;
    fprintf(stderr, "Can't determine size of %s:\n", filename);
        return -1;
}


void crypto(char* cCont, char* kCont, off_t cSize, off_t kSize, char* res)
{
    int pEnc[MAX_SIZE] = {0};
    int kEnc[MAX_SIZE] = {0};
    int key[MAX_SIZE] = {0};
    int cipher[MAX_SIZE] = {0};
    int i;
    for (i = 0; i < cSize; i++)
    if (cCont[i] == ' ')
        pEnc[i] = 26;
    else
    {
        pEnc[i] = (cCont[i] - 65);
    }
    
    for (i = 0; i < kSize; i++)
    {
        if (kCont[i] == ' ')
        {
            kEnc[i] = 26;
        }
        else
        {
            kEnc[i] = (kCont[i] - 65);
        }
    }

    for (i = 0; i < (cSize - 1); i++) //Ignore newline
    {
        key[i] = (pEnc[i] + kEnc[i]);
        cipher[i] = key[i] % 27;
        if (cipher[i] == 26)
        {
            res[i] = ' ';
        }
        else
        {
            res[i] = cipher[i] + 65;
        }

    }
    //strcat(&res[cSize - 1], "\n"); //Append newline 
}
