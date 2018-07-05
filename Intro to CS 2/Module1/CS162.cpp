/*******************************************************
**Program Filename: CS162.cpp
**Author: Brent Doil
**Date: 4/9/2016
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
int menu()
{
	
	int choice;
		
	

	std::string options = "[1] Reverse a string: \n[2] Sum an array: \n[3] Calculate a triangular number: \n[4] Exit: \n";
		
	while (true)
	{
		choice = validNum(options, "Please enter a valid choice: ", 1, 4);
		switch (choice)
		{
		case 1: return 1;
			break;
		case 2: return 2;
			break;
		case 3: return 3;
			break;
		case 4: return 4;
		}
	}	
}