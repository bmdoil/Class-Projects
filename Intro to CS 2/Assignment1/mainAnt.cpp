/*******************************************************
**Program Filename: mainAnt.cpp
**Author: Brent Doil
**Date: 4/9/2016
**Description: Main function for Assignment1
*********************************************************/

#include "Ant.hpp"
#include "CS162.hpp"

int main()
{	
	if (menu()) //If option to start program is chosen
	{
		//Input logic validation by validInt function
		int xCoord = validInt("How many Columns? ", "Please enter a positive integer: ", 1);
		int yCoord = validInt("How many Rows? ", "Please enter a positive integer: ", 1);
		int steps = validInt("How many steps would you like to run?\nSuggestions... 100: 1000: 10000: ", "Please enter a positive integer: ", 1);
		int startType = validInt("How will you place the Ant? [1]Random or [2]User? ", "Please enter 1 or 2: ", 1, 2);

		Grid newGrid(xCoord, yCoord); //Instantiate grid
		Ant ant; //Instantiate ant

		if (startType == 1)
		{
			ant.addAnt(&newGrid);
		}
		//User input, bool used to validate starting coordinates are on grid
		else
		{
			int startX = validInt("Where will the ant start? X: ", "Please enter a valid coordinate: ", 0);
			int startY = validInt("Y: ", "Please enter a valid coordinate: ", 0);
			bool play = ant.addAnt(&newGrid, startX, startY);
			while (!play)
			{
				int startX = validInt("Where will the ant start?\n X: ", "Please enter a valid coordinate: ", 0);
				int startY = validInt("Y: ", "Please enter a valid coordinate: ", 0);
				play = ant.addAnt(&newGrid, startX, startY);
			}
		}

		newGrid.printGrid(); //Print initial grid	

		for (int i = 0; i < steps; i++) //Move ant and print grid for n steps
		{
			ant.moveAnt();
			newGrid.printGrid();
		}
		std::cout << "\n\n" << ant.moveCount() << " Moves.";
	}
	else return 0; //If menu returns false end program
	return 0;
}

