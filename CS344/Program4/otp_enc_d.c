
#include "fencrypt.h"


int main(int argc, char* argv[])
{
    if (argc < 2) {fprintf(stderr,"USAGE: %s [listening port]\n", argv[0]); exit(1); }

    char* handshake = "3Q9I6E"; //Verify connection to otp_enc
    char buffer[MAX_SIZE] = {0};
    struct addrinfo addr, *addrInfo, *p;
    char* hostname = "localhost";    
    char* port = argv[1];   
    socklen_t addr_size;
    struct sockaddr_in clientAddr;   
    int sock, sockFD, status;
    int yes = 1;
    pid_t spawnPid = -5;

    //Network code modified from Beej's networking guide.
    //REF: http://beej.us/guide/bgnet  
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
        if ((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {perror("server: socket"); continue;}
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {perror("setsockopt"); exit(2);}
        if (bind(sock, p->ai_addr, p->ai_addrlen) == -1) {close(sock); perror("server: bind"); continue;}
        break;
    }
    if (p == NULL) {fprintf(stderr, "server failed to bind\n"); exit(2);}
    freeaddrinfo(addrInfo);
    if (listen(sock, 5) == -1) {perror("listen"); exit(1);} //Allow up to 5 connections at once
    printf("Listening on socket: %s:%s\n", hostname, argv[1]);
    while (1) //Loop while waiting on connections
    {
        addr_size = sizeof(clientAddr);
        
        sockFD = accept(sock, (struct sockaddr *)&clientAddr, &addr_size);
        if (sockFD < 0) {continue;} //Keep listening
        //printf("Connection accepted.\n");
        switch (spawnPid = fork()) //When accepted, spawn child
        {
            case -1:
                perror("Server failed to create fork.\n");
                break;
            case 0:
                close(sock); //close listen socket
                memset(buffer, '\0', sizeof(buffer));
                //Handshake
                int checkConn = recv(sockFD, buffer, sizeof(buffer), 0);
                if (checkConn == 1) {perror("Handshake error");close(sockFD); exit(2);}       
                send(sockFD, handshake, strlen(handshake), 0);  
                if (strcmp(buffer, handshake) != 0)
                    {
                            //fprintf(stderr, "Connection with otp_dec rejected: otp_dec cannot use otp_enc_d\n");
                            close(sock);
                            close(sockFD);
                            exit(2);
                    }
                else
                    { 
                                               
                        //If handshake success, continue with send/recv
                        //Setup buffers
                        char plainBuf[MAX_SIZE];
                        char keyBuf[MAX_SIZE];
                        char encrypted[MAX_SIZE];

                        memset(plainBuf, '\0', sizeof(plainBuf));
                        memset(keyBuf, '\0', sizeof(keyBuf));
                        memset(encrypted, '\0', sizeof(encrypted));

                        //Recv plaintext from client
                        recvFile(sockFD, 0, plainBuf);                        
                        //printf("plainBuf: %s\n", plainBuf);
                        send(sockFD, "PT transfer: good\n", 18, 0); //Send ack

                        //Recv key from client
                        recvFile(sockFD, 0, keyBuf);                                             
                        //printf("keyBuf: %s\n", keyBuf);
                        send(sockFD, "K transfer: good\n", 17, 0); //Send ack

                        //Encrypt to ciphertext
                        encrypt(plainBuf, keyBuf, encrypted); 
                        //printf("Encrypted: %s\n", encrypted);
                        //printf("%d\n", (int)strlen(encrypted));
                        
                        memset(buffer, '\0', sizeof(buffer));
                        sendFile(sockFD, encrypted); //Send encrypted file to client
                        if (recv(sockFD, buffer, sizeof(buffer), 0) < 0) {perror("Data recv error"); exit(2);}

                      
                        exit(0);
                        break;
                        
                    }
            default: //Main process
                close(sockFD);
                waitpid(-1, &status, WNOHANG);
        
        }
        
    }
    close(sock);
    return 0;
}

