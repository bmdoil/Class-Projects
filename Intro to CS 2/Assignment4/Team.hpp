/*******************************************************
**Program Filename: Team.cpp
**Author: Brent Doil
**Date: 5/22/2016
**Description: Team interface
*********************************************************/

#ifndef TEAM_HPP
#define TEAM_HPP

#include "FightLogic.hpp"

class Team
{
private:

	struct CreatureNode
	{
		Creature* thisCreature;
		CreatureNode* next;
		CreatureNode(Creature* c, CreatureNode* n = NULL)
		{
			thisCreature = c;
			next = n;
		}
	};
	//Queue structure
	CreatureNode* front = NULL;
	CreatureNode* back = NULL;
	std::string teamName;
	Creature* creat = NULL;
	
public:
	Team(std::string teamN);
	~Team();
	void newCreat(int creatureType, std::string creatureName, std::string teamName);
	void addExisting(Creature* creat);
	Creature* remove();
	bool empty() const;
	std::string getName();
};



#endif // !TEAM_HPP

