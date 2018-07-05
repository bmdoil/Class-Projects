/*********************************************************************
** Author: Brent Doil
** Date: 1/28/2016
** Description: Assignment 5.b BankAccount.hpp
*********************************************************************/
#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include <string>

using namespace std;

class BankAccount
{
private:
	string customerName;
	string customerID;
	double customerBalance;
public:
	//constructor
	BankAccount(string name, string ID, double balance);	
	//getters
	string getCustomerName();
	string getCustomerID();
	double getCustomerBalance();
	//methods
	double withdraw(double w);
	double deposit(double d);
};

#endif // !BANK_ACCOUNT_HPP
