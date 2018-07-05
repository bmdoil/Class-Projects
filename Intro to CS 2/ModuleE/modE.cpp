/*******************************************************
**Program Filename: modE.cpp
**Author: Brent Doil
**Date: 5/8/2016
**Description: moduleE main method
*********************************************************/
#include "State.hpp"
#include "CS162.hpp"
#include <unistd.h>

int main()
{
	State* state1 = new State;
	State* state2 = new State;
	State* state3 = new State;
	State* state4 = new State;

	state1->setState('G', 'R');
	state2->setState('Y', 'R');
	state3->setState('R', 'G');
	state4->setState('R', 'Y');

	state1->setNext(state2);
	state2->setNext(state3);
	state3->setNext(state4);
	state4->setNext(state1);

	State* currentState = state1;

	int iterations = validNum("How many cycles? ","Enter a positive integer: ", 1);
	for (int i = 0; i < iterations; i++)
	{
		if (currentState->getDirEW() == 'G' || currentState->getDirNS() == 'G')
		{
			currentState->nrOfVehiclesAtLight1();
			currentState->nrOfVehiclesAtLight2();
			usleep(2000000);			
		}
		currentState = currentState->getNext();
	}
	int averageWait = (state1->averageWait() + state2->averageWait() + state3->averageWait() + state4->averageWait()) / 4;
	std::cout << "Average wait was: " << averageWait << " vehicles.\n";
	
	delete state1;
	delete state2;
	delete state3;
	delete state4;
}
