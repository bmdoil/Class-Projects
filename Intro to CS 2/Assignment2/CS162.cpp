/*******************************************************
**Program Filename: CS162.cpp
**Author: Brent Doil
**Date: 4/16/2016
**Description: CS162 helper functions implementation
*********************************************************/

#include "CS162.hpp"

//Function to validate integer input. Can set min and max allowable integer
int validNum(const std::string &prompt, const std::string &failmsg, int min, int max)
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
double validNum(const std::string &prompt, const std::string &failmsg, double min, double max)
{

	double input;
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
	std::cout << "Let's Build a Shopping List!\n";
	int choice;
		
	std::string description = "This program builds a shopping list of items. You can add items to the list,\nremove items, and display the contents of the list. \n\n";

	std::string options = "[1] For a description of the program: \n[2] To begin the program: \n[3] To exit: \n";
		
	while (true)
	{
		choice = validNum(options, "Please enter a valid choice: ", 1, 3);
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