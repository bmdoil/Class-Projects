/*******************************************************
**Program Filename: State.cpp
**Author: Brent Doil
**Date: 5/8/2016
**Description: State implementation
*********************************************************/

#include "State.hpp"
/*********************************************************************
** Function: State constructor
** Description: Seeds RNG, sets total arrive/departed to 0
*********************************************************************/
State::State()
{
	srand(time(NULL));
	arrived = 0;
	departed = 0;
	count = 0;
}
/*********************************************************************
** Function: setState
** Description: sets state of direction pair, either R/G/Y for each
*********************************************************************/
void State::setState(char EW, char NS)
{
	directionEW = EW;
	directionNS = NS;
}
/*********************************************************************
** Function: setNext
** Description: sets pointer to next State object in link
*********************************************************************/
void State::setNext(State* link)
{
	
	next = link;
}
/*********************************************************************
** Function: getNext
** Description: returns pointer to next State object
*********************************************************************/
State* State::getNext()
{
	
	return next;
}
/*********************************************************************
** Function: getDirEW
** Description: gets R/G/Y state of direction EW
*********************************************************************/
char State::getDirEW()
{
	return directionEW;
}
/*********************************************************************
** Function: getDirNS
** Description: gets R/G/Y state of direction NS
*********************************************************************/
char State::getDirNS()
{
	return directionNS;
}
/*********************************************************************
** Function: nrOfVehiclesAtLight1
** Description: calculates number of vehicles waiting at light (direction) 1
*********************************************************************/
int State::nrOfVehiclesAtLight1()
{
		atLight1 = this->nrOfVehiclesArrive() - this->nrOfVehiclesDepart();
		if (atLight1 < 0)
		{
			atLight1 = 0;
		}
		std::cout << atLight1 << " vehicles at light 1 of" << " East/West:" <<  this->getDirEW() << " North/South:" << this->getDirNS() << "\n";
		return atLight1;
	
}
/*********************************************************************
** Function: nrOfVehiclesAtLight2
** Description: calculates number of vehicles waiting at light (direction) 2
*********************************************************************/
int State::nrOfVehiclesAtLight2()
{
		atLight2 = this->nrOfVehiclesArrive() - this->nrOfVehiclesDepart();
		if (atLight2 < 0)
		{
			atLight2 = 0;
		}
		std::cout << atLight1 << " vehicles at light 2 of" << " East/West:" << this->getDirEW() << " North/South:" << this->getDirNS() << "\n";
		return atLight2;

}
/*********************************************************************
** Function: nrOfVehiclesArrive
** Description: calculates number of vehicles arriving during time cycle
** Adds 1 to count, keeps track of number of cycles completed
*********************************************************************/
int State::nrOfVehiclesArrive()
{
	count++;
	int arrive = (rand() % 5) + 1 + (rand() % 5) + 1;
	arrived += arrive;
	std::cout << arrive << " vehicles arrive.\n";
	return arrived;
}
/*********************************************************************
** Function: nrOfVehiclesDepart
** Description: calculates number of vehicles departing during time cycle
*********************************************************************/
int State::nrOfVehiclesDepart()
{
	int depart = (rand() % 6) + 1;
	departed += depart;
	std::cout << depart << " vehicles can depart\n";
	return departed;
}
/*********************************************************************
** Function: averageWait
** Description: calculates average wait for State
*********************************************************************/
int State::averageWait()
{
	if (departed != 0 && count != 0)
	{
		int totalVehicles = atLight1 + atLight2;
		int aveDepart = departed / count;
		return totalVehicles / aveDepart;
	}
	else return 0;
}