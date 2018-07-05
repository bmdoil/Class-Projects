/*******************************************************
**Program Filename: Cave.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: cave implementation
*********************************************************/

#include "Cave.hpp"


/*********************************************************************
** Function: Cave constructor
** Description: sets name, new pokemon and items for cave
*********************************************************************/
Cave::Cave()
{
	active = true;
	this->name = "Cave";
	currentPlayer = NULL;
	poke1 = new Pikachu("Electrode", 8);
	poke2 = new Charmander("Magmar", 11);
	poke3 = new Charmander("Ninetails", 13);
	item1 = new Item(BadMojo);
	item2 = new Item(RareCandy);
}
/*********************************************************************
** Function: actionBattle
** Description: battle logic pokemon in Surf
*********************************************************************/
void Cave::actionBattle()
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
** Description: item action for cave
*********************************************************************/
Item* Cave::actionItem()
{
	Item* temp = NULL;
	std::cout << "You find an item in a crevice!\n";
	if (item1 != NULL && item2 != NULL)
	{
		std::cout << "You find some Bad Mojo in the cave!\nYou get lost! Now there is more Wilderness ahead!\n";
		temp = item1;
		item1 = NULL;
		return temp;
	}
	else if (item1 == NULL && item2 == NULL)
	{
		std::cout << "Nothing inside!\n";
		return NULL;
	}
	else
	{
		std::cout << "You found a Rare Candy!\n";
		temp = item2;
		item2 = NULL;
		return temp;
	}
}
/*********************************************************************
** Function: actionSpecial
** Description: special action for cave. Based on RNG
*********************************************************************/
void Cave::actionSpecial()
{
	int num = (rand() % 10) + 1;
	int choice = validNum("Venture deeper into the Cave?\n[1]Yes\n[2]No", "Choose either 1 or 2", 1, 2);
	if (choice == 1)
	{
		if (num < 3)
		{
			std::cout << "You find a Key! This leads to Red, the final boss!\n";
			Item* temp = new Item(Key);
			this->getPlayer()->getBackPack()->addItem(temp);
			temp = NULL;
		}
		else if (num < 6)
		{
			std::string pokeName;
			std::cout << "You find some Bad Mojo in the cave!\nYou get lost! Now there is more Wilderness ahead!\n";
			Item* temp = new Item(BadMojo);
			this->getPlayer()->getBackPack()->addItem(temp);
		}
		else
		{
			std::cout << "You find a stash of 50 gold!\n";
			this->getPlayer()->getBackPack()->changeGold(50);
		}
	}

}

