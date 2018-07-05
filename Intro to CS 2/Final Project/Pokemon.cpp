/*******************************************************
**Program Filename: Pokemon.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: Pokemon implementation
*********************************************************/


#include "Pokemon.hpp"
/*********************************************************************
** Function: Pokemon constructor
** Description: never called, but sets all pokemon initial level to 1
*********************************************************************/
Pokemon::Pokemon()
{
	level = 1;
}
/*********************************************************************
** Function: getLevel
** Description: returns level
*********************************************************************/
int Pokemon::getLevel() const
{
	return this->level;
}
/*********************************************************************
** Function: loseHP
** Description: subtracts argument from HP
*********************************************************************/
void Pokemon::loseHP(double h)
{
	this->HP -= h;
}
/*********************************************************************
** Function: getHP
** Description: returns HP
*********************************************************************/
double Pokemon::getHP() const
{
	return this->HP;
}
/*********************************************************************
** Function: getSpeed
** Description: returns speed
*********************************************************************/
double Pokemon::getSpeed() const
{
	return this->speed;
}
/*********************************************************************
** Function: getDefense
** Description: returns defense
*********************************************************************/
double Pokemon::getDefense() const
{
	return this->defense;
}
/*********************************************************************
** Function: getAttack
** Description: returns attack
*********************************************************************/
double Pokemon::getAttack() const
{
	return this->attack;
}
/*********************************************************************
** Function: levelUP
** Description: levels up pokemon using declared const lvlMod as modifier
*********************************************************************/
void Pokemon::levelUp()
{
	if (level < MAXLVL)
	{
		level++;
		this->HP *= lvlMod;
		this->maxHP *= lvlMod;
		this->attack *= lvlMod;
		this->defense *= lvlMod;		
	}
	else
	{
		std::cout << this->name << " is already max level!\n";
	}

}
/*********************************************************************
** Function: setName
** Description: Sets name for Pokemon
*********************************************************************/
void Pokemon::setName(std::string n)
{
	this->name = n;
}

/*********************************************************************
** Function: getName
** Description: Returns name of Pokemon
*********************************************************************/
std::string Pokemon::getName()
{
	return this->name;
}

/*********************************************************************
** Function: printStats
** Description: prints stats of Pokemon
*********************************************************************/
void Pokemon::printStats()
{
	std::cout << "Name: " << this->getName() << "\n";
	std::cout << "Level: " << (int)this->getLevel() << "\n";
	std::cout << "HP: " << (int)this->getHP() << "\n";
	std::cout << "Attack: " << (int)this->getAttack() << "\n";
	std::cout << "Defense: " << (int)this->getDefense() << "\n";
	std::cout << "Speed: " << (int)this->getSpeed() << "\n";
}
/*********************************************************************
** Function: getAlive
** Description: returns whether pokemon is alive, bool
*********************************************************************/
bool Pokemon::getAlive()
{
	return this->alive;
}
/*********************************************************************
** Function: setAlive
** Description: sets alive bool to argument
*********************************************************************/
void Pokemon::setAlive(bool b)
{
	this->alive = b;
}
/*********************************************************************
** Function: setHP
** Description: sets HP to given argument
*********************************************************************/
void Pokemon::setHP(double hp)
{
	this->HP = hp;
}
/*********************************************************************
** Function: setHPMax
** Description: restores HP to maxHP 
*********************************************************************/
void Pokemon::setHPMax()
{
	this->HP = maxHP;
}