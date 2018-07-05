/*****************************************************
**Program Filename : Harry.cpp
**Author : Brent Doil
**Date : 4 / 28 / 2016
**Description : Harry class implementation
*********************************************************/

#include "Harry.hpp"
/*********************************************************************
** Function: Harry constructor
** Description: Sets armor and strength, and hogwarts ability
*********************************************************************/
Harry::Harry()
{
	armor = 0;
	strength = 10;
	alive = true;
	hogwarts = true;
}
/*********************************************************************
** Function: attack
** Description: Rolls 2d6 to return attack roll for Harry
*********************************************************************/
int Harry::attack()
{
	int rollOne = (rand() % 6) + 1;
	int rollTwo = (rand() % 6) + 1;
	int attackRoll = rollOne + rollTwo;
	std::cout << "Harry attacks for: " << attackRoll << ".\n";
	return attackRoll;
}
/*********************************************************************
** Function: defend
** Description: Defends against an attack argument using 2d6 attack roll
** If strength is reduced to 0 and hogwarts is true, resets strength to
** 10 and sets hogwarts to false
*********************************************************************/
int Harry::defend(int attack)
{
	
	int rollOne = (rand() % 6) + 1;
	int rollTwo = (rand() % 6) + 1;
	int defenseRoll = rollOne + rollTwo;
	int strengthLost = attack - defenseRoll - armor;

	if (strengthLost > 0)
	{
		strength -= strengthLost;
		if (strength < 1)
		{
			if (!hogwarts)
			{
				alive = false;
				std::cout << "Harry defends for " << defenseRoll << " and has " << armor << " armor.\n";
				std::cout << "Harry is KO'd.\n";
				return strengthLost;
			}
			else
			{
				hogwarts = false;
				std::cout << "Harry defends for " << defenseRoll << " and has " << armor << " armor.\n";
				strength = 10;
				std::cout << "Harry recovers! His strength is now " << strength << "!\n";
				return strengthLost;
				
			}
			
		}
		else
		{
			std::cout << "Harry defends for " << defenseRoll << " and has " << armor << " armor.\n";
			std::cout << "Harry loses " << strengthLost << " strength and has " << strength << " strength remaining.\n";
			return strengthLost;
		}
	}
	//If damage is not donne
	else
	{
		std::cout << "Harry defends for " << defenseRoll << " and has " << armor << " armor.\n";
		std::cout << "Harry takes no damage from the attack and has " << strength << " strength remaining.\n";
		return strengthLost;
	}
}
/*********************************************************************
** Function: isAlive
** Description: Returns alive, true or false
*********************************************************************/
bool Harry::isAlive()
{
	return alive;
}
void Harry::setName(std::string n)
{
	this->name = n;
}
