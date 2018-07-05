/*****************************************************
**Program Filename : BlueMen.cpp
**Author : Brent Doil
**Date : 4 / 28 / 2016
**Description : Blue Men class implementation
*********************************************************/

#include "BlueMen.hpp"
/*********************************************************************
** Function: Blue Men constructor
** Description: Sets armor and strength
*********************************************************************/
BlueMen::BlueMen()
{
	armor = 3;
	strength = 12;
	alive = true;
	
}
/*********************************************************************
** Function: attack
** Description: Rolls 2d10 to return attack roll for Blue Men
*********************************************************************/
int BlueMen::attack()
{
	int rollOne = (rand() % 10) + 1;
	int rollTwo = (rand() % 10) + 1;
	int attackRoll = rollOne + rollTwo;
	std::cout << "Blue Men attack for: " << attackRoll << ".\n";
	return attackRoll;
}
/*********************************************************************
** Function: defend
** Description: Defends against an attack argument using variable defense
** roll based on current strength, and armor
*********************************************************************/
int BlueMen::defend(int attack)
{
	int* strengthLost = NULL;
	int* defenseRoll = NULL;
	if (strength <= 4)
	{
		int rollOne = (rand() % 6) + 1;
		defenseRoll = &rollOne;
		int lost = attack - *defenseRoll - armor;
		strengthLost = &lost;
	}
	else if (strength <= 8)
	{
		int rollOne = (rand() % 6) + 1;
		int rollTwo = (rand() % 6) + 1;
		int defense = rollOne + rollTwo;
		defenseRoll = &defense;
		int lost = attack - *defenseRoll - armor;
		strengthLost = &lost;
	}
	else
	{
		int rollOne = (rand() % 6) + 1;
		int rollTwo = (rand() % 6) + 1;
		int rollThree = (rand() % 6) + 1;
		int defense = rollOne + rollTwo + rollThree;
		defenseRoll = &defense;
		int lost = attack - *defenseRoll - armor;
		strengthLost = &lost;
	}
	if (*strengthLost > 0)
	{
		strength -= *strengthLost;
		if (strength < 1)
		{
			alive = false;
			std::cout << "Blue Men defend for " << *defenseRoll << " and have " << armor << " armor.\n";
			std::cout << "Blue Men are KO'd.\n";
			return *strengthLost;
		}
		else
		{
			std::cout << "Blue Men defend for " << *defenseRoll << " and have " << armor << " armor.\n";
			std::cout << "Blue Men lose " << *strengthLost << " strength and have " << strength << " strength remaining.\n";
			return *strengthLost;
		}
	}
	//If damage is not donne
	else
	{
		std::cout << "Blue Men defends for " << *defenseRoll << " and has " << armor << " armor.\n";
		std::cout << "Blue Men takes no damage from the attack and has " << strength << " strength remaining.\n";
		return *strengthLost;
	}
}
/*********************************************************************
** Function: isAlive
** Description: Returns alive, true or false
*********************************************************************/
bool BlueMen::isAlive()
{
	return alive;
}
void BlueMen::setName(std::string n)
{
	this->name = n;
}


