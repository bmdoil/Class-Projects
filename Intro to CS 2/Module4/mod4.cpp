#include "Fibonacci.hpp"
#include "CS162.hpp"
#include <iostream>
#include <ctime>

//Taken from CS162 lecture slides
unsigned long long rfactorial(unsigned long long n);
unsigned long long factorialHelper(unsigned long long n, unsigned long long result);
unsigned long long factorial(unsigned long long n);

int main()
{
	int choice = validNum("Enter an integer n ", "Enter a positive integer.", 1);
	
	/*Not tail recursive
	clock_t time1 = clock();
	std::cout << rfactorial(choice) << "\n";
	time1 = clock() - time1;
	std::cout << "Recursive factorial took:" << (float)time1 / CLOCKS_PER_SEC << " seconds.\n";
	*/

	/*Tail recursive
	clock_t time2 = clock();
	std::cout << factorial(choice) << "\n";
	time2 = clock() - time2;
	std::cout << "Recursive factorial took:" << (float)time2 / CLOCKS_PER_SEC << " seconds.\n";
	*/


	/*Recursion fib
	clock_t time3 = clock();
	FibonacciR recur(choice);
	recur.PrintFibonacci();
	time3 = clock() - time3;
	std::cout << "Recursion Fibonacci took: " << (float)time3 / CLOCKS_PER_SEC << " seconds.\n";
	*/

	//Iteration fib
	clock_t time4 = clock();
	FibonacciNR iter(choice);
	iter.PrintFibonacci();
	time4 = clock() - time4;
	std::cout << "Iteration Fibonacci took: " << (float)time4 / CLOCKS_PER_SEC << " seconds.\n";


		



	
	


	
}
//Not tail recursive from slides
unsigned long long rfactorial(unsigned long long n)
{
	if (n == 1)
		return 1;
	else
		return n * rfactorial(n - 1);
}


//Tail recursive from slides
unsigned long long factorialHelper(unsigned long long n, unsigned long long result) {
	if (n == 1)
		return result;
	else
		return factorialHelper(n - 1, n*result);
}
unsigned long long factorial(unsigned long long n)
{
	return factorialHelper(n, 1);
}
