/*****************************************************
**Program Filename : Medusa.cpp
**Author : Brent Doil
**Date : 4 / 28 / 2016
**Description : Medusa class implementation
*********************************************************/

#include "Medusa.hpp"

/*********************************************************************
** Function: Medusa constructor
** Description: Sets armor and strength.
*********************************************************************/
Medusa::Medusa()
{
	armor = 3;
	strength = startingStr;
	alive = true;
}
/*********************************************************************
** Function: attack
** Description: Rolls 2d6 to return attack roll for Medusa. 
** If a 12 is rolled, Medusa instantly KO's the target by rolling 
** a massive attack.
*********************************************************************/
int Medusa::attack()
{
	//2d6 roll 
	int rollOne = (rand() % 6) + 1;
	int rollTwo = (rand() % 6) + 1;
	int attackRoll = rollOne + rollTwo;
	damage += attackRoll;
	if (attackRoll == 12)
	{
		std::cout << this->getName() << " has turned her target to stone.\n";
		return 9999;
	}
	else
	{
		std::cout << this->getName() << " attacks for: " << attackRoll << ".\n";
		return attackRoll;
	}
	
}
/*********************************************************************
** Function: attack
** Description: Rolls 1d6 to return attack roll for Medusa.
*********************************************************************/
int Medusa::defend(int attack)
{

	int defenseRoll = (rand() % 6) + 1;
	int strengthLost = attack - defenseRoll - armor;
	//If damage is done
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
	//If damage is not donne
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
bool Medusa::isAlive()
{
	return alive;
}
void Medusa::revitalize()
{
	int missingStr = startingStr - strength;
	strength += (1 / 2) * missingStr;
}
