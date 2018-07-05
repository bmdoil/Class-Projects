/*******************************************************
**Program Filename: Store.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: store implementation
*********************************************************/
#include "Store.hpp"

/*********************************************************************
** Function: store constructor
** Description: sets name, pokemon and items set to null
*********************************************************************/
Store::Store()
{
	poke1 = NULL;
	poke2 = NULL;
	item1 = NULL;
	item2 = NULL;
	this->name = "Store";
	active = true;
}
/*********************************************************************
** Function: actionSpecial
** Description: gives special action for store, allows player to buy
** an item, given they gave the gold
*********************************************************************/
void Store::actionSpecial()
{
	
	int choice = validNum("You are at the Store! Would you like to purchase anything?\n[1]Yes\n[2]No\n", "Please enter either 1 or 2", 1, 2);
	if (choice == 1)
	{
		this->getPlayer()->getBackPack()->displayBackpack();
		int buy = validNum("[1]Rare Candy 20g\n[2]Healing Pot 20g\n[3]Pokeball 10g\n[4]Exit\n", "Please enter 1 - 4", 1, 4);
		switch (buy)
		{
		case 1:
		{
			if (this->getPlayer()->getBackPack()->getGold() >= 20)
			{
				this->getPlayer()->getBackPack()->changeGold(-20);
				Item* temp = new Item(RareCandy);
				this->getPlayer()->getBackPack()->addItem(temp);
				this->getPlayer()->getBackPack()->displayBackpack();
				break;
			}
			else
			{
				std::cout << "You don't have enough gold!\n";
				break;
			}

		}
		case 2:
		{
			if (this->getPlayer()->getBackPack()->getGold() >= 20)
			{
				this->getPlayer()->getBackPack()->changeGold(-20);
				Item* temp = new Item(HealingPotion);
				this->getPlayer()->getBackPack()->addItem(temp);
				this->getPlayer()->getBackPack()->displayBackpack();
				break;
			}
			else
			{
				std::cout << "You don't have enough gold!\n";
				break;
			}
		}
		case 3:
		{
			if (this->getPlayer()->getBackPack()->getGold() >= 10)
			{
				this->getPlayer()->getBackPack()->changeGold(-10);
				Item* temp = new Item(Pokeball);
				this->getPlayer()->getBackPack()->addItem(temp);
				this->getPlayer()->getBackPack()->displayBackpack();
				break;
			}
			else
			{
				std::cout << "You don't have enough gold!\n";
				break;
			}
		}
		case 4:
		{
			std::cout << "Goodbye.\n";
			break;
		}

		}
	}
	else
	{
		std::cout << "Goodbye.\n";
	}
}