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
#include <unistd.h>

int main(int argc, char* argv[])
{
    spawnPid = fork();
        if (spawnPid)
        {
            close(listenSocketFD);
            //Open 2nd TCP connection on DATA PORT using commands array  
            
            if (sendDir == 1)
            {                    
                   getDirList(buffer, ".");                           
            }
            else if (sendFile == 1)
            {
                outputFile = fopen(fileName, "wb")
                if (outputFile == NULL){fprintf(stderr, "Unable to open file %s\n", fileName);}
                int bytesSent = (send(newConnFD, outputFile, sizeof(outputFile), 0));
                if (bytesSent < 0){perror("send"); exit(1);}
            }
            
           
        }
        sendDir = 0;
        sendFile = 0;
        close(newConnFD);
        
}
