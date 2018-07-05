/*******************************************************
**Program Filename: BabaYaga.cpp
**Author: Brent Doil
**Date: 4/28/2016
**Description: Baba Yaga creature implementation
*********************************************************/

#include "BabaYaga.hpp"
/*********************************************************************
** Function: Baba Yaga constructor
** Description: Sets armor and strength
*********************************************************************/
BabaYaga::BabaYaga()
{
	armor = 3;
	strength = startingStr;
	alive = true;
	
}
/*********************************************************************
** Function: attack
** Description: Rolls 2d6 to return attack roll for Baba Yaga. 
** Siphons 1/3rd of attack into strength.
*********************************************************************/
int BabaYaga::attack()
{
	int rollOne = (rand() % 6) + 1;
	int rollTwo = (rand() % 6) + 1;
	int attackRoll = rollOne + rollTwo;
	damage += attackRoll;
	std::cout << this->getName() << " attacks for: " << attackRoll << ".\n";
	int siphon = attackRoll / 3;
	std::cout << this->getName() << " siphons " << siphon << " life from her enemy!\n";
	strength += siphon;
	std::cout << this->getName() << "'s strength is now " << strength << ".\n";
	return attackRoll;
}
/*********************************************************************
** Function: defend
** Description: Defends against an attack argument using 1d10 defense 
** roll and armor
*********************************************************************/
int BabaYaga::defend(int attack)
{
	int defenseRoll = (rand() % 10) + 1;
	int strengthLost = attack - defenseRoll - armor;
	if (strengthLost > 0)
	{
		strength -= strengthLost;
		if (strength < 1)
		{
			
				alive = false;
				std::cout << this->getName() << " defends for " << defenseRoll << " and has " << armor << " armor.\n";
				std::cout << this->getName() << " is KO'd.\n";
				return strengthLost;			
		}
		else
		{
			std::cout << this->getName() << " defends for " << defenseRoll << " and has " << armor << " armor.\n";
			std::cout << this->getName() << " loses " << strengthLost << " strength and has " << strength << " strength remaining.\n";
			return strengthLost;
		}
	}
	//If damage is not done
	else
	{
		std::cout << this->getName() << " defends for " << defenseRoll << " and has " << armor << " armor.\n";
		std::cout << this->getName() << " takes no damage from the attack and has " << strength << " strength remaining.\n";
		return strengthLost;
	}
}
/*********************************************************************
** Function: isAlive
** Description: Returns alive, true or false
*********************************************************************/
bool BabaYaga::isAlive()
{
	return alive;
}
void BabaYaga::revitalize()
{

	if (this->strength > this->startingStr)
	{
		strength = startingStr;
	}
	// Recover 50% of missing strength rounded down
	int missingStr = startingStr - strength;
	strength += (1 / 2) * missingStr;
}
