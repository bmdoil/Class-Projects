/*******************************************************
**Program Filename: Creature.hpp
**Author: Brent Doil
**Date: 5/22/2016
**Description: Creature interface
*********************************************************/

#ifndef CREATURE_HPP
#define CREATURE_HPP
#include <ctime>
#include <cstdlib>
#include <cstddef>
#include <iostream>
#include <string>


class Creature
{
protected:
	int armor;
	int strength;
	bool alive;
	std::string name;
	int roundWin = 0;
	int damage = 0;
	std::string team;
	
public:
	Creature();
	virtual ~Creature() {};
	virtual int attack() = 0;
	virtual int defend(int) = 0;
	virtual bool isAlive() = 0;	
	virtual void revitalize() = 0;

	void setName(std::string);	
	std::string getName();

	void setTeam(std::string team);
	int getStrength();
	int getRoundWin();
	int getDamage();
	void RoundWin();
	
	
	std::string getTeam();

};

#endif // !CREATURE_HPP

