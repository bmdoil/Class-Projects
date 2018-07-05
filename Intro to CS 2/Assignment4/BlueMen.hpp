/*****************************************************
**Program Filename : BlueMen.cpp
**Author : Brent Doil
**Date : 4 / 28 / 2016
**Description : Blue Men class interface
*********************************************************/

#ifndef BLUEMEN_HPP
#define BLUEMEN_HPP
#include "Creature.hpp"

class BlueMen : public Creature
{
private:
	const int startingStr = 12;
public:
	BlueMen();
	~BlueMen() {};
	int attack();
	int defend(int);
	bool isAlive();
	void revitalize();
	
};
#endif // !BLUEMEN_HPP

