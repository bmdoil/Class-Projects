#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>



int main(int argc, char* argv[])
{
    if ((argc < 2) || (argc > 4))
    {
        fprintf(stderr, "Usage 1: ./keygen [keylength]\nUsage 2: ./keygen [keylength] > [newFile]\n");
        exit(1);
    }
    srand(time(NULL));
    int keyLength = atoi(argv[1]);
    int i, temp;
    char* seed = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    char* keyGen = malloc(sizeof(char*)*keyLength +1);
    char a = 'A';
    
    for (i = 0; i < keyLength; i++)
    {
        temp = rand() % strlen(seed);
        keyGen[i] = seed[temp];
    }
    
    //keyGen[keyLength] = '\n';
    printf("%s\n", keyGen);
    free(keyGen);
    return 0;
    
}