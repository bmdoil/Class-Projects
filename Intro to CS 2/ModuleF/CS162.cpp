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
	std::cout << "Welcome to the Fight Simulator!\n";
	int choice;
		
	std::string description = "This program pits two different characters together in a battle.\nChoose your matchup!\n\n";

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
void description()
{
	std::cout << "[1] Baba Yaga vs. Barbarian\n[2] Baba Yaga vs. Blue Men\n[3] Baba Yaga vs. Harry Potter\n[4] Baba Yaga vs. Medusa\n[5] Barbarian vs. Blue Men\n[6] Barbarian vs. Harry Potter\n"
		<< "[7] Barbarian vs. Medusa\n[8] Blue Men vs. Harry Potter\n[9] Blue Men vs. Medusa\n[10] Harry Potter vs. Medusa\n[0] To Exit\n";
}