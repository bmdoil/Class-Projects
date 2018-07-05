/*******************************************************
**Program Filename: Roster.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: roster implementation
*********************************************************/

#include "Roster.hpp"

/*********************************************************************
** Function: Roster constructor
** Description: sets currentsize and maxSize. Sets all pokemon to NULL
*********************************************************************/
Roster::Roster()
{
	currentSize = 0;
	maxSize = 5;
	roster = new Pokemon*[maxSize];
	for (int i = 0; i < maxSize; i++)
	{
		roster[i] = NULL;
	}
}
/*********************************************************************
** Function: Roster constructor
** Description: takes argument for max size of roster, sets pokemon to NULL
*********************************************************************/
Roster::Roster(int max)
{
	currentSize = 0;
	maxSize = max;
	roster = new Pokemon*[maxSize];
	for (int i = 0; i < maxSize; i++)
	{
		roster[i] = NULL;
	}
}

/*********************************************************************
** Function: Roster destructor
** Description: Cleans up memory for Roster
*********************************************************************/
Roster::~Roster()
{
	while (!empty())
	{
		remove();
	}
	delete roster;
}
/*********************************************************************
** Function: add
** Description: Adds Pokemon to roster
*********************************************************************/
void Roster::add(Pokemon* c)
{
	if (currentSize == maxSize)
	{
		std::cout << "Roster is full!\n";
		return;
	}
	if (c == NULL)
	{
		return;
	}
	for (int i = 0; i < maxSize; i++)
	{
		if (roster[i] == NULL)
		{
			std::cout << "Added a " << c->getName() << "!\n";
			roster[i] = c;
			currentSize++;
			return;
		}
	}
}
/*********************************************************************
** Function: remove
** Description: removes Pokemon from roster
*********************************************************************/
void Roster::remove()
{
	if (empty())
	{
		std::cout << "No pokemon!\n";
		return;
	}
	else
	{
		for (int i = 0; i < maxSize; i++)
		{
			if (roster[i] != NULL)
			{
				
				currentSize--;
				delete roster[i];
				roster[i] = NULL;
				return;
			}
		}
		std::cout << "Pokemon not found.\n";
	}
}
/*********************************************************************
** Function: remove
** Description: Removes pokemon specified by name, given in argument
********************************************************************/
void Roster::remove(std::string n)
{
	

	if (empty())
	{
		std::cout << "No pokemon!\n";
		return;
	}
	else
	{
		for (int i = 0; i < maxSize; i++)
		{
			if (roster[i] != NULL && roster[i]->getName() == n)
			{
				std::cout << "Removed " << roster[i]->getName() << "\n";
				currentSize--;
				delete roster[i];
				roster[i] = NULL;
				return;
			}
		}
		std::cout << "Pokemon not found.\n";
	}
}
/*********************************************************************
** Function: usePoke
** Description: returns pokemon given by name, does not remove. 
*********************************************************************/
Pokemon* Roster::usePoke(std::string n)
{
	std::string pokeName;
	Pokemon* temp = NULL;
	for (int i = 0; i < maxSize; i++)
	{
		if (roster[i] != NULL && roster[i]->getName() == n)
		{
			if (!roster[i]->getAlive())
			{
				std::cout << "That Pokemon is knocked out! Choose another:\n";
				std::getline(std::cin, pokeName);
				return this->usePoke(pokeName);
			}
			temp = roster[i];
			return temp;
		}
	}
	std::cout << "It looks like you misspelled the name! Try again.\n";	
	std::getline(std::cin, pokeName);
	return this->usePoke(pokeName);
}

/*********************************************************************
** Function: empty
** Description: Checks if  empty
*********************************************************************/
bool Roster::empty() const
{
	if (currentSize > 0)
	{
		return false;
	}
	return true;
}
/*********************************************************************
** Function: displayRoster
** Description: prints roster to screen
*********************************************************************/
void Roster::displayRoster()
{
	if (empty())
	{
		std::cout << "Roster is empty.\n";
	}
	else
	{
		std::cout << "Your roster is\n";
		std::cout << "---------------\n";
		for (int i = 0; i < maxSize; i++)
		{
			if (roster[i] != NULL)
			{
				roster[i]->printStats();
				std::cout << "---------------\n";
			}
		}
	}
}
/*********************************************************************
** Function: checkAlive
** Description: checks to see if any pokemon are alive
*********************************************************************/
bool Roster::checkAlive()
{
	for (int i = 0; i < maxSize; i++)
	{
		if (roster[i] != NULL)
		{
			if (roster[i]->getAlive())
			{
				return true;
			}
		}
	}
	return false;
}
/*********************************************************************
** Function: useRareCandy
** Description: uses a Rare Candy on all pokemon in roster
*********************************************************************/
void Roster::useRareCandy()
{
	for (int i = 0; i < maxSize; i++)
	{
		if (roster[i] != NULL)
		{
			roster[i]->levelUp();
		}
	}
	std::cout << "All Pokemon leveled up!\n";
}
/*********************************************************************
** Function: useHealPot
** Description: uses a Healing Potion on all pokemon in roster
*********************************************************************/
void Roster::useHealPot()
{
	for (int i = 0; i < maxSize; i++)
	{
		if (roster[i] != NULL)
		{
			roster[i]->setHPMax();
			roster[i]->setAlive(true);
		}
	}
	std::cout << "All Pokemon recovered to their Max HP!\n";
}