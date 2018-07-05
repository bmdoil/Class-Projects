/*******************************************************
**Program Filename: Surf.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: Surf implementation
*********************************************************/
#include "Surf.hpp"

/*********************************************************************
** Function: Surf constructor
** Description: sets name, new pokemon and items for Surf
*********************************************************************/
Surf::Surf()
{
	active = true;
	this->name = "Surf";
	currentPlayer = NULL;
	poke1 = new Squirtle("Baby Squirtle", 7);
	poke2 = new Squirtle("Blastoise!", 11);
	poke3 = new Squirtle("Lampras", 10);
	item1 = new Item(RareCandy);
	item2 = new Item(HealingPotion);
}
/*********************************************************************
** Function: actionBattle
** Description: battle logic pokemon in Surf
*********************************************************************/
void Surf::actionBattle()
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
** Description: item action for Surf
*********************************************************************/
Item* Surf::actionItem()
{
	Item* temp = NULL;
	std::cout << "You find an item in the driftwood!\n";
	if (item1 != NULL && item2 != NULL)
	{
		std::cout << "You find a Rare Candy!\n";
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
		std::cout << "You find a Healing Potion!\n";
		temp = item2;
		item2 = NULL;
		return temp;
	}
}
/*********************************************************************
** Function: actionSpecial
** Description: special action for Surf, includes some RNGs
*********************************************************************/
void Surf::actionSpecial()
{
	int num = (rand() % 10) + 1;
	int choice = validNum("A strange woman appears in the waves and offers a gift. Accept?\n[1]Yes\n[2]No", "Choose either 1 or 2", 1, 2);
	if (choice == 1)
	{
		if (num < 3)
		{
			std::cout << "She hands you a pokeball!\n";
			Item* temp = new Item(Pokeball);
			this->getPlayer()->getBackPack()->addItem(temp);
			temp = NULL;
		}
		else if (num < 5)
		{
			std::string pokeName;
			std::cout << "She places a curse on one of your Pokemon, knocking them out!\n";
			currentPlayer->getRoster()->displayRoster();
			std::cout << "Enter the name of the Pokemon to be KO'd\n";
			std::getline(std::cin, pokeName);
			currentPlayer->getRoster()->usePoke(pokeName)->setHP(0);
			currentPlayer->getRoster()->usePoke(pokeName)->setAlive(false);
			if (!currentPlayer->getRoster()->checkAlive())
			{
				std::cout << "All pokemon knocked out! Game over\n";
				currentPlayer->setActive(false);
				return;
			}
			
		}
		else
		{
			std::cout << "She hands you some seashells, which you discard.\n";
		}
	}
	else
	{
		std::cout << "You get away safely.\n";
	}

}