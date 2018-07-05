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
private:
	const int startingStr = 12;
public:
	Medusa();
	~Medusa() {};
	int attack();
	int defend(int);
	bool isAlive();
	void revitalize();
	

};
#endif // !MEDUSA_HPP

