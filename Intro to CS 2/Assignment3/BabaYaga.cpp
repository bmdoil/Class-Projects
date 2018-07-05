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
	strength = 12;
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
	std::cout << "Baba Yaga attacks for: " << attackRoll << ".\n";
	int siphon = attackRoll / 3;
	std::cout << "Baba Yaga siphons " << siphon << " life from her enemy!\n";
	strength += siphon;
	std::cout << "Baba Yaga's strength is now " << strength << ".\n";
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
				std::cout << "Baba Yaga defends for " << defenseRoll << " and has " << armor << " armor.\n";
				std::cout << "Baba Yaga is KO'd.\n";
				return strengthLost;			
		}
		else
		{
			std::cout << "Baba Yaga defends for " << defenseRoll << " and has " << armor << " armor.\n";
			std::cout << "Baba Yaga loses " << strengthLost << " strength and has " << strength << " strength remaining.\n";
			return strengthLost;
		}
	}
	//If damage is not done
	else
	{
		std::cout << "Baba Yaga defends for " << defenseRoll << " and has " << armor << " armor.\n";
		std::cout << "Baba Yaga takes no damage from the attack and has " << strength << " strength remaining.\n";
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
void BabaYaga::setName(std::string n)
{
	this->name = n;
}
