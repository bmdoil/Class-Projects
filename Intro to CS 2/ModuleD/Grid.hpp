/*******************************************************
**Program Filename: Grid.hpp
**Author: Brent Doil
**Date: 4/28/2016
**Description: Grid class interface
*********************************************************/


#ifndef GRID_HPP
#define GRID_HPP
#include "Ant.hpp"
#include "Doodlebug.hpp"
#include <cstddef>


class Grid {
private:
	Critter*** newGrid = NULL;
	enum direction { DOWN, UP, LEFT, RIGHT };
	
	int columns;
	int rows;
	int critterNum = 0;
	int antNum = 0;
	int doodleNum = 0;
	
	bool full = false;

public:
	
	Grid(const int x, const int y);
	~Grid();

	void print();	
	void addCritter(int init, char critType);	
	void moveCritters();

	int getCol();
	int getRow();
	//int getMoves();

	bool fullGrid();
	bool checkMove(int x, int y, int direction);	

};

#endif // !GRID_HPP

