/*****************************************************
**Program Filename : Barbarian.cpp
**Author : Brent Doil
**Date : 4 / 28 / 2016
**Description : Barbarian class implementation
*********************************************************/

#include "Barbarian.hpp"

/*********************************************************************
** Function: Barbarian constructor
** Description: Sets armor and strength
*********************************************************************/
Barbarian::Barbarian()
{
	armor = 0;
	strength = 12;
	alive = true;
	}
/*********************************************************************
** Function: attack
** Description: Rolls 2d6 to return attack roll for Barbarian.
*********************************************************************/
int Barbarian::attack()
{
	int rollOne = (rand() % 6) + 1;
	int rollTwo = (rand() % 6) + 1;
	int attackRoll = rollOne + rollTwo;
	std::cout << "Barbarian attacks for: " << attackRoll << ".\n";
	return attackRoll;
}
/*********************************************************************
** Function: defend
** Description: Defends against an attack argument using 2d6 defense
** roll and armor
*********************************************************************/
int Barbarian::defend(int attack)
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
			alive = false;
			std::cout << "Barbarian defends for " << defenseRoll << " and has " << armor << " armor.\n";
			std::cout << "Barbarian is KO'd.\n";
			return strengthLost;
		}
		else
		{
			std::cout << "Barbarian defends for " << defenseRoll << " and has " << armor << " armor.\n";
			std::cout << "Barbarian loses " << strengthLost << " strength and has " << strength << " strength remaining.\n";
			return strengthLost;
		}
	}
	//If damage is not donne
	else
	{
		std::cout << "Barbarian defends for " << defenseRoll << " and has " << armor << " armor.\n";
		std::cout << "Barbarian takes no damage from the attack and has " << strength << " strength remaining.\n";
		return strengthLost;
	}
}
/*********************************************************************
** Function: isAlive
** Description: Returns alive, true or false
*********************************************************************/
bool Barbarian::isAlive()
{
	return alive;
}
void Barbarian::setName(std::string n)
{
	this->name = n;
}
