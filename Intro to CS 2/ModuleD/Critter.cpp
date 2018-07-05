/*******************************************************
**Program Filename: Critter.cpp
**Author: Brent Doil
**Date: 4/26/2016
**Description: Critter class implementation
*********************************************************/

#include "Critter.hpp"
/*********************************************************************
** Function: Critter default constructor
** Description: Sets moveNum to 0 
*********************************************************************/
Critter::Critter()
{
	critter = 'C';
}
/*********************************************************************
** Function: Critter constructor
** Description: Sets moveNum to 0 and critter to passed argument
*********************************************************************/
Critter::Critter(char crit)
{
	critter = crit;

}
/*********************************************************************
** Function: getCritter
** Description: Returns char representing critter
*********************************************************************/
char Critter::getCritter()
{
	return critter;
}
/*********************************************************************
** Function: setMoved
** Description: sets moved to argument and returns
*********************************************************************/
bool Critter::setMoved(bool x)
{
	moved = x;
	return moved;
}
Critter* Critter::Breed()
{
	this->count++;
	if (this->count >= 3)
	{
		Critter* newCritter = new Critter;
		count = 0;
		return newCritter;
	}
	else return NULL;
}
void Critter::Eat()
{
	//Critter will have a virtual function Eat().If a Doodlebug moves into a grid with an Ant it will eat the
	//	ant.An Ant will not eat another Ant.A Doodlebug will not eat another Doodlebug.
	return;
}
bool Critter::Starve()
{
	return false;
}
