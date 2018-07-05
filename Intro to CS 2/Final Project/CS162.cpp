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
	std::cout << "Welcome to C++ Pokemon!\nYou are a Pokemon trainer! Explore the world, collect items and Pokemon,\nand defeat the other Trainers!\n";
	int choice;					

	std::string options = "[1] To begin the program: \n[2] To read a description of the program: \n[3] To see a hint:\n[4] To exit: \n";
		
	while (true)
	{
		choice = validNum(options, "Please enter a valid choice: ", 1, 4);
		switch (choice)
		{
		case 1: return true;
			break;
		case 2: description();
			break;
		case 3: hint();
			break;
		case 4: return false;
		}
	}	
}
void description()
{
	std::cout << "You will explore the Wilderness with your Pokemon and collect items.\nYou need to collect 4 badges to challenge the final boss.\nItems will help you along the way.\n"
		<< "Items are:\n[1]Rare Candy -- Levels up all Pokemon\n[2]Healing Potion -- Heals all Pokemon to max HP\n[3]Pokeball -- Used to catch a wild Pokemon\n[4]Bike -- Used to ride to next Hospital\n[5]Bad Mojo -- Adds another Wildnerness!\n"
		<< "[6]Badge -- Collect all 4!\n[7]Key -- ???\nIf you run out of gold or conscious Pokemon, you LOSE!\nDon't go buying everything, and watch your Pokemon's HP!\nMOVEMENT:\nEach space you arrive at will provide some interesting random interactions.\nSometimes you are given a choice, sometimes not!\n"
		<< "The Hospital and Store are useful to recover after time spent in the Wild.\nTake advantage of them, because a Trainer might be coming up!\nGLHF!\n";
}
void hint()
{
	std::cout << "Red is the final boss. His Pokemon are around level 20.\nIf you find the key, you'll be transported directly to him.\nBe careful though, your Pokemon might not be ready for him!\nGood luck!\n";
}
double floatRand(double min, double max)
{
	double f = (double)rand() / RAND_MAX;
	return min + f * (max - min);
}