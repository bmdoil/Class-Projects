/*******************************************************
**Program Filename: Player.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: player implementation
*********************************************************/

#include "Player.hpp"

/*********************************************************************
** Function: Player constructor
** Description: sets name and size of backpack
*********************************************************************/
Player::Player(std::string n, int backpk)
{
	backpack = new Backpack(backpk);
	//currentSpace = spc;
	name = n;
	moveCount = 0;
	active = true;
	win = false;
	myRoster = new Roster;
}

/*********************************************************************
** Function: Player destructor
** Description: frees memory for backpack
*********************************************************************/
Player::~Player()
{
	delete backpack;
	backpack = NULL;
	
}
/*********************************************************************
** Function: getBackPack
** Description: returns backpack
*********************************************************************/
Backpack* Player::getBackPack()
{
	return this->backpack;
}
/*********************************************************************
** Function: getName
** Description: returns name
*********************************************************************/
std::string Player::getName()
{
	return this->name;
}
/*********************************************************************
** Function: setActive
** Description: sets whether player is active, to argument
*********************************************************************/
void Player::setActive(bool b)
{
	this->active = b;
}
/*********************************************************************
** Function: getActive
** Description: returns active
*********************************************************************/
bool Player::getActive()
{
	return this->active;
}
/*********************************************************************
** Function: getRoster
** Description: returns roster
*********************************************************************/
Roster* Player::getRoster()
{
	return this->myRoster;
}
/*********************************************************************
** Function: useItem
** Description: uses either a Rare Candy or Healing Potion
*********************************************************************/
bool Player::useItem(ItemType item)
{
	if (this->getBackPack()->removeItem(item))
	{
		switch (item)
		{
		case 0: this->getRoster()->useRareCandy();
			break;
		case 1: this->getRoster()->useHealPot();
			break;
		default:
			break;
		}
		return true;
	}
	
	return false;
}
/*********************************************************************
** Function: getWin
** Description: gets win, (deprecated)
*********************************************************************/
bool Player::getWin()
{
	return this->win;
}
/*********************************************************************
** Function: setWin
** Description: sets win, (deprecated)
*********************************************************************/
void Player::setWin()
{
	this->win = true;
}