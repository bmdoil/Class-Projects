/*  Author: Brent Doil
**  Name: doilb.adventure.c 
**  OSU CS 344 - Fall 2017 - 10/25/2017
**  Adventure program that uses existing room files to build graph. Allows user to traverse through
**  graph to attempt to find end. Uses mutex to incorporate a 2nd thread, printing time to file when called
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <pthread.h>


#define MIN_ROOM_CON 3
#define MAX_ROOM_CON 6
#define MAX_ROOMS 7
#define TOTAL_ROOMS 10
#define MAX_STRING 20
#define MAX_READ 1024
#define MAX_FILE_BUF 256
 
//Typedef boolean since it is not included in ANSI C
typedef enum {FALSE = 0, TRUE = 1} boolean;

//Quick and dirty global variables for fun C string manipulation.
char dirName[MAX_FILE_BUF];
char readBuf[MAX_READ];
char fileBuf[MAX_FILE_BUF];
char currentName[MAX_STRING];
char currentConn[MAX_STRING];
char currentType[MAX_STRING];
char curTimeFile[] = "currentTime.txt";

//Mutex
pthread_mutex_t squirrelTex = PTHREAD_MUTEX_INITIALIZER;


char* roomType[3] = {
    "START_ROOM",
    "MID_ROOM",
    "END_ROOM"
};

char* roomName[TOTAL_ROOMS] = {
    "Arkham_Asylum",
    "Black_Cave",
    "Curiositie_Shoppe",
    "Innsmouth_Jail",
    "Police_Station",
    "Train_Station",
    "River_Docks",
    "St_Marys_Hospital",
    "Independence_Square",
    "Unvisited_Isle"
};

//Room structure, holds name, type, # of connections, and list of active connections to other rtooms
struct Room {
    char name[MAX_STRING];
    char type[MAX_STRING];
    char connList[MAX_ROOM_CON][MAX_STRING];
    int connCount;  
};

//Hold path traversed during running of program.
struct Path {
    int steps;
    int stepsArr[50];
};

/* Function prototypes defined here
** Since we are not using header files for this program
*/

void* writeTime(void* mutex);
void* getTime();
DIR* openDir();
void addPath(struct Path* path, int room);
void connRoom(struct Room* roomX, char* rmCon);
boolean isConnected(struct Room* curRoom, char* rmCheck);
void setType(struct Room* roomX, char* newType);
int findRoom(struct Room** rooms, char* rmName);
void printCurRoom(struct Room** rooms, int curRoom);
void buildRooms(struct Room* rooms[], struct dirent* curFile, FILE* curRoomFile, DIR* newestDir);
void playGame(struct Room** rooms, pthread_mutex_t mutex);
struct Room* createRoom(char* rName, char* rType);
struct Path* createPath();

/*  void* writeTime(void* mutex) 
**  Accepts: Main thread mutex
**  Returns: None
**  Takes the current time and writes it to file
*/
void* writeTime(void* mutex) 
{
    // Takes the current time and writes it to file
    // Attempts to access mutex, only works if main thread has released mutex
    pthread_mutex_lock(mutex);

    FILE* timeFile = fopen(curTimeFile, "w");
    time_t curTime;
    char* timeStr;

    // Gets current time and formats it
    curTime = time(0);
    timeStr = ctime(&curTime);

    // Writes time to file
    fputs(timeStr, timeFile);
    fclose(timeFile);

    // Releases lock on mutex so main thread can regain control
    pthread_mutex_unlock(mutex);
    return NULL;
}

/*  void* getTime() 
**  Accepts: None
**  Returns: None
**  Prints out current time from curTimeFile
*/
void* getTime() 
{
    // Prints out current time from curTimeFile
    FILE* timeFile = fopen(curTimeFile, "r");
    char timestamp[64];
    fgets(timestamp, sizeof(timestamp), timeFile);
    printf("\n%s\n", timestamp);
    fclose(timeFile);
    return NULL;
}

/*  struct Room* createRoom(char* rName, char* rType)
**  Accepts: Room name and type to identify room
**  Returns: Ptr to room struct
**  Instantiates a Room and intializes variables within the Room struct
*/
struct Room* createRoom(char* rName, char* rType)
{

    struct Room* newRoom = malloc(sizeof(struct Room));
    

    memset(newRoom->name, '\0', sizeof(newRoom->name));
    strcpy(newRoom->name, rName);

    newRoom->connCount = 0;

    memset(newRoom->type, '\0', sizeof(newRoom->type));
    strcpy(newRoom->type, rType);

    int i = 0;
    for (i = 0; i < MAX_ROOM_CON; i++)
    {
        memset(newRoom->connList[i], '\0', sizeof(newRoom->connList[i]));
        strcpy(newRoom->connList[i], "NA");
    }
    return newRoom;
}

/*  struct Path* createNewPath()
**  Accepts: None
**  Returns: Ptr to Path struct
**  Instantiates a Path and intializes variables within the Path struct  
*/
struct Path* createNewPath()
{
    // A path is a struct that contains the order in which rooms are visited
    // createNewPath() initializes a new path struct and returns a pointer to it
    struct Path* newPath = malloc(sizeof(struct Path));

