/*******************************************************
**Program Filename: Cave.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: cave interface
*********************************************************/

#ifndef CAVE_HPP
#define CAVE_HPP


#include "Wilderness.hpp"

class Cave : public Wilderness
{
private:
public:
	Cave();
	~Cave() {};
	void actionBattle();
	Item* actionItem();
	void actionSpecial();

};
#endif // !CAVE_HPP
