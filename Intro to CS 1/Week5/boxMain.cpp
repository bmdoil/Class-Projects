#include "Box.hpp"
#include <iostream>

using namespace std;

int main()
{

	double length, width, height;
	cout << "We are making a box. Set the dimensions.\n";
	cout << "Enter [L][H][W]\n";
	cin >> length >> height >> width;
	cout << "\nThanks for the info!\n";

	
	Box box1;
	Box box2;
	box2.setHeight(height);
	box2.setLength(length);
	box2.setWidth(width);

	cout << box1.getSurfaceArea() << " Default box SA\n";
	cout << box1.getVolume() << " Default box volume\n";
	cout << box2.getSurfaceArea() << " Our box SA\n";
	cout << box2.getVolume() << " Our box volume\n";

	


}
