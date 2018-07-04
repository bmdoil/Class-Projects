/*******************************************************
**Program Filename: CS162.cpp
**Author: Brent Doil
**Date: 4/9/2016
**Description: CS162 helper functions implementation
*********************************************************/

#include "CS162.hpp"

//Function to validate integer input. Can set min and max allowable integer
int validInt(const std::string &prompt, const std::string &failmsg, int min, int max)
{

	int input;
	bool invalid = true; //flag
	std::cout << prompt; //Print prompt
	while (invalid) //Use string stream to parse input. If invalid, try again.
	{
		std::string line;
		std::getline(std::cin, line);

		std::istringstream is(line);

		char dummy = '\0'; //Look for enter
		if (!(is >> input) || (is >> std::ws && is.get(dummy)) || input < min || input > max) //Check for cases of failure
			std::cout << failmsg; //Print fail message
		else
			invalid = false;
	}
	return input;
}

//Menu function returns true or false depending on user input
bool menu()
{
	std::cout << "Welcome to Langton's Ant!\n";
	int choice;
		
	std::string description = "Langton's Ant is a cellular automaton with a simple set of rules.\n"
		"Squares on the grid are '.' or '#'. \nAn 'ant' (*) is placed on the grid."
		 " \nIt can move in one of four directions.\nAt a '.' square, it turns right, flips the"
		" square to '#', and moves forward. \nAt a '#' square, it turns left, flips the "
		 "square to '.', and moves forward. \nThis repeats for the given number of iterations. \n\n";

	std::string options = "[1] For a description of the program: \n[2] To begin the program: \n[3] To exit: \n";
		
	while (true)
	{
		choice = validInt(options, "Please enter a valid choice: ", 1, 3);
		switch (choice)
		{
		case 1: std::cout << description;
			break;
		case 2: return true;
			break;
		case 3: return false;
		}
	}	
}