/*
 * CS 261 Assignment 5
 * Name: Brent Doil
 * Date: 7/31/2016
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
*Compares a task with each task already in the heap.   
*@param heap
*@param the new task to compare to the heap 
*@Returns: 0 if not present, 1 if present  
*/

int duplicateCheck(DynamicArray *heap, struct Task *task)
{
	DynamicArray* temp = dyNew(1);
	dyCopy(heap, temp);
	while (dySize(temp) > 0)
	{
		Task* tempTask = dyHeapGetMin(temp);
		if (strcmp(tempTask->name,task->name) == 0)
		{
			return 1;
		}
		dyHeapRemoveMin(temp,taskCompare);
	}	
	dyDelete(temp);
	return 0;
}

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
	const int FORMAT_LENGTH = 256;	
    char format[256];
	snprintf(format, 256, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    { 
	struct Task *newTask = taskNew(temp.priority, temp.name);           	 
  	if (duplicateCheck(heap, newTask) == 0){        
		  dyHeapAdd(heap, newTask, taskCompare);
	}      
    }     

 }


/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
    while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
	Task* newTask;
	Task* firstTask;
	char name[TASK_NAME_SIZE], filename[100], *newLine;
	int priority;
	FILE *filePtr;
	switch (command)
	{
	case 'l': /* load the list from the file */
		printf("Please enter the filename: ");
		
		if (fgets(filename, sizeof(filename), stdin) != NULL)
		{
			/* remove trailing newline character */
			newLine = strchr(filename, '\n');
			if (newLine)
				*newLine = '\0';
		}
		
		filePtr = fopen(filename, "r");
		if (filePtr == NULL) {
			fprintf(stderr, "Cannot open %s\n", filename);
			break;
		}
		
		listLoad(list, filePtr);
		
		fclose(filePtr);
		printf("The list has been loaded from file successfully.\n\n");
		break;	
	case 's': /* save the list to file */
		if (dySize(list) > 0)
		{			
			printf("Please enter the filename: ");
			if (fgets(filename, sizeof(filename), stdin) != NULL)
			{				
				newLine = strchr(filename, '\n');
				if (newLine)
					*newLine = '\0';
			}			
			filePtr = fopen(filename, "w");
			if (filePtr == NULL) {
				fprintf(stderr, "Cannot open %s\n", filename);
				break;
			}		
			listSave(list, filePtr);			
			fclose(filePtr);
			printf("The list has been saved into the file successfully.\n\n");
		}
		else
			printf("Your to-do list is empty!\n\n");

		break;
	case 'a': /* add new task */
		printf("Please enter the task description: ");
		
		if (fgets(name, sizeof(name), stdin) != NULL)
		{			
			newLine = strchr(name, '\n');
			if (newLine)
				*newLine = '\0';
		}
		
		do {
			printf("Please enter the task priority (0-999): ");
			scanf("%d", &priority);
		} while (!(priority >= 0 && priority <= 999));

		while (getchar() != '\n');		
		newTask = taskNew(priority, name);
		dyHeapAdd(list, newTask, taskCompare);
		printf("The task '%s' has been added to your to-do list.\n\n", name);
		break;

	case 'g': /* get the first task */
		if (dySize(list) > 0)
		{
			firstTask = (Task*)dyHeapGetMin(list);
			printf("Your first task is: %s\n\n", firstTask->name);
		}
		else
			printf("Your to-do list is empty!\n\n");

		break;

	case 'r': /* remove the first task */
		if (dySize(list) > 0)
		{
			firstTask = (Task*)dyHeapGetMin(list);
			dyHeapRemoveMin(list, taskCompare);
			printf("Your first task '%s' has been removed from the list.\n\n", firstTask->name);		
			free(firstTask);
		}
		else
			printf("Your to-do list is empty!\n\n");
		break;

	case 'p': /* print the list */
		if (dySize(list) > 0)
		{
			listPrint(list);
		}
		else
			printf("Your to-do list is empty!\n\n");

		break;
	case 'e': /* exit the program */
		printf("Bye!\n\n");
		break;

	}
	   
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
    dyDelete(list);
    return 0;
}
