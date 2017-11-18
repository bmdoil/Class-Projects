#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif


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

//Buffers
#define MAX_DIR 100
#define MAX_ARGS 512
#define MAX_BUFF 2048

//Globals

int fgOnly = 0; //foreground flag
int bgProc = 0; //background flag

//Initialize pid values to junk
pid_t childPid = -5;
pid_t killPid = -5;
pid_t pid = -5;

//Variables for redirection and string manipulation
int outRedir = 0;
int inRedir = 0;
char* outputFile = NULL;
char* inputFile = NULL;
char* token = NULL;
int inFD = 0;
int outFD = 0;
int result = 0;
int numCharsEntered = -5;

//Exit value of child proc
int exitVal = 0;
//Argument cound
int userArgc = 0;
//Used for calloc
size_t size = MAX_BUFF;

//The string manipulation starts here
char* arguments[MAX_ARGS];
char* userInput = NULL;
char* parsedInput = NULL;
char directory[MAX_DIR];


//Signal handlers definition
void stopHandler(int signo);
void interruptHandler(int signo);
//void childHandler(int signo);


// smallsh built in functions
void _procExit(); //exits smallsh
void _procStatus(int exitVal); //prints status/termination signal
void _procCD(char* arguments, char* dir); //cd command
void _redirection(char* input); //encapsulates some redirection/tokens

int main()
{
	//init terminal stop signal
	struct sigaction stopSig;
	stopSig.sa_handler = stopHandler;
	sigfillset(&(stopSig.sa_mask)); //tried this and it worked (:
	stopSig.sa_flags = SA_RESTART;
	sigaction(SIGTSTP, &stopSig, NULL);

	//init interrupt signal
	struct sigaction intSig;
	intSig.sa_handler = interruptHandler;
	sigfillset(&(intSig.sa_mask)); //tried this and it worked (:
	intSig.sa_flags = SA_RESTART;
	sigaction(SIGINT, &intSig, NULL);

	/* init child signal - couldn't figure this out
	struct sigaction cldSig;
	cldSig.sa_handler = &childHandler;
	sigfillset(&(cldSig.sa_mask));
	cldSig.sa_flags = SA_RESTART | SA_NOCLDSTOP;
	*/

	//Zero out directory
	memset(directory, 0, sizeof(directory));

	/************************************************************************
	** Main loop - runs infinitely until exit is called
	**/

	while (1)
	{

		bgProc = 0; //bg proc not active
		//Use calloc to 0 initialize the memory
		userInput = (char*)calloc(size, sizeof(char));
		parsedInput = (char*)calloc(size, sizeof(char));

		//Adapted from REF: https://oregonstate.instructure.com/courses/1648339/pages/3-dot-3-advanced-user-input-with-getline
		while (1)
		{

			//Status cursor
			printf(": ");
			fflush(stdout);

			numCharsEntered = getline(&userInput, &size, stdin);
			//Strip newline and pray to the C string Gods
			userInput[strcspn(userInput, "\n")] = '\0';

			strncpy(parsedInput, userInput, strlen(userInput) + 1); //copy into parsed input 
			parsedInput[strlen(parsedInput) + 1] = '\0'; //make sure it's still null terminated
			//If something went wrong
			if (numCharsEntered == -1)
			{
				clearerr(stdin);
			}
			else
				break;
		}

		userArgc = 0; //set arg count 

		/************************************************************************/


		if (strcmp(parsedInput, "#") == 0) //if comment, ignore rest of line
		{
			continue;
		}
		//REF: https://stackoverflow.com/questions/32413667/replace-all-occurrences-of-a-substring-in-a-string-in-c
		//Expands $$ to pid very carefully by building up a buffer from the replacement value of $$ (getpid)
		char buffer[MAX_BUFF];
		char* pidSymbol = parsedInput;
		char pidString[30] = { 0 };
		sprintf(pidString, "%d", (int)pid);
		while ((pidSymbol = strstr(pidSymbol, "$$")))
		{
			strncpy(buffer, parsedInput, pidSymbol - parsedInput);
			buffer[pidSymbol - parsedInput] = '\0';
			strcat(buffer, pidString);
			strcat(buffer, pidSymbol + strlen(parsedInput));
			strcpy(parsedInput, buffer);
			pidSymbol++;
		}

		_redirection(parsedInput); //first tokenize redirection operators

		//Check for built in function
		if ((strncmp(parsedInput, "exit", 4) == 0)) 
		{
			_procExit();
		}
		else if (strncmp(parsedInput, "cd", 2) == 0)
		{
			_procCD(parsedInput, directory);
		}
		else if (strncmp(parsedInput, "status", 6) == 0)
		{
			if (strlen(parsedInput) >= 8)
			{
				exitVal = 1;
			}
			_procStatus(exitVal);
		}
		
		//This might not be necessary, but it doesn't hurt.
		else if (arguments[0] == NULL || (*(arguments[0]) == '#'))
		{
			continue;
		}
		else //time to fork
		{
			childPid = fork();

			switch (childPid)
			{
			case 0: //child proc begins
				if (bgProc != 1) //if not a bg proc, set SIGINT to default behavior
				{
					intSig.sa_handler = SIG_DFL;
					sigaction(SIGINT, &intSig, NULL);
				}
				if (inRedir == 1) //if input redirection encountered
				{			

					if (bgProc == 1) //if bg proc, dump to dev/null
					{
						inFD = open("/dev/null", O_RDONLY);
						if (inFD == -1)
						{
							perror("error opening file");
							fflush(stdout);
							exit(1);

						}
					}

					else 
					{

						inFD = open(inputFile, O_RDONLY);  //open inputFile (set from redirection)
						if (inFD == -1) //if something goes wrong, cleanup
						{
							printf("cannot open %s for input\n", inputFile);
							fflush(stdout);
							exit(1);

						}

						result = dup2(inFD, 0); //redirect stdin to inFD
						if (result == -1) { perror("source dup2()"); exit(2); } //error conditions
					}

				}
				if (outRedir == 1) //if output redirection encountered
				{
											
					outFD = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644); //open outputFile and set permissions
					if (outFD == -1)//if something goes wrong, cleanup
					{
						printf("cannot open %s for output\n", outputFile);
						fflush(stdout);
						exit(1);

					}

					result = dup2(outFD, 1); //redirect stdout to outFD
					if (result == -1) { perror("target dup2()"); exit(2); } //error conditions

				}


				if (execvp(arguments[0], arguments)) //if bad command, or something goes wrong
				{
					printf("\"%s\": no such file or directory\n", arguments[0]);
					fflush(stdout);
					exit(1);

				}
				break;

			default: //run by parent process

				if (bgProc != 1) //if not running in bg, waitpid
				{
					pid = getpid();
					killPid = waitpid(childPid, &exitVal, 0);
				}
				else
				{
					printf("background pid is %d\n", childPid); //print out background pid
				}

				dup2(0, inFD);  //reset stdin
				dup2(1, outFD); //reset stdout

				break;
			}
		}

		//Cleanup
		inRedir = 0;
		outRedir = 0;

		inputFile = NULL;
		outputFile = NULL;

		memset(arguments, 0, sizeof(arguments));

		//Wait on next child process to terminate. Use WNOHANG to allow for further commands to run
		childPid = waitpid(-1, &exitVal, WNOHANG);
		while (childPid > 0) //reaps terminated background proc, displays some results
		{
			printf("background process %i is done: ", childPid);
			_procStatus(exitVal);
			childPid = waitpid(-1, &exitVal, WNOHANG);
		}


	}

	free(userInput);
	free(parsedInput);

	return 0;
}

