/*******************************************************
**Program Filename: Map.cpp
**Author: Brent Doil
**Date: 5/22/2016
**Description: Map implementation
*********************************************************/
#include "Map.hpp"
/*********************************************************************
** Function: Map constructor
** Description: Instantiates Map and sets name
*********************************************************************/
Map::Map(std::string map)
{
	srand(time(NULL));

	mapName = map;
	for (int i = 0; i < 2; i++)
	{
		int randChoice = (rand() % 4) + 1;
		switch (randChoice)
		{
		case 1:
		{
	 		Space* spc = new Forest;
			this->addSpace(spc);
			break;
		}
		case 2:
		{
			Space* spc = new Surf;
			this->addSpace(spc);
			break;
		}
		case 3:
		{
			Space* spc = new Cave;
			this->addSpace(spc);
			break;
		}
		case 4:
		{
			Space* spc = new Hills;
			this->addSpace(spc);
			break;
		}

		}		
	}
	
}

/*********************************************************************
** Function: addSpace
** Description: adds new Space to Map. Takes space ptr.
*********************************************************************/
void Map::addSpace(Space* space)
{
	if (empty())
	{
		front = new SpaceNode(space);
		back = front;
	}
	else
	{
		back->next = new SpaceNode(space);
		back = back->next;
	}
}
/*********************************************************************
** Function: addRandom
** Description: adds given number of random wilderness spaces to map
*********************************************************************/
void Map::addRandom(int num)
{
	
	for (int i = 0; i < num; i++)
	{
		int randChoice = (rand() % 4) + 1;
		switch (randChoice)
		{
		case 1:
		{
			Space* spc = new Forest;
			this->addSpace(spc);
			break;
		}
		case 2:
		{
			Space* spc = new Surf;
			this->addSpace(spc);
			break;
		}
		case 3:
		{
			Space* spc = new Cave;
			this->addSpace(spc);
			break;
		}
		case 4:
		{
			Space* spc = new Hills;
			this->addSpace(spc);
			break;
		}

		}
	}
}
/*********************************************************************
** Function: remove
** Description: Removes Space from Map and returns
*********************************************************************/
Space* Map::remove()
{
	SpaceNode* old = NULL;
	Space* temp = NULL;
	if (empty())
	{
		std::cout << "Queue is empty!\n";
		return '\0';
	}
	else
	{
		temp = front->thisSpace;
		old = front;
		front = front->next;
		delete old;
		return temp;
	}
}
/*********************************************************************
** Function: peek
** Description: returns front space in Map
*********************************************************************/
Space* Map::peek()
{
	if (front != NULL)
	{
		return front->thisSpace;
	}
	else
	{
		return NULL;
	}

}
/*********************************************************************
** Function: empty
** Description: checks if front space is empty
*********************************************************************/
bool Map::empty() const
{
	if (front == NULL)
	{
		return true;
	}
	else return false;
}
/*********************************************************************
** Function: getName
** Description: Returns name of Map
*********************************************************************/
std::string Map::getName()
{
	return this->mapName;
}
/*********************************************************************
** Function: addHospStore
** Description: adds Hospital and Store to map, and 1 random wilderness
*********************************************************************/
void Map::addHospStore()
{
	
	Space* hosp = new Hospital;
	Space* store = new Store;	
	this->addSpace(hosp);
	this->addSpace(store);
	addRandom(1);
}
/*********************************************************************
** Function: addTrainer
** Description: adds trainer to map
*********************************************************************/
void Map::addTrainer(int t)
{
	Space* trainer = new Trainer(t);
	this->addSpace(trainer);	
}