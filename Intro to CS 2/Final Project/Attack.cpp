/*******************************************************
**Program Filename: Attack.cpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: attack implementation
*********************************************************/

#include "Attack.hpp"
/*********************************************************************
** Function: Attack constructor
** Description: Sets name, power, accuracy of attack
*********************************************************************/
Attack::Attack(std::string n, int pow, int acc)
{
	this->power = pow;
	this->accuracy = acc;
	this->name = n;
}
/*********************************************************************
** Function: getAccuracy
** Description: Returns accuracy
*********************************************************************/
int Attack::getAccuracy()
{
	return this->accuracy;
}
/*********************************************************************
** Function: gePower
** Description: Returns power
*********************************************************************/
int Attack::getPower()
{
	return this->power;
}
/*********************************************************************
** Function: getName
** Description: Returns name
*********************************************************************/
std::string Attack::getName()
{
	return this->name;
}
