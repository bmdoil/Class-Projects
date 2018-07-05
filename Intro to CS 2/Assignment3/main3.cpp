/*******************************************************
**Program Filename: main3.cpp
**Author: Brent Doil
**Date: 4/28/2016
**Description: Assignment 3 main method
*********************************************************/

#include "FightLogic.hpp"
#include "CS162.hpp"
#include <iostream>

int main()
{
	srand(time(NULL));
	if (menu())
	{
		while (true)
		{
			int choice;
			description();
			choice = validNum("Choose your matchup: ", "Choose a number between 0 and 10:", 0, 10);
			switch (choice)
			{
			case 1:
			{
				
				BabaYaga* by = new BabaYaga;
				Barbarian* ba = new Barbarian;
				fightLogic(by,ba);
				delete by;
				delete ba;
				std::cout << "\n\n";				
				break;
			}
			case 2:
			{
				BabaYaga* by = new BabaYaga;
				BlueMen* bl = new BlueMen;
				fightLogic(by,bl);
				delete by;
				delete bl;
				std::cout << "\n\n";
				break;
			}
			case 3:
			{
				BabaYaga* by = new BabaYaga;
				Harry* ha = new Harry;
				fightLogic(by,ha);
				delete by;
				delete ha;
				std::cout << "\n\n";
				break;
			}
			case 4:
			{
				BabaYaga* by = new BabaYaga;
				Medusa* me = new Medusa;
				fightLogic(by,me);
				delete by;
				delete me;
				std::cout << "\n\n";
				break;
			}
			case 5:
			{
				Barbarian* ba = new Barbarian;
				BlueMen* bl = new BlueMen;
				fightLogic(ba,bl);
				delete ba;
				delete bl;
				std::cout << "\n\n";
				break;
			}
			case 6:
			{
				Barbarian* ba = new Barbarian;
				Harry* ha = new Harry;
				fightLogic(ba,ha);
				delete ba;
				delete ha;
				std::cout << "\n\n";
				break;
			}
			case 7:
			{
				Barbarian* ba = new Barbarian;
				Medusa* me = new Medusa;
				fightLogic(ba,me);
				delete ba;
				delete me;
				std::cout << "\n\n";
				break;
			}
			case 8:
			{
				BlueMen* bl = new BlueMen;
				Harry* ha = new Harry;
				fightLogic(bl,ha);
				delete bl;
				delete ha;
				std::cout << "\n\n";
				break;
			}
			case 9:
			{
				BlueMen* bl = new BlueMen;
				Medusa* me = new Medusa;
				fightLogic(bl,me);
				delete bl;
				delete me;
				std::cout << "\n\n";
				break;
			}
			case 10:
			{
				Harry* ha = new Harry;
				Medusa* me = new Medusa;
				fightLogic(ha, me);
				delete ha;
				delete me;
				std::cout << "\n\n";
				break;
			}
			case 0:
				return 0;
			}
		}
		
	}	
	
}

