/*****************************************************
**Program Filename : Harry.cpp
**Author : Brent Doil
**Date : 4 / 28 / 2016
**Description : Harry class interface
*********************************************************/

#ifndef HARRY_HPP
#define HARRY_HPP
#include "Creature.hpp"

class Harry : public Creature
{
private:
	bool hogwarts;
	const int startingStr = 10;
public:
	Harry();
	~Harry() {};
	int attack();
	int defend(int);
	bool isAlive();
	void revitalize();
	
};
#endif // !HARRY_HPP

