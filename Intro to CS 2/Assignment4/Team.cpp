/*******************************************************
**Program Filename: Team.cpp
**Author: Brent Doil
**Date: 5/22/2016
**Description: Team implementation
*********************************************************/
#include "Team.hpp"
/*********************************************************************
** Function: Team constructor
** Description: Instantiates team and sets name
*********************************************************************/
Team::Team(std::string team)
{
	teamName = team;
}
/*********************************************************************
** Function: Team destructor
** Description: Cleans up memory for Team
*********************************************************************/
Team::~Team()
{
	while (!empty())
	{
		CreatureNode* old = front;		
		delete old->thisCreature;
		old->thisCreature = NULL;
		delete old;
		old = NULL;
		front = front->next;			
	}
	delete creat;
}
/*********************************************************************
** Function: newCreat
** Description: adds new creature to Team. Takes creature type 1-5,
** name and team name as arguments
*********************************************************************/
void Team::newCreat(int creatType, std::string creatName, std::string teamName)
{
	
	switch (creatType)
	{
	case 1:
	{
		creat = new Barbarian;
		creat->setName(creatName);
		creat->setTeam(teamName);
		break;
	}
	case 2:
	{
		creat = new BabaYaga;
		creat->setName(creatName);
		creat->setTeam(teamName);
		break;
	}
	case 3: 
	{
		creat = new BlueMen;
		creat->setName(creatName);
		creat->setTeam(teamName);
		break;
	}
	case 4:
	{
		creat = new Harry;
		creat->setName(creatName);
		creat->setTeam(teamName);
		break;
	}
	case 5:
	{
		creat = new Medusa;
		creat->setName(creatName);
		creat->setTeam(teamName);
		break;
	}
	}
	if (empty())
	{
		front = new CreatureNode(creat);
		back = front;
		
	}
	else
	{
		back->next = new CreatureNode(creat);
		back = back->next;
		
	}
	creat = NULL;
}
/*********************************************************************
** Function: addExisting
** Description: adds an existing creature to Team.
*********************************************************************/
void Team::addExisting(Creature* creat)
{
	if (empty())
	{
		front = new CreatureNode(creat);
		back = front;
	}
	else
	{
		back->next = new CreatureNode(creat);
		back = back->next;
	}
}
/*********************************************************************
** Function: remove
** Description: Removes creature from Team and returns
*********************************************************************/
Creature* Team::remove()
{
	CreatureNode* old = NULL;
	Creature* temp = NULL;
	if (empty())
	{
		std::cout << "Queue is empty!\n";
		return '\0';
	}
	else
	{
		temp = front->thisCreature;
		old = front;
		front = front->next;
		delete old;
		return temp;
	}
}
bool Team::empty() const
{
	if (front == NULL)
	{
		return true;
	}
	else return false;
}
/*********************************************************************
** Function: getName
** Description: Returns name of team
*********************************************************************/
std::string Team::getName()
{
	return this->teamName;
}