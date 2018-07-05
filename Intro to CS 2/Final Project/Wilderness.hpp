/*******************************************************
**Program Filename: Wilderness.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: wildnerness interface
*********************************************************/

#ifndef WILDERNESS_HPP
#define WILDERNESS_HPP
#include "Space.hpp"

#include <string>

class Wilderness : public Space
{
protected:
	
	
public:
	Wilderness();
	virtual ~Wilderness();
	virtual void actionSpecial() = 0;
	virtual Item* actionItem() = 0;
	virtual void actionBattle() = 0;
	

};

#endif
