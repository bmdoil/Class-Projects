/* CS261- Assignment 1 - Q. 0*/
/* Name: Brent Doil	
 * Date: 6/21/2016
 * Solution description: Pointer fun by Brent.
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
	printf("Value pointed to is: %d\n", *iptr);
     /*Print the address pointed to by iptr*/
	printf("Address pointed to is: %p\n", iptr);
     /*Print the address of iptr itself*/
	printf("Address of pointer itself is: %p\n", &iptr);
}


int main()
{
    
    //declare an integer x
	int x = 5;
    //print the address of x
	printf("Address of x is: %p\n", &x);
    //Call fooA() with the address of x
	fooA(&x);
    //print the value of x
	printf("Value of x is: %d\n", x);
    return 0;
}
