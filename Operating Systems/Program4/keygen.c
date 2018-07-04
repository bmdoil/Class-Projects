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
    if ((argc < 2) || (argc > 4)) //Check usage
    {
        fprintf(stderr, "Usage 1: ./keygen [keylength]\nUsage 2: ./keygen [keylength] > [newFile]\n");
        exit(1);
    }
    srand(time(NULL));
    int keyLen = strtol(argv[1], NULL, 10); //String to long type
    int i;
    char c;
    for (i = 0; i < keyLen; i++) 
    {
        c = rand() % 27; //Mod 27 for these keys
        if (c == 26) //26 = space in this keygen, set to ASCII space 32
        {
            c = 32;
        }
        else  //Otherwise add 65 to get uppercase char val
        {
            c += 65;
        }
        printf("%c", c); //Print char to stdout
    }
    printf("\n"); //Append newline, necessary for files
    return 0;
}