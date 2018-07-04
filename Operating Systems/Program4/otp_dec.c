#include "fencrypt.h"




int main(int argc, char* argv[])
{
    //argv[1] = cipertext
    //argv[2] = key
    //argv[3] = port
    
    if (argc < 4){fprintf(stderr, "USAGE: %s ciphertext key port\n", argv[0]);exit(3);}
    char* handshake = "8T9GS1"; //Used to verify connecting to otp_dec_d
    
    struct addrinfo addr, *addrInfo, *p;
    char* hostname = "localhost"; //Always localhost
    char* cipherName = argv[1];
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
    memset(buffer, '\0', sizeof(buffer));

    //Send handshake
    int checkConn = send(sock, handshake, strlen(handshake), 0);
    if (checkConn == -1) {perror("Handshake Error"); close(sock); exit(2);}
    
    if (recv(sock, buffer, sizeof(buffer), 0) < 0) {perror("Data recv error"); close(sock); exit(2);}
    
    if (strcmp(buffer, handshake) != 0)
    {
        fprintf(stderr, "Connection with otp_enc_d rejected: otp_dec cannot use otp_enc_d\n");
        close(sock);
        
        exit(2);
    }
    
    //Sets up and parses ciphertext prior to sending
    char* cipherBuf = NULL;
    long cipherLen;
    FILE* cipherFD = fopen(cipherName, "r");
    if (cipherFD == NULL)
    {
        perror("Error opening plaintext file.");
    }  
    else{
        fseek(cipherFD, 0, SEEK_END); //find size of file
        cipherLen = ftell(cipherFD);
        fseek(cipherFD, 0, SEEK_SET); //set seek to beginning
        cipherBuf = (char*)calloc((cipherLen + 1), sizeof(char)); //alloc memory and 0 it out
        if (cipherBuf)
        {
           
            //memset(cipherBuf, '\0', strlen(cipherBuf));
            fread(cipherBuf, 1, cipherLen, cipherFD); //read into buffer and replace ending newline with null char
            cipherBuf[strcspn(cipherBuf, "\n")] = '\0';
        }
    
    fclose(cipherFD);
    }

    //Sets up and parses plaintext contents prior to sending
    char* keyBuf = NULL;
    long keyLen;
    FILE* keyFD = fopen(keyName, "r");
    if (keyFD == NULL)
    {
        perror("Error opening ciphertext file.");
    }  
    else{
        fseek(keyFD, 0, SEEK_END); //find size of file
        keyLen = ftell(keyFD);
        fseek(keyFD, 0, SEEK_SET); //set seek to beginning
        keyBuf = (char*)calloc((keyLen + 1), sizeof(char)); //alloc memory and 0 it out
       
        if (keyBuf)
        {
            //memset(keyBuf, '\0', strlen(keyBuf));
            fread(keyBuf, 1, keyLen, keyFD); //read into buffer and replace ending newline with null char
            keyBuf[strcspn(keyBuf, "\n")] = '\0';   
        }
   
    fclose(keyFD);
    }

     //Check for invalid char
    validateContents(cipherBuf, cipherName);
    validateContents(keyBuf, keyName);    

    //Send cipher to server. Recv requests are to ensure sends dont bleed together. Also used for debugging
    sendFile(sock, cipherBuf);    
    if (recv(sock, buffer, sizeof(buffer), 0) < 0) {perror("Data recv error"); close(sock); exit(2);}
    //printf("cipherBuf: %s\n", cipherBuf);

    //Send key to server
    memset(buffer, '\0', sizeof(buffer));
    sendFile(sock, keyBuf);    
    if (recv(sock, buffer, sizeof(buffer), 0) < 0) {perror("Data recv error"); close(sock); exit(2);}
    //printf("keyBuf: %s\n", keyBuf);

    char plaintext[sizeof(cipherLen)];
    //Receive plaintext from server and print to stdout
    recvFile(sock, 1, plaintext);
    //printf("plaintext: %s\n", plaintext);
    if (send(sock, "PT transfer: good", 18, 0) < 0) {perror("Data recv error"); close(sock); exit(2);}
    free(cipherBuf);
    free(keyBuf);
    return 0;    
}