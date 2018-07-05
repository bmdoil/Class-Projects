/*******************************************************
**Program Filename: Surf.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: surf interface
*********************************************************/

#ifndef SURF_HPP
#define SURF_HPP

#include "Wilderness.hpp"

class Surf : public Wilderness
{
private:
public:
	Surf();
	~Surf() {};
	void actionBattle();
	Item* actionItem();
	void actionSpecial();

};
#endif // !SURF_HPP

