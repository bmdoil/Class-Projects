/*******************************************************
**Program Filename: Ant.hpp
**Author: Brent Doil
**Date: 4/9/2016
**Description: Ant class interface
*********************************************************/

#ifndef ANT_HPP
#define ANT_HPP

#include "A1Grid.hpp"
#include <ctime>
#include <cstdlib>



class Ant {
private:
	Grid* gridPtr; //Pointer to grid initialized with addCritter method
	int moveNum; //Moves counter
	int currentX;
	int currentY;
	int direction;	
	char ant; //Represents the ant on the grid
	char squareColor; //Color of square that ant is on
	
public:
	Ant();	
	bool addAnt(Grid* myGrid); //Adds ant to random location on grid
	bool addAnt(Grid* myGrid, int x, int y); //Adds ant to location given by x and y
	void moveAnt(); //Logic to move ant on grid
	int moveCount(); //Returns moveNum
	char setColor(int x,int y); //Saves content of [x][y] to squareColor
	char getColor(); //Returns squareColor
	enum antFacing { UP, DOWN, LEFT, RIGHT };
	void validMove(int &currentX, int &currentY); //Checks if move is valid on grid, if not, wraps ant around grid
};

#endif // !ANT_HPP

