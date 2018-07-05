#include "BankAccount.hpp"
#include <iostream>

using namespace std;

int main()
{
	BankAccount customer1("Brent", "001", 1000.00);
	
	cout << "Name: " << customer1.getCustomerName() << endl;
	cout << "ID: " << customer1.getCustomerID() << endl;
	cout << "Balance: " << customer1.getCustomerBalance() << endl;
	cout << "Withdraw 2000.00\n";
	customer1.withdraw(2000.00);
	cout << "New balance: " << customer1.getCustomerBalance() << endl;
	cout << "Deposit 5555.55\n";
	customer1.deposit(5555.55);
	cout << "New balance: " << customer1.getCustomerBalance() << endl;
}