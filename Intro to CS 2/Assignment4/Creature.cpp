/*******************************************************
**Program Filename: Creature.cpp
**Author: Brent Doil
**Date: 4/28/2016
**Description: Creature implementation
*********************************************************/


#include "Creature.hpp"
/*********************************************************************
** Function: Creature constructor
** Description: Default creature constructor, never explicitly called
*********************************************************************/
Creature::Creature()
{		

}
/*********************************************************************
** Function: setName
** Description: Sets name for creature
*********************************************************************/
void Creature::setName(std::string n)
{
	this->name = n;
}
/*********************************************************************
** Function: getStrength
** Description: Returns strength of creature
*********************************************************************/
int Creature::getStrength()
{
	return this->strength;
}
/*********************************************************************
** Function: getRoundWin
** Description: Returns number of rounds creature has won
*********************************************************************/
int Creature::getRoundWin()
{
	return this->roundWin;
}
/*********************************************************************
** Function: RoundWin
** Description: Increments round win
*********************************************************************/
void Creature::RoundWin()
{
	roundWin += 1;
}
/*********************************************************************
** Function: getName
** Description: Returns name of creature
*********************************************************************/
std::string Creature::getName()
{
	return this->name;
}
/*********************************************************************
** Function: getDamage
** Description: Returns damage done by creature
*********************************************************************/
int Creature::getDamage()
{
	return this->damage;

}
/*********************************************************************
** Function: setTeam
** Description: Sets team that creature is on
*********************************************************************/
void Creature::setTeam(std::string t)
{
	team = t;
}
/*********************************************************************
** Function: getTeam
** Description: Returns team that creature is on
*********************************************************************/
std::string Creature::getTeam()
{
	return this->team;
}