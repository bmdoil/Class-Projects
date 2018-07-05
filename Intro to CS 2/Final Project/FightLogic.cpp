/*******************************************************
**Program Filename: FightLogic.cpp
**Author: Brent Doil
**Date: 4/28/2016
**Description: Fight Logic implementation
*********************************************************/


#include "FightLogic.hpp"


/*********************************************************************
** Function: fightLogic
** Description: Function to resolve combat between two Pokemons
*********************************************************************/

Pokemon* fightLogic(Pokemon* Pokemon1, Pokemon* Pokemon2)
{
	int round = 1;
	while (Pokemon1->isAlive() && Pokemon2->isAlive() && round <= 50) //Both alive
	{
		round++;
		if (Pokemon1->isAlive()) //Pokemon 1 alive to attack
		{
			Pokemon2->defend(Pokemon1->attack()); //Pokemon 1 attacks Pokemon 2
		}
		if (Pokemon2->isAlive()) //Pokemon 2 alive to attack
		{
			Pokemon1->defend(Pokemon2->attack()); //Pokemon 2 attacks Pokemon 1
		}
		if (round == 50)
		{
			std::cout << "Draw! Winner is decided by strength remaining.";
			if (Pokemon1->getStrength() > Pokemon1->getStrength())
			{
				return Pokemon1;
			}
			else return Pokemon2;
		}
	}
	if (Pokemon1->isAlive())
	{
		Pokemon1->RoundWin();
		return Pokemon1;
	}
	else
	{
		Pokemon2->RoundWin();
		return Pokemon2;
	}
	
}
