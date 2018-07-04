#include <iostream>
#include "Library.hpp"

int main()
{
	Book b1("123", "War and Peace", "Tolstoy");
	Book b2("234", "Moby Dick", "Melville");
	Book b3("345", "Phantom Tollbooth", "Juster");
	
	Patron p1("abc", "Felicity");
	Patron p2("bcd", "Waldo");
	Library lib;
	lib.addBook(&b1);
	lib.addBook(&b2);
	lib.addBook(&b3);
	lib.addPatron(&p1);
	lib.addPatron(&p2);
	std::cout << "Check out book that isn't in library === ";
	std::cout << lib.checkOutBook("abc", "456") << "\n\n";
	std::cout << "Return book that isnt in library === ";
	std::cout << lib.returnBook("456") << "\n\n";
	std::cout << "Request book that isn't in library === ";
	std::cout << lib.requestBook("abc","456") << "\n\n";
	std::cout << "Check out book to patron who isn't a member === ";
	std::cout << lib.checkOutBook("aaa", "123") << "\n\n";
	std::cout << "Request book to patron who isn't a member === ";
	std::cout << lib.requestBook("aaa", "123") << "\n\n";
	std::cout << "Check out book 234 to Waldo ==== ";
	std::cout << lib.checkOutBook("bcd", "234") << "\n\n";
	std::cout << "Check out book 234 to Waldo ==== ";
	std::cout << lib.checkOutBook("bcd", "234") << "\n\n";
	std::cout << "Request book 234 for Felicity ==== ";
	std::cout << lib.requestBook("abc", "234") << "\n\n";
	std::cout << "Request book 234 for Felicity ==== ";
	std::cout << lib.requestBook("abc", "234") << "\n\n";
	std::cout << "Incrementing current date by 7... \n";
	for (int i = 0; i<7; i++)
		lib.incrementCurrentDate();
	
	std::cout << "Check out book 123 to Waldo ==== ";
	std::cout << lib.checkOutBook("bcd", "123") << "\n\n";
	std::cout << "Check out book 345 to Felicity ==== ";
	std::cout << lib.checkOutBook("abc", "345") << "\n\n";
	
	std::cout << "Incrementing current date by 24... \n";
	for (int i = 0; i<24; i++)
		lib.incrementCurrentDate();
	std::cout << "Book 123 Location ==== ";
	std::cout << (int)b1.getLocation() << "\n\n";
	std::cout << "Return book 123 ==== ";
	std::cout << lib.returnBook("123") << "\n\n";
	std::cout << "Book 123 Location ==== ";
	std::cout << (int)b1.getLocation() << "\n\n";
	std::cout << "\n\n";

	std::cout << "Book 234 Location ==== ";
	std::cout << (int)b2.getLocation() << "\n\n";
	std::cout << "Return book 234 ==== ";
	std::cout << lib.returnBook("234") << "\n\n";
	std::cout << "Book 234 Location ==== ";
	std::cout << (int)b2.getLocation() << "\n\n";
	std::cout << "\n\n";
	
	std::cout << "Book 345 Location ==== ";
	std::cout << (int)b3.getLocation() << "\n\n";
	std::cout << "Return book 345 ==== ";
	std::cout << lib.returnBook("345") << "\n\n";
	std::cout << "Book 345 Location ==== ";
	std::cout << (int)b3.getLocation() << "\n\n";
	std::cout << "Return book 345 ==== ";
	std::cout << lib.returnBook("345") << "\n\n";
	

	std::cout << "Patron 1\n";
	std::cout << "ID: " << lib.getPatron("abc")->getIdNum() << "\n\n";
	std::cout << "Name: " << lib.getPatron("abc")->getName() << "\n\n";
	std::cout << "Fine: " << lib.getPatron("abc")->getFineAmount() << "\n\n";
	std::cout << "\n\n";
	std::cout << "Patron 2\n";
	std::cout << "ID: " << lib.getPatron("bcd")->getIdNum() << "\n\n";
	std::cout << "Name: " << lib.getPatron("bcd")->getName() << "\n\n";
	std::cout << "Fine: " << lib.getPatron("bcd")->getFineAmount() << "\n\n";


	std::cout << "Waldo Fine: ";
	std::cout << p2.getFineAmount() << "\n\n";
	std::cout << "Pay .4 for Waldo: ";
	std::cout << lib.payFine("bcd", 0.4) << "\n\n";
	std::cout << "Waldo Fine: ";
	std::cout << p2.getFineAmount() << "\n\n";





	std::cout << "Felicity Fine: ";
	std::cout << p1.getFineAmount() << "\n\n";
	std::cout << "Pay .2 for Felicity: ";
	std::cout << lib.payFine("abc", 0.2) << "\n\n";
	std::cout << "Felicity Fine: ";
	std::cout << p1.getFineAmount() << "\n\n";
	



	std::cout << "Patron 1\n";
	std::cout << "ID: " << lib.getPatron("abc")->getIdNum() << "\n\n";
	std::cout << "Name: " << lib.getPatron("abc")->getName() << "\n\n";
	std::cout << "Fine: " << lib.getPatron("abc")->getFineAmount() << "\n\n";;
	std::cout << "\n\n";
	std::cout << "Patron 2\n";
	std::cout << "ID: " << lib.getPatron("bcd")->getIdNum() << "\n\n";
	std::cout << "Name: " << lib.getPatron("bcd")->getName() << "\n\n";
	std::cout << "Fine: " << lib.getPatron("bcd")->getFineAmount() << "\n\n";


	return 0;


}
