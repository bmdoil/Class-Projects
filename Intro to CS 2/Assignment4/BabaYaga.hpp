/*******************************************************
**Program Filename: BabaYaga.cpp
**Author: Brent Doil
**Date: 4/28/2016
**Description: Baba Yaga creature interface
*********************************************************/

#ifndef BABAYAGA_HPP
#define BABAYAGA_HPP
#include "Creature.hpp"

class BabaYaga : public Creature
{
private:
	const int startingStr = 12;
public:
	BabaYaga();
	~BabaYaga() {};
	int attack();
	int defend(int);
	bool isAlive();
	void revitalize();
	
};
#endif // !BABAYAGA_HPP

