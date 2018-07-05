/*******************************************************
**Program Filename: Hills.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: hills interface
*********************************************************/

#ifndef HILLS_HPP
#define HILLS_HPP
#include "Wilderness.hpp"


class Hills : public Wilderness
{
private:
public:
	Hills();
	~Hills() {};
	void actionBattle();
	Item* actionItem();
	void actionSpecial();

};
#endif // !HILLS_HPP

