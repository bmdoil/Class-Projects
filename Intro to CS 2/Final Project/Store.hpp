/*******************************************************
**Program Filename: Store.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: store interface
*********************************************************/

#ifndef STORE_HPP
#define STORE_HPP

#include "Space.hpp"

class Store : public Space
{
protected:

public:
	Store();
	~Store() {};
	void actionSpecial();
};


#endif // STORE_HPP

