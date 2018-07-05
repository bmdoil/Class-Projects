/*******************************************************
**Program Filename: FightLogic.cpp
**Author: Brent Doil
**Date: 4/28/2016
**Description: Fight Logic implementation
*********************************************************/


#include "FightLogic.hpp"


/*********************************************************************
** Function: fightLogic
** Description: Function to resolve combat between two creatures
*********************************************************************/

Creature* fightLogic(Creature* creature1, Creature* creature2)
{
	int round = 1;
	while (creature1->isAlive() && creature2->isAlive() && round <= 50) //Both alive
	{
		round++;
		if (creature1->isAlive()) //Creature 1 alive to attack
		{
			creature2->defend(creature1->attack()); //Creature 1 attacks creature 2
		}
		if (creature2->isAlive()) //Creature 2 alive to attack
		{
			creature1->defend(creature2->attack()); //Creature 2 attacks creature 1
		}
		if (round == 50)
		{
			std::cout << "Draw! Winner is decided by strength remaining.";
			if (creature1->getStrength() > creature1->getStrength())
			{
				return creature1;
			}
			else return creature2;
		}
	}
	if (creature1->isAlive())
	{
		creature1->RoundWin();
		return creature1;
	}
	else
	{
		creature2->RoundWin();
		return creature2;
	}
	
}
