/*******************************************************
**Program Filename: Map.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: map interface
*********************************************************/

#ifndef TEAM_HPP
#define TEAM_HPP


#include "Forest.hpp"
#include "Surf.hpp"
#include "Hospital.hpp"
#include "Cave.hpp"
#include "Hills.hpp"
#include "Store.hpp"
#include "Trainer.hpp"
#include <ctime>
class Map
{
private:

	struct SpaceNode
	{

		Space* thisSpace;
		
		SpaceNode* next;
		SpaceNode* prev;
		SpaceNode(Space* c, SpaceNode* n = NULL, SpaceNode* p = NULL)
		{
			thisSpace = c;
			next = n;
			prev = p;
		}
	};
	//Queue structure
	SpaceNode* front = NULL;
	SpaceNode* back = NULL;	
	SpaceNode* hospital = NULL;
	SpaceNode* trainer = NULL;

	std::string mapName;	
public:
	Map(std::string teamN);
	~Map() {};
	void addSpace(Space*);
	
	Space* remove();
	Space* peek();
	void addRandom(int);
	bool empty() const;
	std::string getName();
	void addHospStore();
	void addTrainer(int);
};



#endif // !TEAM_HPP

