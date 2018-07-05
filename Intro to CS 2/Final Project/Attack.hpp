/*******************************************************
**Program Filename: Attack.hpp
**Author: Brent Doil
**Date: 6/4/2016
**Description: attack interface
*********************************************************/

#ifndef ATTACK_HPP
#define ATTACK_HPP
#include <string>
class Attack
{
private:
	int power, accuracy;
	std::string name;


public:
	Attack(std::string, int, int);
	int getPower();
	int getAccuracy();
	std::string getName();
};

#endif // !ATTACK_HPP
