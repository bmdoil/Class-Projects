/*******************************************************
**Program Filename: Hospital.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: hospital implementation
*********************************************************/

#include "Hospital.hpp"

/*********************************************************************
** Function: Hospital constructor
** Description: sets name, new pokemon and items are set to null
*********************************************************************/
Hospital::Hospital()
{
	poke1 = NULL;
	poke2 = NULL;
	item1 = NULL;
	item2 = NULL;
	this->name = "Hospital";
	active = true;
}
/*********************************************************************
** Function: actionSpecial
** Description: Hospital special action. Offers to heal and lvlUp
** All pokemon for 40g
*********************************************************************/
void Hospital::actionSpecial()
{
	//Offer to heal all pokemon and level them up for 50g
	int choice = validNum("You are at the Hospital! Heal all Pokemon and level up for 40g?\n[1]Yes\n[2]No", "Please enter either 1 or 2", 1, 2);
	if (choice == 1)
	{
		if (this->getPlayer()->getBackPack()->getGold() >= 40)
		{
			this->getPlayer()->getBackPack()->changeGold(-40);
			this->getPlayer()->getBackPack()->displayBackpack();
			this->getPlayer()->getRoster()->useHealPot();
			this->getPlayer()->getRoster()->useRareCandy();
			std::cout << "All your Pokemon are healthy!\n";
			this->getPlayer()->getRoster()->displayRoster();
		}
		else
		{
			std::cout << "You don't have enough gold!\n";
		}
	}
	else if (choice == 2)
	{
		std::cout << "Goodbye.\n";
	}
}