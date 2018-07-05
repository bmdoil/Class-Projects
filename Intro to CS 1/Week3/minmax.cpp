/*********************************************************************
** Author: Brent Doil	
** Date: 1/17/2016
** Description: Assignment 3.a minmax.cpp
*********************************************************************/

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	//Declare global variables
	int numberEntered;
	int firstNum;
	int min;
	int max;
	

	//Prompt user for a number
	cout << "How many integers would you like to enter (>= 1)?\n";
	cin >> numberEntered;

	//Prompt user to enter list of integers
	cout << "Please enter " << numberEntered << " integers.\n";
	cin >> firstNum;

	// Initialize min and max values to first integer entered to allow comparison inside for loop.
	min = max = firstNum;
	

	// Run loop 'numberEntered - 1' times
	for (int i = 0; i < numberEntered - 1; i++)
	{
		int currentNum;
		cin >> currentNum;
		
		// Update min and max variables while iterating through the for loop to determine overall min and max.
		if (currentNum < min)
			min = currentNum;

		if (currentNum > max)
			max = currentNum;
	}

	//Output min and max
	cout << "min: " << min << endl;
	cout << "max: " << max << endl;

	return 0;
}
