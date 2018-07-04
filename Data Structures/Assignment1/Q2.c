/* CS261- Assignment 1 - Q.2*/
/* Name: Brent Doil
 * Date: 6/24/2016
 * Solution description: Shows how pointers are used as function parameters
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
	*a = *a * 2;
    /*Set b to half its original value*/
	*b = *b / 2;
    /*Assign a+b to c*/
	c = *a + *b;
    /*Return c*/
	return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
	int x = 5;
	int y = 6;
	int z = 7;
	int value;
    /*Print the values of x, y and z*/
	printf("x: %d\ny: %d\nz: %d\n", x, y, z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
	value = foo(&x, &y, z);
    /*Print the value returned by foo*/
	printf("Value returned: %d\n", value);
    /*Print the values of x, y and z again*/
	printf("x: %d\ny: %d\nz: %d\n", x, y, z);
    /*Is the return value different than the value of z?  Why?*/
	printf("Return value is different than the value of z because z was passed by value into the function foo. Foo did not change the original value of z, but made a copy of it, performed an operation, and returned the value.\n");
    return 0;
}
    
    
