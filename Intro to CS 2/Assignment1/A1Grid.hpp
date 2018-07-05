/*******************************************************
**Program Filename: A1Grid.hpp
**Author: Brent Doil
**Date: 4/9/2016
**Description: A1Grid class interface
*********************************************************/


#ifndef A1GRID_HPP
#define A1GRID_HPP

#include <cstddef>
const char BLACKSQ = '#'; //Represents a black square
const char WHITESQ = '.'; //Represents a white square

class Grid {
private:
	char** grid = NULL;	//Points to 2d grid
	int columnNum; 
	int rowNum;
	

public:
	
	Grid(const int x, const int y); //Instantiates grid 
	~Grid(); //Frees memory 
	void printGrid();
	void setSquare(const int x, const int y, const char squareType); //Set square at [x][y] to squareType	
	char getSquare(const int x, const int y); //Return content of square at [x][y]
	int getColNum();
	int getRowNum();

};

#endif // !A1GRID_HPP

