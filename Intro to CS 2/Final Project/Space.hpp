/*******************************************************
**Program Filename: Space.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: space interface
*********************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP
#include "Backpack.hpp"
#include "Player.hpp"
#include "Pikachu.hpp"
#include "Squirtle.hpp"
#include "Bulbasaur.hpp"
#include "Charmander.hpp"

//Base class
//Derived classes are Wilderness,Trainer, Hospital, Store
//Derived classes of Wilderness are are Forest, Surf, Cave, Hills

class Space
{
protected:
	bool active;
	std::string name;
	Pokemon* poke1;
	Pokemon* poke2;
	Pokemon* poke3;
	Item* item1;
	Item* item2;
	Player* currentPlayer;

public:
	Space() {};
	~Space() {};

	virtual void actionSpecial() {};
	virtual Item* actionItem() { return NULL; };
	virtual void actionBattle() {};

	void setPlayer(Player*);
	Player* getPlayer();
	std::string getName();
	bool getActive();

};
#endif // !SPACE_HPP

