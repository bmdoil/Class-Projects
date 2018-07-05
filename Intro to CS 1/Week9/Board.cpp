#include <iostream>
#include "Board.hpp"

using namespace std;

//Instantiates the playing board with all spaces set as .
Board::Board()
{
	turnNum = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			board[i][j] = ".";
}
//Takes an x and y coordinate, and the player as arguments. If board space is unoccupied, records move and returns true, else returns false
bool Board::makeMove(int x, int y, std::string player)
{
	if (board[x][y] == ".")
	{
		board[x][y] = player;
		return true;
	}
	else return false;
}
//Logic for win conditions, draw, or whether game is unfinished
int Board::gameState()
{

	turnNum++;
	std::string winner = ".";

	//Tests winning logic for each of the 8 different possible win conditions
	if ((board[0][0] == "x" || board[0][0] == "o") && (board[0][0] == board[0][1]) && (board[0][0] == board[0][2]))
	{
		winner = board[0][0];
	}
	else if ((board[0][0] == "x" || board[0][0] == "o") && (board[0][0] == board[1][0]) && (board[0][0] == board[2][0]))
	{
		winner = board[0][0];
	}
	else if ((board[0][0] == "x" || board[0][0] == "o") && (board[0][0] == board[1][1]) && (board[0][0] == board[2][2]))
	{
		winner = board[0][0];
	}
	else if ((board[0][1] == "x" || board[0][1] == "o") && (board[0][1] == board[1][1]) && (board[0][1] == board[2][1]))
	{
		winner = board[0][1];
	}
	else if ((board[0][2] == "x" || board[0][2] == "o") && (board[0][2] == board[1][2]) && (board[0][2] == board[2][2]))
	{
		winner = board[0][2];
	}
	else if ((board[1][0] == "x" || board[1][0] == "o") && (board[1][0] == board[1][1]) && (board[1][0] == board[1][2]))
	{
		winner = board[1][0];
	}
	else if ((board[2][0] == "x" || board[2][0] == "o") && (board[2][0] == board[2][1]) && (board[2][0] == board[2][2]))
	{
		winner = board[2][0];
	}
	else if ((board[2][2] == "x" || board[2][2] == "o") && (board[2][2] == board[1][1]) && (board[2][2] == board[0][2]))
	{
		winner = board[2][2];
	}
	if (turnNum == 9)
	{
		return DRAW;
	}
	if (winner == "x")
	{
		return X_WON;
	}
	else if (winner == "o")
	{
		return O_WON;
	}
	else return UNFINISHED;

}




//Prints current state of board to screen
void Board::print()
{
	cout << "  " << endl;
	for (int h = 0; h < 3; h++)
	{
		cout << "   " << h;
	};
	cout << endl;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			if (j == 0)
			{
				cout << i << "  ";
			};
			cout << board[i][j] << "   ";
			if (j == 2)
			{
				cout << endl;
			}

		}

}

