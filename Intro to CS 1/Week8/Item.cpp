#include "Item.hpp"

//default constructor
Item::Item()
{
	setName("");
	setPrice(0.0);
	setQuantity(0);
}

//constructor
Item::Item(std::string n, double p, int q)
{
	setName(n);
	setPrice(p);
	setQuantity(q);
}

//setters

void Item::setName(std::string n)
{
	name = n;
}
void Item::setPrice(double p)
{
	price = p;
}
void Item::setQuantity(int q)
{
	quantity = q;
}

//getters
std::string Item::getName()
{
	return name;
}
double Item::getPrice()
{
	return price;
}
int Item::getQuantity()
{
	return quantity;
}