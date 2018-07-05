/*********************************************************************
** Author: Brent Doil	
** Date: 1/17/2016	
** Description: Assignment 3.c numGuess.cpp
*********************************************************************/

#include <iostream>

using std::cout;
using std::cin;


int main()
{
	int numToGuess;
	int enteredGuess;
	int guessCount = 0;

	cout << "Enter a number for the player to guess.\n";
	cin >> numToGuess;

	cout << "Enter your guess.\n";
	//Use do-while loop to continually test enteredGuess  while it is not equal to numToGuess
	do
	{
		cin >> enteredGuess;
		if (enteredGuess > numToGuess)
			cout << "Too high - Try again.\n";
		else if (enteredGuess < numToGuess)
			cout << "Too low - Try again.\n";
		guessCount++;

	} while (numToGuess != enteredGuess);
			
	cout << "You guessed it in " << guessCount << " tries.\n";
	return 0;
}