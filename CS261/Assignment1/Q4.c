/* CS261- Assignment 1 - Q.4*/
/* Name: Brent Doil
 * Date: 6/26/2016
 * Solution description: Sort elements of a struct
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/   
	int i, j;
	int tempScore;
	int tempId;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < (n - 1); j++)
		{
			if (students[j].score > students[j + 1].score)
			{
				tempScore = students[j].score;
				tempId = students[j].id;

				students[j].score = students[j + 1].score;
				students[j].id = students[j + 1].id;

				students[j + 1].score = tempScore;
				students[j + 1].id = tempId;

			}
		}
	}
}

int main(){
    /*Declare an integer n and assign it a value.*/
	int n = 20;
    /*Allocate memory for n students using malloc.*/
	struct student* studList = malloc(n * sizeof(struct student));
    /*Generate random IDs and scores for the n students, using rand().*/
	int id;
	for (int i = 0; i < n; i++)
	{
		id = (rand() % n) + 1;
		for (int j = 0; j <= i; j++) //loop through id from j to i, reroll random if id already exists, then start loop over
		{
			if (studList[j].id == id)
			{
				id = (rand() % n) + 1;
				j = -1;
			}
		}

		studList[i].score = (rand() % 101);
		studList[i].id = id;
	}
    /*Print the contents of the array of n students.*/

	for (int i = 0; i < n; i++)
	{
		int id = studList[i].id;;
		int score = studList[i].score;
		printf("ID:%d  Score:%d\n", id, score);
		
	}
    /*Pass this array along with n to the sort() function*/
	sort(studList, n);
	printf("Sorted students\n");
    /*Print the contents of the array of n students.*/
	for (int i = 0; i < n; i++)
	{
		int id = studList[i].id;;
		int score = studList[i].score;
		printf("ID:%d  Score:%d\n", id, score);

	}
    return 0;
}
