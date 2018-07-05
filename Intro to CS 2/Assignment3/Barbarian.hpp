/*******************************************************
**Program Filename: Barbarian.cpp
**Author: Brent Doil
**Date: 4/28/2016
**Description: Barbarian class interface
*********************************************************/

#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP
#include "Creature.hpp"

class Barbarian : public Creature
{
public:
	Barbarian();
	~Barbarian() {};
	int attack();
	int defend(int);
	bool isAlive();
	void setName(std::string);
};





#endif // !BARBARIAN_HPP
