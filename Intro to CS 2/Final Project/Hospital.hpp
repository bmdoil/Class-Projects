/*******************************************************
**Program Filename: Hospital.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: hospital interface
*********************************************************/

#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP
#include "Space.hpp"

class Hospital : public Space
{
protected:

public:
	Hospital();
	~Hospital() {};
	void actionSpecial();
};


#endif // !HOSPITAL_HPP

