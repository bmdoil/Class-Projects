/*
2   * FibonacciNR.cpp
3   *
4   *  Created on: Sep 11, 2010
5   *      Author: julian
6   */

#include "Fibonacci.hpp"
#include <iostream>
FibonacciNR::FibonacciNR() 
{
	
	
}

FibonacciNR::FibonacciNR(const int &n):n_(&n)
{
}

 FibonacciNR::~FibonacciNR() {

}

 int FibonacciNR::Fibonacci(const int &n)
 {
	 int first = 0;
	 int second = 1;
	 int counter = 2;
	 while (counter < n)
	 {
		 int temp = second;
		 second = first + second;
		 first = temp;
		 ++counter;
	 }
	 if (n == 0)
		 return 0;
	 else
		 return first + second;
 }
void FibonacciNR::PrintFibonacci() {
	 const int result = Fibonacci(*n_);
	 std::cout << *n_ << "th fibonacci Number:" << result << std::endl;
	
}
/*
2   * FibonacciClass1.cpp
3   *
4   *  Created on: Sep 10, 2010
5   *      Author: julian
6   */


FibonacciR::FibonacciR() {

}

FibonacciR::FibonacciR(const int &n) :n_(&n) {

}

FibonacciR::~FibonacciR() {

}

int FibonacciR::Fibonacci(const int &n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	return Fibonacci(n - 1) + Fibonacci(n - 2);

}
void FibonacciR::PrintFibonacci() {
	int FibonaciNum = Fibonacci(*n_);
	std::cout << *n_ << "th fibonacci number: " << FibonaciNum << std::endl;

}