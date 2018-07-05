/*******************************************************
**Program Filename: Grid.cpp
**Author: Brent Doil
**Date: 4/28/2016
**Description: Grid class implementation
*********************************************************/

#include "Grid.hpp"
#include <iostream>



/*********************************************************************
** Function: Grid constructor
** Description: Sets column and row size. Initializes memory of 2d array 
** Pre-Conditions: x and y > 0 
*********************************************************************/
Grid::Grid(const int x, const int y)
{
	srand(time(NULL));
	columns = x;
	rows = y;	

//Create initial memory chunk
	newGrid = new Critter**[y];
//Create rest of memory
	for (int i = 0; i < y; i++)
	{
		newGrid[i] = new Critter*[x];
	}
//Fill array with blanks, specified by a '.'
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			newGrid[i][j] = NULL;
		}
	}
}
/*********************************************************************
** Function: Grid destructor
** Description: Deletes memory allocated by constructor
*********************************************************************/
Grid::~Grid()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (newGrid[i][j] != NULL)
			{
				delete newGrid[i][j];
				newGrid[i][j] = NULL;
			}
		}
		delete[] newGrid[i];
		
	}
	delete[] newGrid;
	newGrid = NULL;
}


/*********************************************************************
** Function: print
** Description: Prints state of grid to console
*********************************************************************/
void Grid::print()
{
	
	std::cout << ' ';
	for (int h = 0; h <= columns; h++)
		std::cout << " - ";
	std::cout << std::endl;
	for (int i = 0; i < rows; i++)
	{
		std::cout << " |";
		for (int j = 0; j < columns; j++)
		{
			if (newGrid[i][j] != NULL)
				std::cout << ' ' << newGrid[i][j]->getCritter() << ' ';
			else std::cout << " . ";
			if (j == (columns - 1))
				std::cout << "|" << std::endl;
		}
	}
	std::cout << ' ';
	for (int k = 0; k <= columns; k++)
		std::cout << " - ";

	std::cout << std::endl;
}
/*********************************************************************
** Function: addCritter 
** Description: Takes initial number of Critters and critter type
** Adds Ants or Doodlebugs to grid at random locations
*********************************************************************/
void Grid::addCritter(int init, char critType) //Random
{
	if (critType == 'A')
	{
		while (antNum < init)
		{
			
			int randX = rand();
			int randY = rand();
			int x = randX % (getCol());
			int y = randY % (getRow());
			if (newGrid[x][y] == NULL)
			{

				newGrid[x][y] = new Ant;
				antNum++;
			}
		}
	}
	else if (critType == 'D')
	{
		while (doodleNum < init)
		{
			int randX = rand();
			int randY = rand();
			int x = randX % (getCol());
			int y = randY % (getRow());
			if (newGrid[x][y] == NULL)
			{

				newGrid[x][y] = new Doodlebug;
				doodleNum++;
			}
		}
	}
	else return;
}
/*********************************************************************
** Function: moveCritters
** Description: Loops through 2d array to randomly move Critter in 
** 1 of 4 directions. Critter attempts to breed after each successful move
*********************************************************************/
void Grid::moveCritters()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (newGrid[i][j] != NULL)
			{
				newGrid[i][j]->setMoved(false);
			}
		}
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (newGrid[i][j] != NULL)
			{
				int direction = rand() % 4;
				
				if (direction == RIGHT)
				{
					if (checkMove(i, j, RIGHT))
					{
						if (newGrid[i][j]->Starve())
						{
							delete newGrid[i][j];
							newGrid[i][j] = NULL;
							return;
						}
						else
						{
							newGrid[i][j]->setMoved(true);
							newGrid[i][j + 1] = newGrid[i][j];
							newGrid[i][j] = newGrid[i][j]->Breed(); //Either sets old space to NULL or creates a new Critter depending on move count
						}		
					}
				}
				else if (direction == LEFT)
				{
					if (checkMove(i, j, LEFT))
					{
						if (newGrid[i][j]->Starve())
						{
							delete newGrid[i][j];
							newGrid[i][j] = NULL;
							return;
						}
						else
						{
							newGrid[i][j]->setMoved(true);
							newGrid[i][j - 1] = newGrid[i][j];
							newGrid[i][j] = newGrid[i][j]->Breed(); //Either sets old space to NULL or creates a new Critter depending on move count
						}
					}
				}
				else if (direction == DOWN)
				{
					if (checkMove(i, j, DOWN))
					{
						
						if (newGrid[i][j]->Starve())
						{
							delete newGrid[i][j];
							newGrid[i][j] = NULL;
							return;
						}
						else
						{
							newGrid[i][j]->setMoved(true);
							newGrid[i + 1][j] = newGrid[i][j];
							newGrid[i][j] = newGrid[i][j]->Breed(); //Either sets old space to NULL or creates a new Critter depending on move count
						}
					}
				}
				else if (direction == UP)
				{
					if (checkMove(i, j, UP))
					{
						if (newGrid[i][j]->Starve())
						{
							delete newGrid[i][j];
							newGrid[i][j] = NULL;
							return;
						}
						else
						{
							newGrid[i][j]->setMoved(true);
							newGrid[i - 1][j] = newGrid[i][j];
							newGrid[i][j] = newGrid[i][j]->Breed(); //Either sets old space to NULL or creates a new Critter depending on move count
						}
					}
					}
				}
			}
		}
	}

	


