/*****************************************************
**Program Filename : Medusa.cpp
**Author : Brent Doil
**Date : 4 / 28 / 2016
**Description : Medusa class interface
*********************************************************/

#ifndef MEDUSA_HPP
#define MEDUSA_HPP
#include "Creature.hpp"

class Medusa : public Creature
{
public:
	Medusa();
	~Medusa() {};
	int attack();
	int defend(int);
	bool isAlive();
	void setName(std::string);

};
#endif // !MEDUSA_HPP

