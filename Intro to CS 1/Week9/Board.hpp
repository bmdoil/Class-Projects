#ifndef BOARD_HPP
#define BOARD_HPP
#include <iostream>
#include <sstream>
#include <string>
enum gameState { X_WON, O_WON, DRAW, UNFINISHED };

class Board
{
private:
	std::string board[3][3];
	int turnNum;

public:
	//default constructor
	Board();
	int gameState();
	void print();
	bool makeMove(int xCoord, int yCoord, std::string player);
	
};
#endif // !

