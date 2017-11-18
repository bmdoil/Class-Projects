/* Brent Doil - Project 1
** chatclient.c [hostname] [port]
** OSU CS 372 - Fall 2017
** C chat client that set connects to hostname and port given in CL arguments. 
** If connection to chat server successful, allows client to send and recv 
** messages w/ server, set client handle, and close connection
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>



#define MAX_HANDLE 13
#define MAX_BUF 512

//Globals
struct addrinfo hints;
struct addrinfo* res;
int socketConn;
int socketfd;
char* clientHandle;
char* serverHandle;

//Function definitions
void checkArgC();
void setIntAddr(char* h, char* p);
void setConn();
void setHandles(char* p);
void beginChat();


void checkArgC(int argc)
{
	if (argc != 3)
	{
		printf("Correct usage: ./chatclient [hostname] [port]\n");
		exit(1);
	}

}



//Sets hostname and port to CL arguments
//Returns getaddrinfo result

/* From: http://man7.org/linux/man-pages/man3/getaddrinfo.3.html

Given node and service, which identify an Internet host and a
service, getaddrinfo() returns one or more addrinfo structures, each
of which contains an Internet address that can be specified in a call
to bind(2) or connect(2).

The hints argument points to an addrinfo structure that specifies
criteria for selecting the socket address structures returned in the
list pointed to by res.*/	

void setIntAddr(char* h, char* p)
{
	char* host = h;
	char* port = p;
	//Set all fields to 0 in hints
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	//Args: *node, *service, *hints, **res
	getaddrinfo(host, port, &hints, &res);

}

//Sets up the socket connection
void setConn()
{
	//Create a socket
	if (res == NULL)
	{
		printf("Error in creating connection.\n");
		exit(1);
	}

	socketfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);

	//Check if unsuccesful socket creation
	if (socketfd == -1)
	{
		printf("Error establishing socket.\n");
		close(socketfd);
		exit(1);
				
	}

	//Create a connection
	socketConn = connect(socketfd, res->ai_addr, res->ai_addrlen);

	if (socketConn == -1)
	{
		printf("Error establishing connection to server.\n");
		close(socketfd);
		exit(1);
	}
	printf("Connection established with server.\n");

}

//Sets client handle and gets server handle from the active socket connection
void setHandles(char* p)
{ 
	char* port = p;
	int length = 0;
	size_t inputLen = MAX_HANDLE;
	clientHandle = malloc(sizeof(char) * (MAX_HANDLE + strlen(port)));	
	memset(clientHandle, 0, sizeof(*clientHandle));
	printf("Please enter your client handle [12 characters or less]\n");

	
	while (length > MAX_HANDLE || length == 0)
	{
		length = getline(&clientHandle, &inputLen, stdin);
		//Remove newline from input
		clientHandle[strcspn(clientHandle, "\n")] = 0;

	}
	const char space = ' ';
	clientHandle = strncat(clientHandle, &space, 1);
	clientHandle = strncat(clientHandle, port, 8);

	send(socketfd, clientHandle, strlen(clientHandle), 0);
	serverHandle = malloc(sizeof(char) * MAX_HANDLE);
	memset(serverHandle, 0, sizeof(*serverHandle));
	recv(socketfd, serverHandle, inputLen, 0);

	//Print server handle
	fflush(stdout);
}



//Runs the chat until connection is closed
void beginChat()
{
	int chat = 1;
	char writeBuf[MAX_BUF];
	char readBuff[MAX_BUF];
	
	while (chat)
	{
		//Clear writeBuf and clear stdout buffer
		memset(&writeBuf, 0, sizeof(writeBuf));
		
		fflush(stdout);
		
		//Prompt and receive client message
		printf("%s> ", clientHandle);
		fgets(writeBuf, 512, stdin);
		//If quit entered, break out of loop
		if (strncmp(writeBuf, "!quit", 5) == 0)
		{
			printf("Quitting.\n");
			close(socketfd);
			return;
			
		}
		//If send unsuccessful, close socket and exit. Otherwise write message to server.
		int checkConn = 0;
		checkConn = send(socketfd, writeBuf, strlen(writeBuf), 0);
		if (checkConn == -1)
		{
			printf("Connection has been closed.");
			close(socketfd);
			return;
		}

		//Receive the response
		memset(&readBuff, 0, sizeof(readBuff));
		recv(socketfd, readBuff, 512, 0);
		printf("%s> %s\n", serverHandle, readBuff);

		fflush(stdout);
	}

	//Clean up.
	close(socketfd);
	printf("Closing connection.");
	return;
	
}


//argv[1] = hostname argv[2] = port
int main(int argc, char* argv[])
{
	
	checkArgC(argc);
	setIntAddr(argv[1], argv[2]);
	setConn();
	setHandles(argv[2]);
	beginChat();

	//Free malloc'd vars from setHandles
	free(clientHandle);
	free(serverHandle);

	return 0;

}
	