/*********************************************************************
** Function: getCol
** Description: Returns columns
*********************************************************************/
int Grid::getCol()
{
	return columns;
}
/*********************************************************************
** Function: getRow
** Description: Returns rows
*********************************************************************/
int Grid::getRow()
{
	return rows;
}
/*********************************************************************
** Function: checkMove
** Description: Takes x,y coords and direction, checks if direction of 
** possible move is valid. If yes, returns true.
*********************************************************************/
bool Grid::checkMove(int x, int y, int dir)
{
	//If moving a doodlebug into an ant, call eat.
	if (dir == RIGHT)
	{
		
		int newY = y + 1;

		if (newY < 0 || newY > getRow() - 1)
			return false;
		else if (newGrid[x][newY] != NULL)
		{
			if ((newGrid[x][y]->getCritter() == 'D') && newGrid[x][newY]->getCritter() == 'A')
			{
				newGrid[x][y]->Eat();
				
				//Put this into an Eat function in Ant?
				delete newGrid[x][newY];
				newGrid[x][newY] = NULL;
				return true;
			}
			else return false;
		}
		else return true;
	}
	else if (dir == LEFT)
	{
		
		int newY = y - 1;

		if (newY < 0 || newY > getRow() - 1)
			return false;
		else if (newGrid[x][newY] != NULL)
		{
			if ((newGrid[x][y]->getCritter() == 'D') && newGrid[x][newY]->getCritter() == 'A')
			{
				newGrid[x][y]->Eat();
				//Put this into an Eat function in Ant?
				delete newGrid[x][newY];
				newGrid[x][newY] = NULL;
				return true;
			}
			else return false;
		}
		else return true;
	}
	else if (dir == DOWN)
	{
		int newX = x + 1;
		

		if (newX < 0 || newX > getCol() - 1)
			return false;
		else if (newGrid[newX][y] != NULL)
		{
			if ((newGrid[x][y]->getCritter() == 'D') && newGrid[newX][y]->getCritter() == 'A')
			{
				newGrid[x][y]->Eat();
				//Put this into an Eat function in Ant?
				delete newGrid[newX][y];
				newGrid[newX][y] = NULL;
				return true;
			}
			else return false;
		}
		else return true;
	}
	else if (dir == UP)
	{
		int newX = x - 1;
		

		if (newX < 0 || newX > getCol() - 1)
			return false;
		else if (newGrid[newX][y] != NULL)
		{
			if ((newGrid[x][y]->getCritter() == 'D') && newGrid[newX][y]->getCritter() == 'A')
			{
				newGrid[x][y]->Eat();
				//Put this into an Eat function in Ant?
				delete newGrid[newX][y];
				newGrid[newX][y] = NULL;
				return true;
			}
			else return false;
		}
		else return true;
	}
	return false; //Return falls if it falls through
	
}
/*********************************************************************
** Function: fullGrid
** Description: Checks if grid is full of Critters. If yes, returns true
** Else returns false.
*********************************************************************/
bool Grid::fullGrid()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (newGrid[i][j] == NULL)
			{
				full = false;
				return full;
			}
		}
	}
	full = true;
	return full;
}

