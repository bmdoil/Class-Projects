#include "fencrypt.h"




int main(int argc, char* argv[])
{
    //argv[1] = plaintext
    //argv[2] = key
    //argv[3] = port
    
    if (argc < 4){fprintf(stderr, "USAGE: %s plaintext key port\n", argv[0]);exit(3);}
    char* handshake = "3Q9I6E"; //Used to verify connecting to otp_enc_d
    
    struct addrinfo addr, *addrInfo, *p;
    char* hostname = "localhost"; //Always localhost
    char* plainName = argv[1];
    char* keyName = argv[2];
    int sock;
    char buffer[MAX_SIZE] = {0};    
    char* port = argv[3];
    
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
        if ((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {perror("Socket Setup"); continue;}
        if (connect(sock, p->ai_addr, p->ai_addrlen) == -1) {fprintf(stderr, "Bad Port: %s\n", argv[3]); close(sock); exit(2);}
        break;
    }
    freeaddrinfo(addrInfo);
    if (p == NULL){perror("Connection failed\n"); exit(2);}
    memset(&buffer, '\0', sizeof(buffer));

    //Send handshake
    int checkConn = send(sock, handshake, strlen(handshake), 0);
    if (checkConn == -1) {perror("Handshake Error"); close(sock); exit(2);}
    
    if (recv(sock, buffer, sizeof(buffer), 0) < 0) {perror("Data recv error"); close(sock); exit(2);}
    
    if (strcmp(buffer, handshake) != 0) //If send and recv success, check if response = handshake, if no exit
    {
        fprintf(stderr, "Connection with otp_dec_d rejected: otp_enc cannot use otp_dec_d\n");
        close(sock);
        
        exit(2);
    }
    

   //Sets up and parses plaintext contents prior to sending
    char* plainBuf = NULL;
    long plainLen;
    FILE* plainFD = fopen(plainName, "r");
    if (plainFD == NULL)
    {
        perror("Error opening plaintext file.");
    }  
    else{
        fseek(plainFD, 0, SEEK_END); //find size of file
        plainLen = ftell(plainFD);
        fseek(plainFD, 0, SEEK_SET); //set seek to beginning
        plainBuf = (char*)calloc((plainLen + 1), sizeof(char)); //alloc memory and 0 it out
        if (plainBuf)
        {
            //memset(plainBuf, '\0', strlen(plainBuf));
            fread(plainBuf, 1, plainLen, plainFD); //read into buffer and replace ending newline with null char
            plainBuf[strcspn(plainBuf, "\n")] = '\0';
        }    
    fclose(plainFD);
    }
    
    //Sets up and parses plaintext contents prior to sending
    char* keyBuf = NULL;
    long keyLen;
    FILE* keyFD = fopen(keyName, "r");
    if (keyFD == NULL)
    {
        perror("Error opening plaintext file.");
    }  
    else{
        fseek(keyFD, 0, SEEK_END); //find size of file
        keyLen = ftell(keyFD);
        fseek(keyFD, 0, SEEK_SET); //set seek to beginning
        keyBuf = (char*)calloc((keyLen + 1), sizeof(char)); //alloc memory and 0 it out
        if (keyBuf)
        {
           
            memset(keyBuf, '\0', strlen(keyBuf));
            fread(keyBuf, 1, keyLen, keyFD); //read into buffer and replace ending newline with null char
            keyBuf[strcspn(keyBuf, "\n")] = '\0';    
        }
   
    fclose(keyFD);
    }

    if (strlen(plainBuf) > strlen(keyBuf)) //Can't continue if key shorter
    {
        fprintf(stderr, "Error: Key shorter than plaintext\n");
        exit(1);
    }

    //Check for invalid chars
    validateContents(plainBuf, plainName); 
    validateContents(keyBuf, keyName);    

    //Send plaintext to server. Recv requests are to ensure sends dont bleed together. Also used for debugging
    sendFile(sock, plainBuf);    
    if (recv(sock, buffer, sizeof(buffer), 0) < 0) {perror("Data recv error"); close(sock); exit(2);}
    //printf("%s", buffer);

    //Send key to server
    memset(buffer, '\0', sizeof(buffer));
    sendFile(sock, keyBuf);    
    if (recv(sock, buffer, sizeof(buffer), 0) < 0) {perror("Data recv error"); close(sock); exit(2);}
    //printf("%s", buffer);

    char ciphertext[sizeof(plainLen)];
    //Receive cipher from server and print to stdout         
    recvFile(sock, 1, ciphertext);
    if (send(sock, "C transfer: good", 17, 0) < 0) {perror("Data recv error"); close(sock); exit(2);}
    free(plainBuf);
    free(keyBuf);
    return 0;    
}
