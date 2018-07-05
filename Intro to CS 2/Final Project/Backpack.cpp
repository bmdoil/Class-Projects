/*******************************************************
**Program Filename: Backpack.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: backpack implementation
*********************************************************/

#ifndef BACKPACK_CPP
#define BACKPACK_CPP

#include "Backpack.hpp"

/*********************************************************************
** Function: Backpack constructor
** Description: new backpack, takes int as max size arg
*********************************************************************/
Backpack::Backpack(int max)
{
	currentsize = 0;
	gold = 100;
	maxSize = max;
	pack = new Item*[maxSize];
	for (int i = 0; i < maxSize; i++)
	{
		pack[i] = NULL;
	}
}
/*********************************************************************
** Function: Backpack destructor
** Description: frees memory for backpack
*********************************************************************/
Backpack::~Backpack()
{
	for (int i = 0; i < maxSize; i++)
	{
		if (pack[i] != NULL)
			delete pack[i];
	}
	delete[] pack;
	pack = NULL;
}
/*********************************************************************
** Function: addItem
** Description: Takes item arg and adds to backpack. If no other of same
** item, puts in new slot. Otherwise adds to quantity of item already there
*********************************************************************/
void Backpack::addItem(Item* it)
{
	if (currentsize == maxSize)
	{
		std::cout << "Backpack full!\n";
		return;
	}
	if (it == NULL)
	{
		return;
	}
	for (int i = 0; i < maxSize; i++)
	{
		if ((pack[i] != NULL) && (pack[i]->type() == it->type()))
		{
			std::cout << "Picked up a " << it->getName() << "!\n";
			pack[i]->add();
			return;
		}		
	}
	for (int i = 0; i < maxSize; i++)
	{
		if (pack[i] == NULL)
		{
			std::cout << "Picked up a " << it->getName() << "!\n";
			pack[i] = it;
			currentsize++;
			return;
		}
	}
}
/*********************************************************************
** Function: addItem
** Description: Takes addition arg, gold, and subtracts that gold front
** player. Used in the store.
*********************************************************************/
void Backpack::addItem(Item* it, int g)
{
	if (this->gold > g)
	{
		for (int i = 0; i < maxSize; i++)
		{
			if (pack[i] != NULL && (pack[i]->type() == it->type()))
			{
				std::cout << "Bought a " << it->getName() << " for " << g << " gold.\n";
				pack[i]->add();
				gold -= g;
				return;
			}
			else if (pack[i] == NULL)
			{
				std::cout << "Bought a " << it->getName() << " for " << g << " gold.\n";
				pack[i] = it;
				currentsize++;
				gold -= g;
				return;
			}
		}
	}
	else
	{
		std::cout << "Not enough gold!\n";
		return;
	}
}
/*********************************************************************
** Function: removeItem
** Description: removes item of arg ItemType
*********************************************************************/
bool Backpack::removeItem(ItemType itemType)
{
	for (int i = 0; i < maxSize; i++)
	{
		if ((pack[i] != NULL) && pack[i]->type() == itemType)
		{
			
			std::cout << "Used a " << pack[i]->getName() << ".\n";
			pack[i]->use();
			if (pack[i]->getQuantity() == 0)
			{
				currentsize--;
				delete pack[i];
				pack[i] = NULL;
				return true;
			}
			return true;
		}
	}
	//std::cout << "Item not found\n";
	return false;
}
/*********************************************************************
** Function: getItemQuant
** Description: returns # of items in backpack of arg ItemType
*********************************************************************/
int Backpack::getItemQuant(ItemType itemType)
{
	for (int i = 0; i < maxSize; i++)
	{
		if ((pack[i] != NULL) && (pack[i]->type() == itemType))
		{

			return pack[i]->getQuantity();			
		}
	}
	//std::cout << "Item not found\n";
	return 0;
}
/*********************************************************************
** Function: displayBackpack
** Description: prints contents of backpack to screen
*********************************************************************/
void Backpack::displayBackpack()
{
	std::cout << "\nBackpack Contains:\n";
	for (int i = 0; i < maxSize; i++)
	{
		if (pack[i] != NULL)
		{			
			pack[i]->print();
		}
	}
	std::cout << "Gold: " << gold << "\n";
	std::cout << "-----------------------------------\n\n";
}
/*********************************************************************
** Function: changeGold
** Description: Changes amt of gold in backpack, - to remove + to add
*********************************************************************/
void Backpack::changeGold(int g)
{
	gold += g;
}
/*********************************************************************
** Function: getGold
** Description: returns gold in backpack
*********************************************************************/
int Backpack::getGold()
{
	return this->gold;
}
#endif // !BACKPACK_CPP
