#include <pthread.h>



#define MAX_CLIENTS 10
#define MAX_DIR 1024
#define PENDING 5
#define MAX_LEN INET6_ADDRSTRLEN

struct THREAD{
    pthread_t threadID;
    int sockFD;
    char currentDir[MAX_DIR];
};

struct CLIENT{
    struct THREAD cliThread;
    struct CLIENT* nextC;
};

struct CLIENTLIST{
    struct CLIENT *first, *last;
    int numClients;
};



void sigchld_handler(int signo);
void sigpipe_handler(int signo);
void* get_in_addr(struct sockaddr *sa);
void getDirList(char* buf, char* path);
void clientInit(struct CLIENTLIST*);
int clientAdd(struct CLIENTLIST*, struct THREAD*);
int clientRemove(struct CLIENTLIST*, struct THREAD*);
int clientCompare(struct THREAD*, struct THREAD*);
void dataConn(void* fd);
void sendFile()