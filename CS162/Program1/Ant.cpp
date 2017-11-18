/*******************************************************
**Program Filename: Ant.cpp
**Author: Brent Doil
**Date: 4/9/2016
**Description: Ant class implementation
*********************************************************/

#include "Ant.hpp"


/*********************************************************************
** Function: Ant constructor
** Description: Seeds RNG, sets direction to DOWN, moveNum to 0 
** and sets ant
*********************************************************************/
Ant::Ant()
{
	srand(time(NULL));
	direction = DOWN;
	moveNum = 0;
	ant = '*';
	

}
/*********************************************************************
** Function: addAnt (Random)
** Description: Adds the critter to a grid via pointer to grid.
** Sets gridPtr to the passed argument. Sets square color and
** Randomly places ant on grid
*********************************************************************/
bool Ant::addAnt(Grid* myGrid)
{
	
	gridPtr = myGrid;
	int randNum = rand();
	currentX = randNum % (gridPtr->getColNum());
	currentY = randNum % (gridPtr->getRowNum());
	setColor(currentX, currentY);
	gridPtr->setSquare(currentX, currentY, ant);
	return true;
	
}
/*********************************************************************
** Function: addAnt (User)
** Description: Adds the critter to a grid via pointer to grid.
** Sets gridPtr to the passed argument. Sets square color and
** Accepts user coordinates to place ant on grid. Rejects invalid [x][y]
*********************************************************************/
bool Ant::addAnt(Grid* myGrid, int x, int y)
{

	gridPtr = myGrid;
	if (x < 0 || y < 0)
		return false;
	else if (x > gridPtr->getColNum() - 1 || y > gridPtr->getRowNum() - 1)
		return false;
	else
	{
		currentX = x;
		currentY = y;
		setColor(currentX, currentY);
		gridPtr->setSquare(currentX, currentY, ant);
		return true;
	}
	
}
/*********************************************************************
** Function: moveAnt
** Description: Moves ant in one of 4  directions based on logic for 
** Langton's Ant automaton Increments moveNum. 
*********************************************************************/
void Ant::moveAnt()
{
	moveNum++;
	
		if (direction == DOWN)
		{
			if (getColor() == WHITESQ)
			{
				direction = LEFT; //Turn right 90
				gridPtr->setSquare(currentX, currentY, BLACKSQ); //Change square to black
				currentY--; //LEFT = -1 Y
				validMove(currentX, currentY);
				setColor(currentX, currentY); //Remember color
				gridPtr->setSquare(currentX, currentY, ant); //Place ant
				
			}
			else if (getColor() == BLACKSQ)
			{
				direction = RIGHT; //Turn left 90
				gridPtr->setSquare(currentX, currentY, WHITESQ); //Change square to white
				currentY++; //RIGHT = +1 Y
				validMove(currentX, currentY);
				setColor(currentX, currentY); //Remember color
				gridPtr->setSquare(currentX, currentY, ant); //Place ant
				
			}
		}
		else if (direction == UP)
		{
			if (getColor() == WHITESQ)
			{
				direction = RIGHT; //Turn right 90
				gridPtr->setSquare(currentX, currentY, BLACKSQ); //Change square to black
				currentY++; //RIGHT = +1 Y
				validMove(currentX, currentY);
				setColor(currentX, currentY); //Remember color
				gridPtr->setSquare(currentX, currentY, ant); //Place ant
				
			}
			else if (getColor() == BLACKSQ)
			{
				direction = LEFT;
				gridPtr->setSquare(currentX, currentY, WHITESQ); //Change square to white
				currentY--; //LEFT = -1 Y
				validMove(currentX, currentY);
				setColor(currentX, currentY); //Remember color
				gridPtr->setSquare(currentX, currentY, ant); //Place ant
				
			}
		}
		else if (direction == RIGHT)
		{
			if (getColor() == WHITESQ)
			{
				direction = DOWN;
				gridPtr->setSquare(currentX, currentY, BLACKSQ);
				currentX--;
				validMove(currentX, currentY);
				setColor(currentX, currentY);
				gridPtr->setSquare(currentX, currentY, ant);
				
			}
			else if (getColor() == BLACKSQ)
			{
				direction = UP;
				gridPtr->setSquare(currentX, currentY, WHITESQ);
				currentX++;
				validMove(currentX, currentY);
				setColor(currentX, currentY);
				gridPtr->setSquare(currentX, currentY, ant);
				
			}
		}
		else if (direction == LEFT)
		{
			if (getColor() == WHITESQ)
			{
				direction = UP;
				gridPtr->setSquare(currentX, currentY, BLACKSQ);
				currentX++;
				validMove(currentX, currentY);
				setColor(currentX, currentY);
				gridPtr->setSquare(currentX, currentY, ant);
				
			}
			else if (getColor() == BLACKSQ)
			{
				direction = DOWN;
				gridPtr->setSquare(currentX, currentY, WHITESQ);
				currentX--;
				validMove(currentX, currentY);
				setColor(currentX, currentY);
				gridPtr->setSquare(currentX, currentY, ant);
				
			}
		}
		return;
	
}
/*********************************************************************
** Function: moveCount
** Description: Returns counter for number of moves.
*********************************************************************/
int Ant::moveCount()
{
	return moveNum;
}
/*********************************************************************
** Function: setColor
** Description: Sets content of [x][y] to squareColor
*********************************************************************/
char Ant::setColor(int x, int y)
{
	squareColor = gridPtr->getSquare(x, y);
	return squareColor;
}
/*********************************************************************
** Function: getColor
** Description: Returns squareColor
*********************************************************************/
char Ant::getColor()
{
	return squareColor;
}
/*********************************************************************
** Function: checkOnGrid
** Description: If x or y coord is outside grid dimension, wraps to other side of grid
*********************************************************************/
void Ant::validMove(int &currentX, int &currentY)
{
	if (currentX < 0)
	{
		currentX = gridPtr->getColNum() - 1;
	}
	else if (currentY < 0)
	{
		currentY = gridPtr->getRowNum() - 1;
	}
	else if (currentX > gridPtr->getColNum() - 1)
	{
		currentX = 0;
	}
	else if (currentY > gridPtr->getRowNum() - 1)
	{
		currentY = 0;
	}
	return;

}