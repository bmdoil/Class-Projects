
#include "TicTacToe.hpp"

using namespace std;
//Constructor that takes 'x' or 'o' as an argument for first player
TicTacToe::TicTacToe(std::string firstMove)
{
	player = firstMove;
}
//Logic for playing the game
void TicTacToe::play()
{
	int status = newBoard.gameState();
	int xCoord, yCoord;
	
	do 
	{
		cout << "Player " << player << " please enter your move. ";
		
		cin >> xCoord >> yCoord;
		//Check to see if move is valid
		if (newBoard.makeMove(xCoord, yCoord, player))
		{
			//Record the move
			newBoard.makeMove(xCoord, yCoord, player);
			//Print board state to screen
			newBoard.print();
			//Update status
			status = newBoard.gameState();
			if (player == "X")
			{
				player = "O";
			}
			else player = "X";
		}
		else
		{
			cout << "That square is already taken\n";
		}		
	}
	while (status == UNFINISHED);
	if (status == X_WON)
	{
		cout << "Player X wins!\n";
	}
	else if (status == O_WON)
	{
		cout << "Player O wins!\n";
	}
	else if (status == DRAW)
	{
		cout << "Draw!\n";
	}
}

int main()
{
	std::string player;
	cout << "Choose who goes first, X or O.\n";
	getline(cin, player);
	while ((player != "X") || (player != "O"))
	{
		cout << "Please enter either 'x' or 'o'\n";
		cin >> player;

	}	
	
	TicTacToe newGame(player);
	newGame.play();
	return 0;

		
}