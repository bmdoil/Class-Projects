/*******************************************************
**Program Filename: Doodlebug.cpp
**Author: Brent Doil
**Date: 4/28/2016
**Description: Doodlebug class implementation
*********************************************************/

#include "Doodlebug.hpp"

Doodlebug::Doodlebug()
{
	count = 0;
	eat = 0;
	this->critter = 'D';
}
Doodlebug* Doodlebug::Breed()
{
	this->count++;
	if (this->count >= BREED)
	{
		Doodlebug* newDoodlebug = new Doodlebug;
		count = 0;
		return newDoodlebug;
	}
	else return NULL;
}
void Doodlebug::Eat()
{
	this->eat = 0;
}
bool Doodlebug::Starve()
{
	this->eat++;
	if (this->eat > STARVED)
	{
		return true;
	}
	else return false;
}
