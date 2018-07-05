/*******************************************************
**Program Filename: Player.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: player interface
*********************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Backpack.hpp"
#include "Roster.hpp"

class Player
{
protected:
	std::string name;
	Roster* myRoster;
	int moveCount;
	bool active;
	bool win = false;
	
	Backpack* backpack;

public:
	Player(std::string, int);
	~Player();
	
	
	Backpack* getBackPack();
	Roster* getRoster();
	std::string getName();
	void setActive(bool);
	bool getActive();
	bool useItem(ItemType);
	void setWin();
	bool getWin();
	
};
#endif // !PLAYER_HPP

