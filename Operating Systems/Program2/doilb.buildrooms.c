/*	Author: Brent Doil
**  Name: doilb.buildrooms.c 
**  OSU CS 344 - Fall 2017 - 10/25/2017
**  Helper program for Adventure game that builds Rooms for graph and writes to text file
**
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>


#define MIN_ROOM_CON 3
#define MAX_ROOM_CON 6
#define MAX_ROOMS 7
#define TOTAL_ROOMS 10
#define MAX_STRING 50

//Typedef boolean since it is not included in ANSI C
typedef enum {FALSE = 0, TRUE = 1} boolean;

//Types of rooms
char* roomType[3] = {
	"START_ROOM",
	"MID_ROOM",
	"END_ROOM"
};

//List of possible rooms names
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
	char name[20];
	char type[20];
	char connList[MAX_ROOM_CON][MAX_STRING];
	int connCount;	
};

/* Function prototypes defined here
** Since we are not using header files for this program
*/

char* createDir();
char** roomNames();
void freeNames(char** rooms);
boolean connsFull(struct Room** rooms);
void printRooms(struct Room** rooms, char* dir);
void connRooms(struct Room** rooms);
void addConn(struct Room* roomX, struct Room* roomY);
struct Room* createRoom(char* rName, char* rType);

/*	createDir()
**  Accepts: None
**  Returns: Directory as char*
**  Creates a new directory from the current directory, appends pid to end of directory
**  to ensure no naming conflicts
*/
char* createDir()
{	

	int pid = getpid();
	char* directory = malloc(25);
	sprintf(directory, "doilb.rooms.%d",pid);
	//Set unix perms
	mkdir(directory, 0760);
	return directory;
}

/*	roomNames()
**  Accepts: None 
**  Returns: 
**  
**
*/
char** roomNames()
{
	//Seed RNG
	srand(time(NULL));

	//Create temp ptr of TOTAL_ROOMS char* rooms
	char** rooms = malloc(sizeof(char*) * 10);
	int i = 0;
	for (i = 0; i < TOTAL_ROOMS; i++)
	{
		rooms[i] = roomName[i];
	}

	//Create another temp ptr to hold the random room names
	char** randRoom = malloc(sizeof(char*) * MAX_ROOMS);
	int j = MAX_ROOMS;
	//While loop randomizes the names of MAX_ROOMS # of rooms
	//Once room is named, pushed to end of array and iterator decremented
	//Runs until all rooms are named
	while (j > 0)
	{
		int randNum = rand() % j;
		randRoom[j - 1] = rooms[randNum];
		rooms[MAX_ROOMS] = rooms[randNum];
		int k = randNum;
		for (k = randNum; k < MAX_ROOMS; k++)
		{
			rooms[k] = rooms[k +1];
		}
		j--;
	}
	free(rooms);
	//Returns the ptr to char* of randomized room names
	return randRoom;
}

/*	freeNames(char** rooms)
**  Accepts: Ptr to array of room names
**  Returns: None
**  Simple helper function to free memory from room names allocated
**  by roomNames()
*/
void freeNames(char** rooms)
{
	free(rooms);
}

/*	connsFull(struct Room** rooms)
**  Accepts: Double Ptr to Room struct, to check all rooms in struct. 
**  Returns: Boolean 0 or 1
**  Checks rooms within Room** struct supplied to determine if connections
**  are able to be made. Use in a while loop to help fill all possible connections
*/
boolean connsFull(struct Room** rooms)
{
	int i;
	for (i = 0; i < MAX_ROOM_CON; i++)
	{
		//Are connections available? Checks for connCount b/t MIN and MAX ROOM CON
		if (rooms[i]->connCount < MIN_ROOM_CON || rooms[i]->connCount >=MAX_ROOM_CON)
			return 0;
	}
	return 1;
}

/*	printRooms(struct Room** rooms, char* dir)
**  Accepts: Double Ptr to the Room struct, and directory to print to
**  Returns: None
**  Prints the room struct to files for use in the Adventure program. Each room is a 
**  separate file.
*/
void printRooms(struct Room** rooms, char* dir)
{

	chdir(dir);
	int i, j;
	for (i = 0; i < MAX_ROOMS; i++)
	{
		FILE* myFile = fopen(rooms[i]->name, "w");
		//Room name as name of file
		fprintf(myFile, "ROOM NAME: %s\n", rooms[i]->name);

		for (j = 0; j < rooms[i]->connCount; j++)
		{
			//Print all connections
			fprintf(myFile, "CONNECTION %d: %s\n", j + 1, rooms[i]->connList[j]);
		}
		//Print room type
		fprintf(myFile, "ROOM TYPE: %s\n", rooms[i]->type);
		fclose(myFile);
	}
}

/*	connRooms(struct Room** rooms)
**  Accepts: Double Ptr to Room struct 
**  Function to connect all the rooms in the provide Room struct together
**  Uses the connsFull() and addConn() functions to run until all possible connections
**  have been made.
*/
void connRooms(struct Room** rooms)
{
	while (connsFull(rooms) == FALSE)
	{
		addConn(rooms[rand() % MAX_ROOMS], rooms[rand() % MAX_ROOMS]);
	}
}

/*	addConn(struct Room* roomX, struct Room* roomY)
**  Accepts: Ptrs to 2 rooms to be connected 
**  Attempts to create connection between 2 rooms. Will fail and simply return if connection cant be made
*/
void addConn(struct Room* roomX, struct Room* roomY)
{
	//Can they accept another conn?
	if (roomX->connCount == MAX_ROOM_CON || roomY->connCount == MAX_ROOM_CON)
	{
		return;
	}

	int i;
	//Check for existing connections between each room (both ways)
	for (i = 0; i < roomX->connCount; i++)
	{
		if (strcmp(roomX->connList[i], roomY->name) == 0)
		{
			return;
		}
	}

	for (i = 0; i < roomY->connCount; i++)
	{
		if (strcmp(roomY->connList[i], roomX->name) == 0)
		{
			return;
		}
	}
	//Same rooms?
	if (roomX == roomY)
	{
		return;
	}
	
	//Create forward and backward connection between 2 rooms if none of above checks fail.
	strcpy(roomX->connList[roomX->connCount], roomY->name);
	strcpy(roomY->connList[roomY->connCount], roomX->name);
	//Increment both connCounts
	roomX->connCount++;
	roomY->connCount++;
	
}


/*	createRoom(char* rName, char* rType)
**  Accepts: name and type strings
**  Returns: Ptr to Room struct
**  Instantiates room given new room name and type. Returns ptr to the new room.
**  
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
		

int main(){

	
	char** rNames = roomNames();
	char* rDir = createDir();

	struct Room* rooms[MAX_ROOMS];

	//Wrote this outside of a function because it was simplest solution. Could refactor later
	int i = 0;
	for (i = 0; i < MAX_ROOMS; i++)
	{
		if (i == 0)
		{
			rooms[i] = createRoom(rNames[i], roomType[0]);
		}
		else if (i < 6)
		{
			rooms[i] = createRoom(rNames[i], roomType[1]);
		}
		else if (i == 6)
		{
			rooms[i] = createRoom(rNames[i], roomType[2]);
		}
		else
			printf("Error assigning types");
	}

	connRooms(rooms);
	printRooms(rooms, rDir);
	freeNames(rNames);
	int j;
	for (j = 0; j < MAX_ROOMS; j++)
	{
		free(rooms[j]);
	}

	free(rDir);
	return 0;
}