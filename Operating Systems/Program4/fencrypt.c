
#include "fencrypt.h"



char buffer[MAX_SIZE];

void validateContents(char* contents, char* filename)
{
    char c;
    int i;
    
    for (i = 0; i < strlen(contents); i++) 
    {
       c = contents[i]; 
       if (c < 65 || c > 90) //Check if char is uppercase A = 65 Z = 90
        {
            if (c != 32) //If not uppercase and not space, error
            {
                fprintf(stderr, "Error: Invalid character in %s: '%c' at location %d\n", filename, contents[i], i);
                exit(1);
            }
        }
    }
}

void sendFile(int sockfd, char* contents)
{   
    int msgSize;
    int offset = 0;
    char msg[strlen(contents) + 3]; //Add buffer for termination chars (to look for when receiving) and null byte
    memset(msg, '\0', sizeof(msg)); //ZSero out msg
    strcat(msg, contents); //cat contents into message
    strcat(msg, "$$");      //cat term chars
    int remaining = strlen(msg); //set remaining bytes to length of msg

    while (remaining > 0) //Whilebytes remaining
    {
        if (remaining > MAX_LEN) {msgSize = MAX_LEN;} //Set appropriate packet size
        else {msgSize = remaining;}

        char buffer[msgSize + 1];   //Set up buffer
        memset(buffer, '\0', sizeof(buffer));
        strncpy(buffer, msg + offset, msgSize); //Copy piece of msg into the buffer, keep track of offset

        int bytesSent = send(sockfd, buffer, msgSize, 0); //send
        if (bytesSent < 0){perror("Server error sending");}
        if (bytesSent < msgSize){printf("Error sending all file data");}

        offset += msgSize; //Move offset
        remaining -= msgSize; //Update remaining bytes

    }         
}
//Recv file
void recvFile(int sockfd, int mode, char* msg)
{
    int bytesRecv = 0;    
    
    char buffer[MAX_LEN + 1]; //Holds incoming stream
    memset(msg, '\0', sizeof(msg));
    while (strstr(msg, "$$") == NULL) //While termination chars not found
    {
        memset(buffer, '\0', sizeof(buffer));
        bytesRecv = recv(sockfd, buffer, sizeof(buffer - 1), 0); //Recv message into buffer
        strcat(msg, buffer); //Cat onto msg
        if (bytesRecv < 0) {perror("error reading from socket");} //Report an error
    }
    if (mode == 1) //Sends to stdout
    {
        int temp = strstr(msg, "$$") - msg; //Find termination chars
        msg[temp] = '\0';                   //Set their location to null but
        printf("%s\n", msg);                //Print and flush stdout
        fflush(stdout); 
    }
    else //Null term msg and do not print to stdout
    { 
        int temp = strstr(msg, "$$") - msg;
        msg[temp] = '\0';        
    }

}
//Uses char/int manipulation to encrypt ciphertext using key. OTP with 27
void encrypt(char *plaintext, char *keytext, char* ciphertext) 
{
    int i;
    char c, p, k;    //c = cipher p = plain k = key indexes
    // loop through each character in plaintext since it is shorter than key
    for (i = 0; i < strlen(plaintext); i++) 
    {
        k = keytext[i] - 65; //'A' = 65, subtract 65 to set up OTP math
        p = plaintext[i] - 65;

        if (k == -33) k = 26; //ASCII space = 32. 32 - 65 = -33, set to 26 (0-25 corresponds A-Z)
        if (p == -33) p = 26;   
        c = (p + k) % 27; //Add plain + key then mod 27
        if (c == 26) c = 32; //If space, set to ASCII val      
        else  c += 65;  //Otherwise add 65 to get ASCII char val          
        ciphertext[i] = c; //Set to index
    }
   
}
//Uses char/int manipulation to decrypt ciphertext using key. OTP with 27
void decrypt(char *ciphertext, char *keytext, char* plaintext) 
{
    int i;
    
    char c, p, k;
    
    // loop through each character in ciphertext since it is shorter than key
    for (i = 0; i < strlen(ciphertext); i++) 
    {
        k = keytext[i] - 65; //'A' = 65, subtract 65 to set up OTP math
        c = ciphertext[i] - 65;

        if (k == -33) k = 26;  //ASCII space = 32. 32 - 65 = -33, set to 26 (0-25 corresponds A-Z)
        if (c == -33) c = 26;  
        if ((c - k) < 0)    //If cipher - key < 0, add 27
        {
            p = (c - k ) + 27;
        }
        else                // Otherwise cipher - key mod 27
        {
            p = (c - k) % 27;
        }

        if (p == 26) p = 32; //If space, set to ASCII val   
        else  p += 65;       //Otherwise add 65 to get ASCII char val            

        plaintext[i] = p; //Set to index
    }
   
}

