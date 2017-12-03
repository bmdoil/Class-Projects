#include "fencrypt.h"



int main(int argc, char* argv[])
{
    if (argc < 2) {fprintf(stderr,"USAGE: %s [listening port]\n", argv[0]); exit(1); }

    char* handshake = "8T9GS1"; //Verify connection to otp_dec  
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
                            //fprintf(stderr, "Connection with otp_enc rejected: otp_enc cannot use otp_dec_d\n");
                            close(sock);
                            close(sockFD);
                            exit(2);
                    }
                else
                    {                      
                        //If handshake success, continue with send/recv
                        //Setup buffers
                        char ciphBuf[MAX_SIZE];
                        char keyBuf[MAX_SIZE];
                        char decrypted[MAX_SIZE];

                        memset(ciphBuf, '\0', sizeof(ciphBuf));
                        memset(keyBuf, '\0', sizeof(keyBuf));
                        memset(decrypted, '\0', sizeof(decrypted));
                        

                        //Get cipher from client
                        recvFile(sockFD, 0, ciphBuf);
                        //printf("ciphBuf: %s\n", ciphBuf);               
                        send(sockFD, "C transfer: good\n", 18, 0); //Send ack

                        //Get key from client
                        recvFile(sockFD, 0, keyBuf);              
                        //printf("keyBuf: %s\n", keyBuf);
                        send(sockFD, "K transfer: good\n", 17, 0); //Send ack

                        //Decrypt to plaintext 
                        decrypt(ciphBuf, keyBuf, decrypted);
                        //printf("decrypted: %s\n", decrypted);
                        //printf("%d\n", (int)strlen(decrypted));
                        memset(buffer, '\0', sizeof(buffer));
                        
                        sendFile(sockFD, decrypted); //Send plaintext to client
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

