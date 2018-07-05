/*******************************************************
**Program Filename: A1Grid.cpp
**Author: Brent Doil
**Date: 4/9/2016
**Description: A1Grid class implementation
*********************************************************/

#include "A1Grid.hpp"
#include <iostream>



/*********************************************************************
** Function: Grid constructor
** Description: Sets column and row size. Initializes memory of 2d array
** Pre-Conditions: x and y > 0
*********************************************************************/
Grid::Grid(const int x, const int y)
{
	if (x < 1 || y < 1) //Validation
	{
		std::cout << "Can't have a grid of < 1 dimension.";
		return;
	}
	columnNum = x;
	rowNum = y;
	
	//Create initial memory chunk
	grid = new char*[y];
	//Create rest of memory
	for (int i = 0; i < y; i++)
	{
		grid[i] = new char[x];
	}

	for (int i = 0; i < rowNum; i++)
	{
		for (int j = 0; j < columnNum; j++)
		{
			grid[i][j] = WHITESQ;
		}
	}
}

/*********************************************************************
** Function: Grid destructor
** Description: Deletes memory allocated by constructor
*********************************************************************/
Grid::~Grid()
{
	for (int i = 0; i < rowNum; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
	grid = NULL;
}


/*********************************************************************
** Function: printGrid
** Description: Prints state of grid to console
*********************************************************************/
void Grid::printGrid()
{

	std::cout << ' ';
	for (int h = 0; h <= columnNum; h++)
		std::cout << " - ";
	std::cout << std::endl;
	for (int i = 0; i < rowNum; i++)
	{
		std::cout << " |";
		for (int j = 0; j < columnNum; j++)
		{
			std::cout << ' ' << grid[i][j] << ' ';
			if (j == (columnNum - 1))
				std::cout << "|" << std::endl;
		}
	}
	std::cout << ' ';
	for (int k = 0; k <= columnNum; k++)
		std::cout << " - ";

	std::cout << std::endl;
}
/*********************************************************************
** Function: setSquare
** Description: Takes x and y and updates [x][y] to squareType
*********************************************************************/
void Grid::setSquare(const int x, const int y, const char squareType)
{
	grid[x][y] = squareType;
	return;
}

/*********************************************************************
** Function: getColNum
** Description: Returns number of columns
*********************************************************************/
int Grid::getColNum()
{
	return columnNum;
}
/*********************************************************************
** Function: getRowNum
** Description: Returns number of rows
*********************************************************************/
int Grid::getRowNum()
{
	return rowNum;
}
/*********************************************************************
** Function: getSquare
** Description: Returns square at [x][y]
*********************************************************************/
char Grid::getSquare(const int x, const int y)
{	
	return grid[x][y];
}