//Built-in command to exit smallsh
void _procExit()
{
	exit(0);
}
//Built in command to implement cd. 
//Requires an input stream and directory buffer to write to
void _procCD(char* parsedInput, char* dir)
{
	token = strtok(parsedInput, " "); //tokenize input
	while (token != NULL) //this builds the string
	{
		strcpy(dir, token); 
		token = strtok(NULL, " ");
	}
	if (strcmp(dir, "cd") == 0) //if cd is only arg, chdir to home
	{
		chdir(getenv("HOME"));
	}

	else
	{
		chdir(dir); //execute command

	}

}
//Built-in command to print exit value or signal that terminated process
void _procStatus(int exitVal)
{

	if (WIFEXITED(exitVal)) //if process exited, print exit status
	{
		printf(" exit value %d\n", WEXITSTATUS(exitVal));
		fflush(stdout);
	}
	else
	{
		printf(" terminated by signal %d\n", exitVal); //if terminated, print signal 
		fflush(stdout);
	}
}
//Encapsulates process of tokenizing input for IO redirection. Strips redirectors and saves arguments to array
void _redirection(char* parsedInput)
{

	token = strtok(parsedInput, " "); //tokenize
	while (token != NULL)
	{
		if (strcmp(token, ">") == 0)
		{

			token = strtok(NULL, " "); //get token
			//printf("> is here, token is %s", token);
			outRedir = 1; //flags the argument set to run the outRedir code
			outputFile = token; //places the token to outPutFile for action later
		}
		else if (strcmp(token, "<") == 0)
		{

			token = strtok(NULL, " ");
			//printf("< is here, token is %s", token);
			inRedir = 1; //flags the argument set to run the inRedir code
			inputFile = token; //places the token to inPutFile for action later
		}
		
		else if (strcmp(token, "&") == 0) //sets bgProc flag, unless fgOnly is already active
		{
			if (fgOnly == 1)
			{
				bgProc = 0;
			}
			else
				bgProc = 1;
		}	
		
		else
		{
			arguments[userArgc] = token; //set arguments array to correct arguments as loop runs
			userArgc++; 
		}
		token = strtok(NULL, " "); 
	}
	arguments[userArgc] = NULL; //NULL terminate the arg list
}
//Ctrl-Z will swap foreground-only mode back and forth. Displays message and flips fgOnly flag
void stopHandler(int signo)
{
	if (fgOnly == 0)
	{
		printf("\nEntering foreground-only mode (& is now ignored)\n");
		fgOnly = 1;
	}
	else
	{
		printf("\nExiting foreground-only mode\n");
		fgOnly = 0;
	}
}
//Kills process set to killPid
void interruptHandler(int signo)
{
	printf("terminated by signal %d\n:", signo);
	kill(killPid, SIGKILL);
}

//Couldn't figure it out in time
/*void childHandler(int signo)
{
pid_t p;
while ((p = waitpid(-1, &exitVal, WNOHANG) != -1))
{

}
}
*/
