/*******************************************************
**Program Filename: Roster.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: roster interface
*********************************************************/

#ifndef ROSTER_HPP
#define ROSTER_HPP
#include "Pokemon.hpp"
class Roster 
{
private:
	int maxSize;
	Pokemon** roster;
	int currentSize;

public:
	Roster();
	Roster(int);
	~Roster();
	void add(Pokemon*);
	Pokemon* usePoke(std::string);
	void remove();
	void remove(std::string);
	bool empty() const;
	void displayRoster();
	bool checkAlive();
	void useRareCandy();
	void useHealPot();


};

#endif