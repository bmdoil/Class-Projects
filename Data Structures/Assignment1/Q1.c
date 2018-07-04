/* CS261- Assignment 1 - Q.1*/
/* Name: Brent Doil
 * Date: 6/21/2016
 * Solution description: Generates random IDs and Numbers in struct
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
	struct student* temp = malloc(sizeof(struct student) * 10);	
     /*return the pointer*/
	return temp;
}

void generate(struct student* students){
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
	
	int id;
	for (int i = 0; i < 10; i++)
	{
		id = (rand() % 10) + 1;
		for (int j = 0; j <= i; j++) //loop through id from j to i, reroll random if id already exists, then start loop over
		{
			if (students[j].id == id)
			{
				id = (rand() % 10) + 1;
				j = -1;
			}
		}
		
		students[i].score = (rand() % 101);
		students[i].id = id;
	}
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/

	for (int i = 0; i < 10; i++)
	{
		int id = students[i].id;;
		int score = students[i].score;
		printf("ID:%d  Score:%d\n", id, score);
	}
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
	int minimum = 101;
	int maximum = -1;
	int sum = 0;
	double average;
	for (int i = 0; i < 10; i++)
	{
		int score = students->score;
		if (score < minimum)
		{
			minimum = score;
		}
		if (score > maximum)
		{
			maximum = score;
		}
		sum += score;
		students++;
	}
	average = sum / 10;
	printf("Minimum: %d\n", minimum);
	printf("Maximum: %d\n", maximum);
	printf("Average: %.0f\n", average);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	free(stud);
	stud = NULL;
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
	stud = allocate();
    /*call generate*/
	generate(stud);
    /*call output*/
	output(stud);
    /*call summary*/
	summary(stud);
    /*call deallocate*/
	deallocate(stud);
    return 0;
}
