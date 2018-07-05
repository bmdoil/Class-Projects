/*******************************************************
**Program Filename: State.cpp
**Author: Brent Doil
**Date: 5/8/2016
**Description: State interface
*********************************************************/

#ifndef STATE_HPP
#define STATE_HPP
#include <ctime>
#include <cstdlib>
#include <cstddef>
#include <iostream>
class State {
private:
	State* next;
	char directionEW;
	char directionNS;
	int arrived;
	int departed;
	int atLight1;
	int atLight2;
	int count;
	int nrOfVehiclesDepart();
	int nrOfVehiclesArrive();

public:
	State();
	~State() {};
	void setState(char EW, char NS);
	void setNext(State* link);
	State* getNext();
	char getDirEW();
	char getDirNS();
	int nrOfVehiclesAtLight1();
	int nrOfVehiclesAtLight2();
	
	int averageWait();
};
#endif // !STATE_HPP

