/*******************************************************
**Program Filename: Hills.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: hills implementation
*********************************************************/

#include "Hills.hpp"

/*********************************************************************
** Function: Hills constructor
** Description: sets name, new pokemon and items for Hills
*********************************************************************/
Hills::Hills()
{
	active = true;
	this->name = "Hills";
	currentPlayer = NULL;
	poke1 = new Pikachu("Electrode", 8);
	poke2 = new Charmander("Magmar", 10);
	poke3 = new Bulbasaur("Venomoth", 11);
	item1 = new Item(Bike);
	item2 = new Item(Pokeball);
}

/*********************************************************************
** Function: actionBattle
** Description: battle logic pokemon in Surf
*********************************************************************/
void Hills::actionBattle()
{
	//Set temp pointers
	Pokemon* spacePoke = NULL;
	Pokemon* playerPoke = NULL;
	std::string pokeName;
	// Check to see if there are any pokemon in the space, then which one is active. Looks in poke1, then poke2


	if (poke1 == NULL && poke2 == NULL && poke3 == NULL)
	{
		std::cout << "No pokemon in this space!\n";
		this->active = false;
		return;
	}
	else if (poke1 != NULL)
	{
		spacePoke = poke1;
		std::cout << "A wild " << spacePoke->getName() << " appears!\n";
	}
	else if (poke2 != NULL)
	{
		spacePoke = poke2;
		std::cout << "A wild " << spacePoke->getName() << " appears!\n";
	}
	else if (poke3 != NULL)
	{
		spacePoke = poke3;
		std::cout << "A wild " << spacePoke->getName() << " appears!\n";
	}

	//Check to see if any pokemon are alive
	if (!currentPlayer->getRoster()->checkAlive())
	{
		std::cout << "All pokemon knocked out! Game over\n";
		currentPlayer->setActive(false);
		return;
	}

	//Display roster and prompt user to choose a pokemon
	currentPlayer->getRoster()->displayRoster();
	std::cout << "Enter the name of the Pokemon you want to battle with\n";
	std::getline(std::cin, pokeName);
	//Set playerPoke to the pokemon chosen. Will reprompt user if name isn't correct. 
	playerPoke = currentPlayer->getRoster()->usePoke(pokeName);

	//Logic for fighting the pokemon in the space
	//Highest speed goes first, then alternate attacks
	//AI pokemon choses an attack randomly
	while (spacePoke->getAlive() && playerPoke->getAlive())
	{
		if (spacePoke->getSpeed() >= playerPoke->getSpeed())
		{
			if (spacePoke->getAlive())
			{
				spacePoke->attackAI(playerPoke);
				playerPoke->printStats();
			}

			if (playerPoke->getAlive())
			{
				playerPoke->attackPokemon(spacePoke);
				spacePoke->printStats();
			}
		}
		else
		{
			if (playerPoke->getAlive())
			{
				playerPoke->attackPokemon(spacePoke);
				spacePoke->printStats();
			}

			if (spacePoke->getAlive())
			{
				spacePoke->attackAI(playerPoke);
				playerPoke->printStats();
			}

		}
	}

	//If playerPoke is still alive after fight, attempt to capture spacePoke with a pokeball
	if (playerPoke->getAlive())
	{
		//Success!
		if (currentPlayer->useItem(Pokeball))
		{
			currentPlayer->getRoster()->add(spacePoke);
			std::cout << "You captured a " << spacePoke->getName() << " !\n";
			//Ownership transfered to Player roster, set appropriate poke pointer to NULL
			if (spacePoke == poke1)
			{

				poke1 = NULL;
			}
			else if (spacePoke == poke2)
			{

				poke2 = NULL;
			}
			else if (spacePoke == poke3)
			{

				poke3 = NULL;
			}
		}
		//No pokeballs
		else
		{
			std::cout << "You don't have any Pokeballs to capture the Pokemon with.\n";
			//Remove the appropriate KO'd pokemon
			if (spacePoke == poke1)
			{
				delete poke1;
				poke1 = NULL;
			}
			else if (spacePoke == poke2)
			{
				delete poke2;
				poke2 = NULL;
			}
			else if (spacePoke == poke3)
			{
				delete poke3;
				poke3 = NULL;
			}
		}

	}

}
/*********************************************************************
** Function: actionItem
** Description: item action for Hills
*********************************************************************/
Item* Hills::actionItem()
{
	Item* temp = NULL;
	std::cout << "There's an abandoned house at the top of the hill. Time to explore.\n";
	if (item1 != NULL && item2 != NULL)
	{
		std::cout << "You find an old Bike!\nYou can use this to skip to the Hospital and Store!\nYou can use it after finishing up here.\n";
		temp = item1;
		item1 = NULL;
		return temp;
	}
	else if (item1 == NULL && item2 == NULL)
	{
		std::cout << "Nothing useful inside.\n";
		return NULL;
	}
	else
	{
		std::cout << "You found a Pokeball!\n";
		temp = item2;
		item2 = NULL;
		return temp;
	}
}
/*********************************************************************
** Function: actionSpecial
** Description: special action for Hills. Based on RNG
*********************************************************************/
void Hills::actionSpecial()
{
	int num = (rand() % 10) + 1;
	 
	int choice = validNum("An old wanderer stops you and offers to lead you to the next area. Follow him?\n[1]Yes\n[2]No", "Choose either 1 or 2", 1, 2);
	if (choice == 1)
	{
		if (num <= 4)
		{
			std::cout << "It's a trap! He tries to steal a Pokeball\n";			
			this->getPlayer()->getBackPack()->removeItem(Pokeball);
			
		}
		else 
		{
			std::string pokeName;
			std::cout << "He offers sage advice on your journey, and you become a better trainer.\n Your Pokemon level up!";
			this->getPlayer()->getRoster()->useRareCandy();
		}
		
	}
	else
	{
		std::cout << "Probably a good choice ;)\n";
	}
}