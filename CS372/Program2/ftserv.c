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
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <signal.h>
#include <dirent.h>

#define MAX_LEN 1024

//Globals
int getList = 0;
int getFile = 0;

void sendDir(int sockfd);
void sendFile(int sockfd, char* file);

int main(int argc, char *argv[])
{
    /*The framework for creating the server is adapted from OSU CSS 344 - Brewster's server.c
    REF: https://oregonstate.instructure.com/courses/1648339/pages/block-4
    Lecture 4.3 - Network Servers
    And also Beej's Networking Guide http://beej.us/guide/bgnet/output/html/multipage/clientserver.html
    */
    int controlSock, controlFD, dataSock, dataFD;
   
    int yes = 1;
    int result = -5;
    struct addrinfo servAddr, *servInfo, *dataInfo, *p;
    struct sockaddr_in clientAddr;
    socklen_t addr_size, cname_size;
    char buffer[MAX_LEN];
    char dataPort[MAX_LEN];
    char clientName[MAX_LEN];
    char fileName[MAX_LEN];

    
      
    if (argc < 2) {fprintf(stderr,"USAGE: %s [hostname] [port]\n", argv[0]); exit(1); }

    //Set up address struct
    //REF: http://beej.us/guide/bgnet/output/html/multipage/syscalls.html#getaddrinfo
    memset((char *)&servAddr, '\0', sizeof(servAddr));
    servAddr.ai_family = AF_INET;
    servAddr.ai_socktype = SOCK_STREAM;
    servAddr.ai_flags = AI_PASSIVE;
    servAddr.ai_protocol = 0;

    if ((getaddrinfo(argv[1], argv[2], &servAddr, &servInfo)) != 0)
    {fprintf(stderr, "control conn getaddrinfo error: %s\n", gai_strerror(result)); exit(1);}

    //Loop through results of gettaddrinfo and bind to first valid one
    //REF: http://beej.us/guide/bgnet/output/html/multipage/clientserver.html
    for (p = servInfo; p != NULL; p = p->ai_next)
    {
        if ((controlSock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {perror("server: socket"); continue;}
        if (setsockopt(controlSock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {perror("setsockopt"); exit(1);}
        if (bind(controlSock, p->ai_addr, p->ai_addrlen) == -1) {close(controlSock); perror("server: bind"); continue;}
        break;
    }

    freeaddrinfo(servInfo);

    if (p == NULL) {fprintf(stderr, "server failed to bind\n"); exit(1);}
    //Waiting on client connection
    if (listen(controlSock, 1) == -1) {perror("listen"); exit(1);}

    printf("server: waiting for connections...\n");
    fflush(stdout);
    
    addr_size = sizeof(struct sockaddr_in);
    controlFD = accept(controlSock, (struct sockaddr *)&clientAddr, &addr_size);
    if (controlFD < 0) {perror("accept"); printf("error accepting connection"); close(controlSock); close(controlFD); exit(1);}
    //Receive and parse commands     
        
    printf("Control connection received from client\n");        
    memset(&buffer, '\0', sizeof(buffer));
    //Get data port
    result = recv(controlFD, dataPort, sizeof(dataPort), 0);
    printf("Data port: %s\n", dataPort);
    //Check port transfer status
    if (result < 0)
    {
        close(controlFD); 
        close(controlSock); 
        perror("conn read");
        fflush(stdout);            
        exit(1);
    }        
    else
    { 
        //Begin command transfer
        fflush(stdout);
        send(controlFD, "Port transfer: success", 23, 0);
        recv(controlFD, buffer, MAX_LEN, 0);
        printf("Command: %s\n", buffer);
        if ((strcmp(buffer, "-l") == 0))
        {   //Set list flag
            send(controlFD, "Command transfer: success", 27, 0);
            getList = 1;    
        }
        else if ((strcmp(buffer, "-g") == 0))
        {   //Set file flag and get the file name                     
            send(controlFD, "Command transfer: success", 27, 0);
            getFile = 1; 
            recv(controlFD, fileName, sizeof(fileName), 0);
            send(controlFD, "Filename transfer: good", 23, 0);
            printf("File transfer request received: %s\n", fileName);
                      
        }               
        else
        {   //Throw an error to client
            send(controlFD, "Error parsing commands.\n", 24, 0);
            printf("error parsing commands. quitting."); 
            close(controlFD);
            exit(1);
        }
                              
    }    
    //Prep data connection
    if ((getaddrinfo(argv[1], dataPort, &servAddr, &dataInfo)) != 0)
    {fprintf(stderr, "data conn getaddrinfo error: %s\n", gai_strerror(result)); exit(1);}
    //Modified from Beej's guide to establish a connection
    //REF: http://beej.us/guide/bgnet/output/html/multipage/clientserver.html   
    for (p = dataInfo; p != NULL; p = p->ai_next)
    {
        if ((dataSock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {perror("server: socket"); continue;}
        if ((dataFD = connect(dataSock, p->ai_addr, p->ai_addrlen)) == -1) {perror("data sock conn"); close(controlFD); close(dataSock); close(dataFD); exit(1);}
        break;
    }
    freeaddrinfo(dataInfo);

    if (p == NULL) {fprintf(stderr, "data connection failed\n"); exit(1);}
    //Used to print client name for data conn  
    cname_size = sizeof(clientName);
    addr_size = sizeof(clientAddr);
        
    getnameinfo((struct sockaddr*) &clientAddr, addr_size, clientName, cname_size, NULL, 0, 0);

    printf("Data connection received from client %s\n", clientName);
    //Only 1 will run depending on flags
    sendDir(dataSock);
    sendFile(dataSock, fileName);
        
    close(dataSock);
    close(controlSock);
    close(dataFD);
    
    return 0;
}

//List files in directory and send using socket conn. Adapted from:
//REF:https://stackoverflow.com/questions/3554120/open-directory-using-c
void sendDir(int dataSock)
{
    if (getList == 1)
    {   //Set up vars to parse directory and send over socket
        char currentDir[MAX_LEN] = "";
        char cwd[MAX_LEN];
        DIR* dir;
        struct dirent* entry;
        char nline[2] = "\n";

        getcwd(cwd, sizeof(cwd));
        printf("Directory: %s\n", cwd);
        //If dir can be opened
            if ((dir = opendir(cwd)) != NULL)
            {
                //Read dir contents
                while ((entry = readdir (dir)) != NULL)
                {
                    //Concat regular files in dir together, add newlines for formatting
                    if (entry->d_type == DT_REG)
                    {
                        strcat(currentDir, entry->d_name);
                        strcat(currentDir, nline);
                    }
                    
                }
                printf("List: \n%s\n", currentDir);
                closedir (dir);          
                
            }
        //Send it to client
        int checkConn = send(dataSock, currentDir, MAX_LEN, 0);
        if (checkConn == -1){perror("data con send"); exit(1);}
    }
}
//Send file using socket conn. Adapted from:
//REF: https://stackoverflow.com/questions/11952898/c-send-and-receive-file
//REF: http://beej.us/guide/bgnet/output/html/multipage/advanced.html 7.3 Handling Partial send()s
void sendFile(int sockfd, char* file)
{   
    int bytesSent = 0;
    if (getFile == 1)
    {
        FILE* fd = NULL;
       
        fd = fopen(file, "r");
        //If file not in directory
        if (fd <= 0)
        {
            send(sockfd, "NOFILE", 6, 0);
            perror("File not found\n");
            printf("Quitting.\n");
            return;           
        }
        //Transfer file while EOF has not been reached
        send(sockfd, file, strlen(file), 0);
        while(!(feof(fd)))
        {
            
            char* fileBuf[MAX_LEN] = {0};
            int n = fread(fileBuf, 1, MAX_LEN, fd);  
            bytesSent += n;          
            send(sockfd, fileBuf, n, 0);
        }     
         printf("File transfer complete. Sent %d bytes.\n", bytesSent);     
    }  
      
}




