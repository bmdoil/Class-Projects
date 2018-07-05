/*******************************************************
**Program Filename: Trainer.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: trainer implementation
*********************************************************/
#include "Trainer.hpp"

/*********************************************************************
** Function: Trainer constructor
** Description: sets name, pokemon, gold and item based on given arg
*********************************************************************/
Trainer::Trainer(int t)
{
	switch (t)
	{
	case 0:
	{
		poke1 = new Charmander("Charmeleon", 9);
		poke2 = new Bulbasaur("Venosaur", 11);
		this->name = "Agatha";
		trainerGold = 30;
		item1 = new Item(Badge);
		active = true;
		break;
	}
	case 1:
	{
		poke1 = new Charmander("Growlith", 10);
		poke2 = new Pikachu("Voltorb", 12);
		this->name = "Bruno";
		trainerGold = 40;
		item1 = new Item(Badge);
		active = true;
		break;
	}
	case 2:
	{
		poke1 = new Squirtle("Gyrados", 13);
		poke2 = new Bulbasaur("Venomoth", 11);
		this->name = "Lorelei";
		trainerGold = 40;
		item1 = new Item(Badge);
		active = true;
		break;
	}
	case 3:
	{
		poke1 = new Charmander("Charizard", 15);
		poke2 = new Pikachu("Jolteon", 17);
		this->name = "Lance";
		trainerGold = 50;
		item1 = new Item(Badge);
		active = true;
		break;
	}
	case 4:
	{
		poke1 = new Charmander("Moltres", 18);
		poke2 = new Squirtle("Articuno", 19);
		this->name = "Red";
		item1 = new Item(Key);
		active = true;
		break;
	}
	}
}
/*********************************************************************
** Function: Trainer destructor
** Description: cleans up memory for pokemon and item
*********************************************************************/
Trainer::~Trainer()
{
	delete poke1;
	delete poke2;
	delete item1;
	poke1 = NULL;
	poke2 = NULL;
	item1 = NULL;
}
/*********************************************************************
** Function: actionBattle
** Description: battle logic for trainer battle
*********************************************************************/
void Trainer::actionBattle()
{
	//Set temp pointers
	Pokemon* trainerPoke = NULL;
	Pokemon* playerPoke = NULL;
	std::string pokeName;
	// Check to see if there are any pokemon in the space, then which one is active. Looks in poke1, then poke2
	if ((!poke1->getAlive()) && (!poke2->getAlive()))
	{
		if (this->getName() == "Red")
		{
			std::cout << "You defeated Red! You win!\n";
			currentPlayer->setWin();
			active = false;
			return;
		}
		else
		{
			std::cout << this->getName() << " is defeated!\n";
			currentPlayer->getBackPack()->addItem(item1);
			std::cout << "You receive " << trainerGold << " gold.\n";
			currentPlayer->getBackPack()->changeGold(trainerGold);
			active = false;
			return;
		}
		
	}
	else if (poke1->getAlive())
	{
		std::cout << "You have been challenged by " << this->getName() << "\n";
		trainerPoke = poke1;
		std::cout << this->getName() << " uses " << trainerPoke->getName() << "!\n";
	}
	else if (poke2->getAlive())
	{
		std::cout << "You have been challenged by " << this->getName() << "\n";
		trainerPoke = poke2;
		std::cout << this->getName() << " uses " << trainerPoke->getName() << "!\n";
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
	while (trainerPoke->getAlive() && playerPoke->getAlive())
	{
		if (trainerPoke->getSpeed() >= playerPoke->getSpeed())
		{
			if (trainerPoke->getAlive())
			{
				trainerPoke->attackAI(playerPoke);
				playerPoke->printStats();
			}

			if (playerPoke->getAlive())
			{
				playerPoke->attackPokemon(trainerPoke);
				trainerPoke->printStats();
			}
		}
		else
		{
			if (playerPoke->getAlive())
			{
				playerPoke->attackPokemon(trainerPoke);
				trainerPoke->printStats();
			}

			if (trainerPoke->getAlive())
			{
				trainerPoke->attackAI(playerPoke);
				playerPoke->printStats();
			}

		}
	}
}
