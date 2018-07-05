/*******************************************************
**Program Filename: Forest.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: forest interface
*********************************************************/
#ifndef FOREST_HPP
#define FOREST_HPP
#include "Wilderness.hpp"

class Forest : public Wilderness
{
private:
	
public:
	Forest();
	~Forest() {};
	void actionBattle();
	Item* actionItem();
	void actionSpecial();
	
};
#endif // !FOREST_HPP

