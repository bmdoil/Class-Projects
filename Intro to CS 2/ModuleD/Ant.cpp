/*******************************************************
**Program Filename: Ant.cpp
**Author: Brent Doil
**Date: 4/15/2016
**Description: Ant class implementation
*********************************************************/

#include "Ant.hpp"

Ant::Ant()
{
	count = 0;
	this->critter = 'A';
}
Ant* Ant::Breed()
{
	this->count++;
	if (this->count >= BREED)
	{
		Ant* newAnt = new Ant;		
		count = 0;
		return newAnt;
	}
	else return NULL;
}