    // Initialize with 0 steps
    newPath->steps = 0;

    // Initialize stepsArr with every value of array with sentinel value of -1
    int i;
    for (i = 0; i < 32; i++) {
        newPath->stepsArr[i] = -1;
    }

    return newPath;
}

/*  addPath(struct Path* path, int room)
**  Accepts: Path struct, index of room
**  Returns: None
**  Adds to Path struct and increments steps taken by player. Used to create history
**  of steps taken. 
*/
void addPath(struct Path* path, int room) 
{
   
    path->stepsArr[path->steps] = room;
    path->steps++;
}

/*  connRoom(struct Room* roomX, char* rmCon) 
**  Accepts: Room, name of conn to check
**  Returns: None
**  Connects 2 rooms. Prereq is that connection can be made. 
*/
void connRoom(struct Room* roomX, char* rmCon) 
{
    
    strcpy(roomX->connList[roomX->connCount], rmCon);
    roomX->connCount++;
}

/*  isConnected(struct Room* room, char* rmCheck)
**  Accepts: Room, name of room to check
**  Returns: boolean TRUE/FALSE
**  Checks to see if Room is connected to another room (by name)
*/
boolean isConnected(struct Room* room, char* rmCheck) 
{
    // Returns TRUE if rooms are connected
    int i;
    for (i = 0; i < room->connCount; i++) {
        if (strcmp(room->connList[i], rmCheck) == 0) 
        {
            return TRUE;
        }
    }
    return FALSE;
}

/*  setType(struct Room* roomX, char* newType) 
**  Accepts: Room, type to set as
**  Returns: None
**  Sets room type of room in argument to type in argument
*/
void setType(struct Room* roomX, char* newType) 
{
    // Sets the room type of the given room to the specified type
    memset(roomX->type, '\0', sizeof(roomX->type));
    strcpy(roomX->type, newType);
}


/*  findRoom(struct Room** rooms, char* rmName)
**  Accepts: Ptr to room struct, room name to search for
**  Returns: Index of room in room struct
**  Given a room name, find the index it occupies in rooms array
*/
int findRoom(struct Room** rooms, char* rmName) 
{
    // Given a room name, find the index it occupies 
    int i;
    for (i = 0; i < MAX_ROOMS; i++) {
        if (strcmp(rooms[i]->name, rmName) == 0) 
        {
            return i;
        }
    }

    // Returns -1 if not found
    return -1;
}


/*  printCurRoom(struct Room** rooms, int curRoom)
**  Accepts: Ptr to room struct, current room int
**  Returns: None, prints to stdout
**  Prints the name of the current room and the rooms it is connected to
*/
void printCurRoom(struct Room** rooms, int curRoom) 
{
    // Prints the name of the current room and the rooms it is connected to
    printf("CURRENT LOCATION: %s\n", rooms[curRoom]->name);
    printf("POSSIBLE CONNECTIONS: ");
    int i = 0;
    for (i = 0; i < rooms[curRoom]->connCount; i++) {
        printf("%s", rooms[curRoom]->connList[i]);
        if (i != (rooms[curRoom]->connCount - 1)) {
            printf(", ");
        }
    }
    printf(".\n");
}


/*  openDir(struct dirent* fileInDir)
**  Accepts: dirent 
**  Returns: Ptr to DIR 
**  Opens the most recently created existing rooms directory doilb.rooms.*
**  
*/
DIR* openDir(struct dirent* fileInDir)
{
    DIR* currDir = opendir(".");
    if (currDir < 0) {
        fprintf(stderr, "Can't open directory\n");
        exit(1);
    }

    // Adapted from Brewster lecture slide 2.4 on manipulating directories
    memset(dirName, '\0', sizeof(dirName));
    struct stat dirAttr;
    long int newestDirTime = -1;
    int dirExists = 0;
    while ((fileInDir = readdir(currDir)) != NULL) {
        
        if (strstr(fileInDir->d_name, "doilb.rooms.") != NULL) {
            dirExists = 1;
            
            stat(fileInDir->d_name, &dirAttr);
            if ((long int)(dirAttr.st_mtime) > newestDirTime) {
                // Finds most recently modified rooms directory
                newestDirTime = (long int)dirAttr.st_mtime;
                memset(dirName, '\0', sizeof(dirName));
                strcpy(dirName, fileInDir->d_name);
            }
        }
    }
    closedir(currDir);

    if (dirExists == 0) {
        fprintf(stderr, "No rooms found\n");
        exit(1);
    }

    DIR* returnDir = opendir(dirName);
    return returnDir;
}


