#ifndef ITEM_HPP
#define ITEM_HPP


#include <string>

class Item
{
private:
	std::string name;
	double price;
	int quantity;
public:
	//default constructor
	Item();

	//constructor
	Item(std::string n, double p, int q);

	//getters
	std::string getName();
	double getPrice();
	int getQuantity();
	
	//setters
	void setName(std::string n);
	void setPrice(double p);
	void setQuantity(int q);
};


#endif // !ITEM_HPP


