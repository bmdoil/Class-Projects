#ifndef FENCRYPT_H
#define FENCRYPT_H

#define MAX_LEN 1024 //Max packet size
#define MAX_SIZE 70000 //Max file size


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


void validateContents(char* contents, char* filename); //Validate that file contents have only valid characters
void sendFile(int sockfd, char* contents); //Send file through socket sockfd
void recvFile(int sockfd, int mode, char* msg); //Receive file from sockfd, mode = 1 prints directly to stdout, mode = 0 does not
void encrypt(char *plaintext, char *key, char* cipher); //Encrypts plaintext using key and sends to cipher
void decrypt(char *ciphertext, char *key, char* plaintext); //Decrypts cipher using key and sends to plaintext



#endif