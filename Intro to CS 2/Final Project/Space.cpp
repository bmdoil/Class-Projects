/*******************************************************
**Program Filename: Space.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: space implementation
*********************************************************/

#include "Space.hpp"

/*********************************************************************
** Function: getName
** Description: returns name
*********************************************************************/
std::string Space::getName()
{
	return this->name;
}
/*********************************************************************
** Function: setPlayer
** Description: adds player to space
*********************************************************************/
void Space::setPlayer(Player* p)
{
	if (this == NULL)
	{
		return;
	}
	this->currentPlayer = p;
	std::cout << this->currentPlayer->getName() << " moves to " << this->getName() << "\n";
}
/*********************************************************************
** Function: getPlayer
** Description: returns player
*********************************************************************/
Player* Space::getPlayer()
{
	return this->currentPlayer;
}
/*********************************************************************
** Function: getActive
** Description: returns active status of space
*********************************************************************/
bool Space::getActive()
{
	return this->active;
}