/*  buildRooms(struct Room* rooms[], struct dirent* curFile, FILE* curRoomFile, DIR* newestDir)
**  Accepts: Room struct, dirent, FILE and DIR. MUST HAVE ALL ARGUMENTS
**  Returns: None
**  Builds rooms for game from existing room files in most recent directory. Will exit with EC 1
**  if prerequisites are not met. Requires error-free run of buildrooms.c
*/
void buildRooms(struct Room* rooms[], struct dirent* curFile, FILE* curRoomFile, DIR* newestDir)
{
    int i = 0;
    // Read in files in directory
    while ((curFile = readdir(newestDir)) != NULL)
    {
        // Opens the file 
        if (curFile->d_type == DT_REG)
        {
            // Clears any char buffers
            memset(readBuf, '\0', sizeof(readBuf));
            memset(fileBuf, '\0', sizeof(fileBuf));
            memset(currentName, '\0', sizeof(currentName));
            memset(currentConn, '\0', sizeof(currentConn));
            memset(currentType, '\0', sizeof(currentType));

            // Reconstructs room filenam
            strcpy(fileBuf, dirName);
            strcat(fileBuf, "/");
            strcat(fileBuf, curFile->d_name);
            curRoomFile = fopen(fileBuf, "r");
            //Error check
            if (!curRoomFile) {
                fprintf(stderr, "Could not open room file\n");
                exit(1);
            }

            // Get room name 
            fgets(readBuf, sizeof(readBuf), curRoomFile);
            readBuf[strlen(readBuf) - 1] = '\0';
            strcpy(currentName, &readBuf[11]);

            // Create new room with room name
            rooms[i] = createRoom(currentName, roomType[1]);

            // Get connections and room type then assign
            while (fgets(readBuf, sizeof(readBuf), curRoomFile) != NULL) 
            {
                if (strstr(readBuf, "CONNECTION") != NULL) 
                {
                    readBuf[strlen(readBuf) - 1] = '\0';
                    strcpy(currentConn, &readBuf[14]);
                    connRoom(rooms[i], currentConn);
                }
                else 
                {
                    readBuf[strlen(readBuf) - 1] = '\0';
                    strcpy(currentType, &readBuf[11]);
                    setType(rooms[i], currentType);
                }
            }

            // Close current file
            fclose(curRoomFile);
            i++;
        }
    }
    closedir(newestDir);
    return;
}


/*  createDir()
**  Accepts: None
**  Returns: Directory as char*
**  Creates a new directory from the current directory, appends pid to end of directory
**  to ensure no naming conflicts
*/
void playGame(struct Room** rooms, pthread_mutex_t mutex)
{
    int threadVar = 0;
    int charCount = 0;
    int i = 0;
    int curRoom = 0;
    //Lock main thread
    pthread_mutex_lock(&mutex);
    
    size_t buf = 0;
    pthread_t threadTwo;
    char* player = NULL;
    boolean endGame;
    struct Path* path = createNewPath();

    // Run the game until the END_ROOM is reached
    while (strcmp(rooms[curRoom]->type, roomType[2]) != 0) {
        endGame = FALSE;
        printCurRoom(rooms, curRoom);

        // Get player input
        while (endGame == FALSE) 
        {
            printf("WHERE TO? >");
            charCount = getline(&player, &buf, stdin);
            player[charCount - 1] = '\0';
            if ((isConnected(rooms[curRoom], player) == 0) &&
                (strcmp(player, "time") != 0)) 
            {
                // Force proper input from player
                printf("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
                free(player);
                buf = 0;
                player = NULL;
            }
            else if (strcmp(player, "time") == 0)
            {
                // If player inputs "time", then update curTimeFile and print

                // Main thread releases lock on mutex
                pthread_mutex_unlock(&mutex);

                // Creates a new thread to update currentTime.txt 
                // threadTwo is initialized and locked within writeTime function
                threadVar = pthread_create(&threadTwo, NULL, writeTime, &mutex);

                // Block until timeThread unlocks and terminates
                pthread_join(threadTwo, NULL);

                // Relock mutex on main thread
                pthread_mutex_lock(&mutex);

                // Main thread prints time
                getTime();

                free(player);
                buf = 0;
                player = NULL;
            }
            else
            {
                // All good? Move player to next room and update Path struct
                curRoom = findRoom(rooms, player);
                addPath(path, curRoom);

                printf("\n");
                free(player);
                buf = 0;
                player = NULL;
                endGame = TRUE;
            }
        }
    }
    //IT WORKED! Print out success messages
    printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
    printf("YOU TOOK %d STEPS. ", path->steps);
    printf("YOUR PATH TO VICTORY WAS:\n");
    //Print out path of rooms visited
    for (i = 0; i < path->steps; i++) {
        printf("%s\n", rooms[path->stepsArr[i]]->name);
    }

    // Free all rooms for cleanup
    for (i = 0; i < 7; i++) {
        free(rooms[i]);
    }
    free(path);    

}


int main() 
{
    //Set up variables to load information from existing room files and directory, add Room struct to write them to
    struct dirent* curFile = NULL;   
    DIR* newestDir = openDir(curFile);   
    struct Room* rooms[MAX_ROOMS];     
    FILE* curRoomFile = NULL;     

    //Builds room graphs from files and directory specified
    buildRooms(rooms, curFile, curRoomFile, newestDir); 

    //Plays game by passing in rooms struct and the main thread mutex. Secondary thread is created within
    playGame(rooms, squirrelTex);

    return 0; 

    
}