/* CS261- Assignment 2 - stack.c: Stack application
* Name: Brent Doil
* Date: 7/10/2016
* Solution description: Stack application to check if parentheses are balanced.
*/

#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"
#include <assert.h>

/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	int capacity = 50;
	char next;

	assert(s != 0);

	DynArr* arr = newDynArr(capacity);

	do
	{
		next = nextChar(s);
		/*Push left brackets on stack*/
		if ((next == '(') || (next == '{') || (next == '['))
		{
			pushDynArr(arr, next);
		}

		/*Checks if brackets are balanced*/
		if ((next == ')') || (next == '}') || (next == ']'))
		{
			if (!sizeDynArr(arr))		
			{
				return 0;				
			}

			else
			{
				if (next == ')')
				{
					if (topDynArr(arr) == '(')
					{
						popDynArr(arr);
					}
				}
				if (next == '}')
				{
					if (topDynArr(arr) == '{')
					{
						popDynArr(arr);
					}
				}

				if (next == ']')
				{
					if (topDynArr(arr) == '[')
					{
						popDynArr(arr);
					}
				}
			}
		}
	} while (next != '\0');
									
	if (sizeDynArr(arr) == 0)
	{
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

