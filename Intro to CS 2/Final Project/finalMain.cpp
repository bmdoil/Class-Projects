/*******************************************************
**Program Filename: pokeFinal.cpp
**Author: Brent Doil
**Date: 6/5/2016
**Description: CS162 Final main method
*********************************************************/
#include "Map.hpp"
#include "Player.hpp"

//Helper functions
void checkItem(Map* m, Player* p);
void wilderness(Map* m, Player* p);
void battleTrainer(Map* m, Player* p, int t);
void useItem(Map* m, Player* p);

int main()
{
	while (menu())
	{
		//Instantiate map 
		Map* myMap = new Map("Kanto");

		std::cout << "Welcome to C++ Pokemon! Choose your Player and Pokemon names!\nConsider using something easy for testing :)\n";
		//Instantiate Player and initial Pokemon
		std::string playerName;
		std::string pokeName;
		std::cout << "Pick a name for your player.\n";
		std::getline(std::cin, playerName);
		Player* player = new Player(playerName, 5);
		std::cout << "You start with 2 Pokemon.\n";
		std::cout << "Pick a name for your Pikachu.\n";
		std::getline(std::cin, pokeName);
		Pokemon* poke1 = new Pikachu(pokeName, 12);
		std::cout << "Pick a name for your Charmander.\n";
		std::getline(std::cin, pokeName);
		Pokemon* poke2 = new Charmander(pokeName, 12);

		player->getRoster()->add(poke1);
		player->getRoster()->add(poke2);

	
		player->getRoster()->displayRoster();
		int count = 0;
		while ((player->getActive() || !player->getWin()) && count < 6)
		{

			wilderness(myMap, player);
			battleTrainer(myMap, player, count);
			myMap->addRandom(2);
			if (count == 0 || count == 2)
			{
				myMap->addHospStore();
			}					
			count++;
		}		
		std::cout << "Your final stats:\n";
		player->getName();
		player->getRoster()->displayRoster();
		player->getBackPack()->displayBackpack();
		if (player->getActive())
		{
			std::cout << "\nCongratualations, you've won!!!Go ahead and play again!\n";

		}
		else
		{
			std::cout << "\nYou were defeated! Try again?\n";
		}
		//Cleanup
		delete myMap;
		delete player;
		delete poke1;
		delete poke2;
		myMap = NULL;
		player = NULL;
		poke1 = NULL;
		poke2 = NULL;
	}	
	return 0;
	
}
void wilderness(Map* m, Player* p)
{
	
	while ((!m->empty()) && p->getActive() && m->peek()->getActive())
	{
		validNum("Press 1 to move to the next space.\n", "Press 1 to move to the next space.\n", 1, 1);
		m->peek()->setPlayer(p);
		if (m->peek()->getName() == "Hospital" || m->peek()->getName() == "Store")
		{
			m->peek()->actionSpecial();
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				if (p->getWin())
				{
					return;
				}
				else
				{
					int randChoice = (rand() % 3) + 1;
					switch (randChoice)
					{
					case 1:
					{
						checkItem(m, p);
						m->peek()->actionSpecial();
						break;
					}

					case 2:
					{
						checkItem(m, p);
						p->getBackPack()->addItem(m->peek()->actionItem());
						break;
					}

					case 3:
					{
						if (!m->peek()->getActive())
							break;
						m->peek()->actionBattle();

						if (!p->getRoster()->checkAlive())
						{
							p->setActive(false);
							break;
						}
						checkItem(m, p);
						useItem(m, p);
						break;
					}
					}
					if (!p->getActive())
					{
						return;
					}
				}
				}
				
		}		
		m->remove();
	}
	
}

	
void checkItem(Map* m, Player* p)
{
	if (p->getBackPack()->removeItem(Bike))
	{
		
		//Make sure it's out there somewhere
		m->addHospStore();
		m->remove();
		//Find Hosp
		while (m->peek()->getName() != "Hospital")
		{
			m->remove();		

		}
		//Complete action for Hospital
		m->peek()->setPlayer(p);
		m->peek()->actionSpecial();
		m->remove();
		// and Store
		m->peek()->setPlayer(p);
		m->peek()->actionSpecial();
		m->remove();
		m->peek()->setPlayer(p);
	}
	

	
	else if (p->getBackPack()->removeItem(BadMojo))
	{

		m->addRandom(1);		
	}
	else if (p->getBackPack()->getItemQuant(Badge) == 4)
	{
		std::cout << "You collected all 4 Badges!\nTime to battle Red!";
		p->getRoster()->useHealPot();
		p->getRoster()->useRareCandy();
		battleTrainer(m, p, 4);
	}
	else if (p->getBackPack()->getItemQuant(Key) >= 1)
	{
		p->getRoster()->useHealPot();
		p->getRoster()->useRareCandy();
		battleTrainer(m, p, 4);
	}
}
void battleTrainer(Map* m, Player* p, int t)
{
	if (p->getWin())
	{
		return;
	}
	if (!p->getActive())
	{
		return;
	}
	m->addTrainer(t);
	m->peek()->setPlayer(p);
	while (p->getActive() && m->peek()->getActive())
	{
		m->peek()->actionBattle();
	}
	m->remove();
	m->peek()->setPlayer(p);
}
void useItem(Map* m, Player* p)
{
	std::cout << "Now is a good time to check your backpack...\n";
	p->getBackPack()->displayBackpack();
	if ((p->getBackPack()->getItemQuant(RareCandy) > 0) && (p->getBackPack()->getItemQuant(HealingPotion) > 0))
	{
		int choice = validNum("[1]Use Rare Candy\n[2]Use Healing Potion\n[3]Exit\n", "Enter 1 - 3", 1, 3);
		if (choice == 1)
		{
			p->useItem(RareCandy);
		}
		else if (choice == 2)
		{
			p->useItem(HealingPotion);
		}
		else return;
	}
	else if (p->getBackPack()->getItemQuant(RareCandy) > 0)
	{
		int choice = validNum("[1]Use Rare Candy\n[2]Exit\n", "Enter 1 - 2", 1, 2);
		if (choice == 1)
		{
			p->useItem(RareCandy);
		}
		else return;
	}
	else if (p->getBackPack()->getItemQuant(HealingPotion) > 0)
	{
		int choice = validNum("[1]Use Healing Potion\n[2]Exit\n", "Enter 1 - 2", 1, 2);
		if (choice == 1)
		{
			p->useItem(HealingPotion);
		}
		else return;
	}
}
