#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "Board.hpp"

class TicTacToe
{
private:
	Board newBoard;
	std::string player;
	
public:
	TicTacToe(std::string player);
	void play();
};



#endif
