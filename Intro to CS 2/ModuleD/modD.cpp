/*******************************************************
**Program Filename: modD.cpp
**Author: Brent Doil
**Date: 4/28/2016
**Description: Main function for moduleD
*********************************************************/

#include <iostream>
#include <sstream>
#include <string>

#include "Grid.hpp"
#include "CS162.hpp"


int main()
{	
	
	int xCoord = validNum("How many Columns? ", "Please enter a positive integer: ", 1);	
	int yCoord = validNum("How many Rows? ", "Please enter a positive integer: ", 1);
	int antNum = validNum("How many ants will be added? ", "Please enter a positive integer (but don't add more than Columns * Rows): ", 1, xCoord * yCoord);
	int doodleNum = validNum("How many doodlebugs will be added?", "Please enter a positive integer (but don't add more than Columns * Rows): ", 1, xCoord * yCoord);
	int steps = validNum("How many steps through the grid should be run? ", "Please enter a positive integer: ", 1);
	Grid newGrid(xCoord, yCoord); //Instantiate grid
	newGrid.addCritter(antNum,'A');
	newGrid.addCritter(doodleNum, 'D');

	newGrid.print(); //Print initial grid
	int completeSteps = 0;
	for (int i = 0; i < steps; i++)
	{
		//if (!newGrid.fullGrid())
	//	{
			completeSteps++;
			newGrid.moveCritters();
			newGrid.print();
	//	}
	//	else
	//	{
	//		std::cout << "Grid full after " << completeSteps << " completed steps!\n";
	//		return 0;
	//	}		
	}
	return 0;
}
