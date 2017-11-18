#include <iostream>
#include <fstream>
#include <sstream>
#include "Library.hpp"

using std::cout;

int mainMenu();
std::string getString(std::string);
//Read in values for id, title, author
//For each set of values, create a new book
// and add book to library
Book populateLib();

int main()
{

	Library lib;
	Book book1 = populateLib();
	//lib.addBook(&book1);
	Patron patron1("1", "Brent");
	Patron patron2("2", "Gwels");
	Patron patron3("3", "Me");
	bool retMenu = true;
	//cout << lib.getBook("1")->getAuthor() << "\n";
	//cout << lib.getBook("1")->getTitle() << "\n";
	//cout << lib.getBook("1")->getIdCode() << "\n";
	do
	{
		int choice = mainMenu();
		switch (choice)
		{
		case -1: return -1;
			break;
		case 1: // allow user input to add patron lib.addPatron(&patron1);
			break;
		case 2: lib.addBook(&book1);
			break;
		case 3: lib.checkOutBook("1", "1");
			break;
		case 4: lib.requestBook("1", "1");
			break;
		case 5: lib.returnBook("1");
			break;
		case 6: cout << lib.getBook("1")->getTitle();
			break;
		case 7: cout << lib.getPatron("1")->getName();
			break;
		}

		cout << "Return to menu? Yes[1] No[0]\n";
		std::cin >> retMenu;
		if (!retMenu)
		{
			return -1;
		}

	} while (retMenu);
}
	
	

	

	
	


int mainMenu()
{
	cout << "Welcome to the Library!\n";
	cout << "What would you like to do?\n";
	cout << "Enter the corresponding number [1-7]\n";
	cout << "Enter -1 to quit.\n";
	cout << "1. Add Patron\n";
	cout << "2. Add Book\n";
	cout << "3. Check out a book\n";
	cout << "4. Request a book\n";
	cout << "5. Return a book\n";
	cout << "6. Get book details\n";
	cout << "7. Get Patron details\n";

	int userChoice;
	while (!(std::cin >> userChoice) || userChoice < 1 || userChoice > 7)
	{
		if (userChoice == -1)
		{
			std::cout << "Goodbye.\n";
			return userChoice;
		}
		std::cout << "Enter a number between 1 and 7:";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return userChoice;
}
std::string getString(std::string s)
{
	std::getline(std::cin, s);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return s;
}
Book populateLib()
{

	std::string id;
	std::string author;
	std::string title;

	cout << "Enter Book ID # ";
	std::cin >> id;
	std::cin.ignore(80, '\n');

	cout << "Enter Book Author: ";
	std::cin >> author;
	std::cin.ignore(80, '\n');

	cout << "Enter Book Title: ";
	std::cin >> title;
	std::cin.ignore(80, '\n');


	Book book(id, title, author);
	
	return book;

	
}
