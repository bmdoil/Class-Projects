/*********************************************************************
** Author: Brent Doil
** Date: 1/28/2016
** Description: Assignment 5.b BankAccount.cpp
*********************************************************************/
#include "BankAccount.hpp"

//constructor
BankAccount::BankAccount(string name, string ID, double balance)
{
	customerName = name;
	customerID = ID;
	customerBalance = balance;
}

string BankAccount::getCustomerName()
{
	return customerName;
}

string BankAccount::getCustomerID()
{
	return customerID;
}

double BankAccount::getCustomerBalance()
{
	return customerBalance;
}
//set customer balance (withdraw)
double BankAccount::withdraw(double w)
{
	customerBalance -= w;
	return customerBalance;
}
//set customer balance (deposit)
double BankAccount::deposit(double d)
{
	customerBalance += d;
	return customerBalance;
}