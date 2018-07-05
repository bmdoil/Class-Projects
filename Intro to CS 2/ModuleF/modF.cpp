#include "CS162.hpp"
#include "Traffic.hpp"


int main()
{
	
	Traffic north("North");
	Traffic south("South");
	Traffic east("East");
	Traffic west("West");

	int iterations = validNum("How many cycles? ", "Enter a positive integer: ", 1);
	int output = validNum("Would you like to show individual output for each lane?\n[1]Yes\n[2]No\n", "Please enter a 1 or 2: ", 1, 2);
	if (output == 1)
	{
		north.setOutPut(true);
		south.setOutPut(true);
		east.setOutPut(true);
		west.setOutPut(true);
	}
	for (int i = 1; i <= iterations; i++)
	{
		north.arriving(i);
		south.arriving(i);
		east.arriving(i);
		west.arriving(i);

		north.departing(i);
		south.departing(i);
		east.departing(i);
		west.departing(i);
	}
	int totalWait = (north.getWait() + south.getWait() + east.getWait() + west.getWait()) / 4;
	
	std::cout << "Average North wait was: " << north.getWait() << "\n";
	std::cout << "Average South wait was: " << south.getWait() << "\n";
	std::cout << "Average East wait was: " << east.getWait() << "\n";
	std::cout << "Average West wait was: " << west.getWait() << "\n";
	std::cout << "Average wait was: " << totalWait << " vehicles.\n";
	 


}