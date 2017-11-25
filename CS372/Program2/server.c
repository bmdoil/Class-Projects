
#include "server.h"


//Get correct sockaddr. Handles IPv4 and IPv6 
//REF: http://beej.us/guide/bgnet/output/html/multipage/clientserver.html
void *get_in_addr(struct sockaddr *sa)
{
    return sa->sa_family == AF_INET
      ? (void *) &(((struct sockaddr_in*)sa)->sin_addr)
      : (void *) &(((struct sockaddr_in6*)sa)->sin6_addr);
}
//List files in directory 'path'
//REF:https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program
void getDir(char* buf, char* path)
{
    DIR* d;
    d = opendir(path);
    struct dirent* dir;
    if (d)
    {
        while (dir = readdir(d) != NULL)
        {
            if (dir->d_type == DT_REG)
            {                                
                snprintf(buf, sizeof(buf) - 1, "%s\n", dir->d_name);
            }
        }
    }
    closedir(d);
    //Make sure all data is sent                 
}

void sendFile(char* buffer, int sockFD, FILE* fp)
{

}
