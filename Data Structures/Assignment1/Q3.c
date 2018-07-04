/* CS261- Assignment 1 - Q.3*/
/* Name: Brent Doil
 * Date: 6/26/2016
 * Solution description: Q3, sorting implementation
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>


void sort(int* number, int n){
     /*Sort the given array number , of length n*/ 
	//Bubble sort
	int i, j, temp;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < (n - 1); j++)
		{
			if (number[j] > number[j + 1])
			{
				temp = number[j];
				number[j] = number[j + 1];
				number[j + 1] = temp;
			}
		}
	}

}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
	int n = 20;
    /*Allocate memory for an array of n integers using malloc.*/
	int* array = malloc(n * sizeof(int));
    /*Fill this array with random numbers, using rand().*/
	for (int i = 0; i < n; i++)
	{
		array[i] = rand() % 1000;
	}
    /*Print the contents of the array.*/
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", array[i]);
	}
    /*Pass this array along with n to the sort() function of part a.*/
	sort(array, n);
    /*Print the contents of the array.*/    
	printf("Sorted Array\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", array[i]);
	}
	free(array);
    return 0;
}
