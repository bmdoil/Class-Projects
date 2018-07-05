/*******************************************************
**Program Filename: Trainer.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: trainer interface
*********************************************************/

#ifndef TRAINER_HPP
#define TRAINER_HPP
#include "Space.hpp"

class Trainer : public Space
{
protected:
	int trainerGold;
	
public:
	
	Trainer(int);
	~Trainer();
	void actionBattle();
	
	
};
#endif // !TRAINER_HPP
