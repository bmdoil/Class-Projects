/*******************************************************
**Program Filename: Bulbasaur.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: bulbasaur implementation
*********************************************************/

#include "Bulbasaur.hpp"
/*********************************************************************
** Function: Bulbasaur constructor
** Description: Takes name and starting level as arguments. Sets combat
** stats. Sets name and attacks. Levels up to given start level
*********************************************************************/
Bulbasaur::Bulbasaur(std::string n, int startLev)
{
	this->name = n;
	this->alive = true;
	this->HP = 45;
	this->maxHP = 45;
	this->attack = 49;
	this->defense = 49;
	this->speed = 45;
	this->att1 = new Attack("Razor Leaf", 35, 100);
	this->att2 = new Attack("Vine Whip", 60, 75);
	this->att3 = new Attack("Tackle", 40, 90);
	//Level up to start level
	for (int i = 1; i < startLev; i++)
	{
		this->levelUp();
	}
}
/*********************************************************************
** Function: Bulbasaur destructor
** Description: deletes memory for attacks
*********************************************************************/
Bulbasaur::~Bulbasaur()
{
	delete att1;
	delete att2;
	delete att3;
	att1 = NULL;
	att2 = NULL;
	att3 = NULL;
}
/*********************************************************************
** Function: attackPokemon
** Description: takes defending Pokemon as argument and runs battle logic
*********************************************************************/
void Bulbasaur::attackPokemon(Pokemon* defender)
{
	Attack* currentAtt = NULL;
	//Choose your attack
	std::cout << this->getName() << " is attacking!\n";
	std::cout << "Which attack will you use?\n" << "[1]:" << this->att1->getName() << "\n" << "[2]:" << this->att2->getName() << "\n" << "[3]:" << this->att3->getName() << "\n";
	int choice = validNum("Pick [1] [2] [3]:\n", "Pick [1] [2] [3]:", 1, 3);
	switch (choice)
	{
	case 1: currentAtt = att1;
		break;
	case 2: currentAtt = att2;
		break;
	case 3: currentAtt = att3;
		break;
	default: break;
	}
	std::cout << this->getName() << " attacks " << defender->getName() << " with " << currentAtt->getName() << "!\n";
	int accuracy = rand() % 101;
	double damage;
	//Calculates if attack will connect based on accuracy
	if (currentAtt->getAccuracy() < accuracy)
	{
		std::cout << currentAtt->getName() << " misses!\n";
		return;
	}
	else
	{	
		//Damage calculation function
		damage = (((2 * this->level + 10) / 20) * (this->getAttack() / defender->getDefense()) * currentAtt->getPower() + 2) * floatRand(.85, 1.0);
		std::cout << this->getName() << "'s " << currentAtt->getName() << " does " << (int)damage << " damage!\n";
		defender->loseHP(damage);
		//Display results
		if (defender->getHP() < 1)
		{
			std::cout << defender->getName() << " is knocked out!\n";
			defender->setAlive(false);
			defender->setHP(0);
			std::cout << this->getName() << " levels up!\n";
			this->levelUp();
		}
		else
		{
			std::cout << defender->getName() << " has " << (int)defender->getHP() << " remaining.\n";
		}


	}


}
/*********************************************************************
** Function: attackAI
** Description: takes defending Pokemon as argument and runs battle logic
** Used if user input is not required, i.e. for AI pokemon
*********************************************************************/
void Bulbasaur::attackAI(Pokemon* defender)
{
	Attack* currentAtt = NULL;
	std::cout << this->getName() << " is attacking!\n";
	int choice = (rand() % 3) + 1;
	switch (choice)
	{
	case 1: currentAtt = att1;
		break;
	case 2: currentAtt = att2;
		break;
	case 3: currentAtt = att3;
		break;
	default: break;
	}
	std::cout << this->getName() << " attacks " << defender->getName() << " with " << currentAtt->getName() << "!\n";
	int accuracy = rand() % 100;
	double damage;
	if (currentAtt->getAccuracy() < accuracy)
	{
		std::cout << currentAtt->getName() << " misses!\n";
		return;
	}
	else
	{
		damage = (((2 * this->level + 10) / 20) * (this->getAttack() / defender->getDefense()) * currentAtt->getPower() + 2) * floatRand(.85, 1.0);
		std::cout << this->getName() << "'s " << currentAtt->getName() << " does " << (int)damage << " damage!\n";
		defender->loseHP(damage);
		if (defender->getHP() < 1)
		{
			std::cout << defender->getName() << " is knocked out!\n";
			defender->setAlive(false);
			defender->setHP(0);
			std::cout << this->getName() << " levels up!\n";
			this->levelUp();
		}
		else
		{
			std::cout << defender->getName() << " has " << (int)defender->getHP() << " remaining.\n";
		}


	}

}