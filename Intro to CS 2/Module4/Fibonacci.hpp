/*
2   * FibonacciNR.h
3   *
4   *  Created on: Sep 11, 2010
5   *      Author: julian
6   */
#ifndef FIBONACCINR_HPP
#define FIBONACCINR_HPP
class FibonacciNR
{
public:
	FibonacciNR(const int &n);
	virtual ~FibonacciNR();
	void PrintFibonacci();
private:
	 FibonacciNR();
	 int Fibonacci(const int &n);
	 const int* n_;
		
};


/*
2   * FibonacciR.h
3   *
4   *  Created on: Sep 10, 2010
5   *      Author: julian
6   */
class FibonacciR {
public:
	FibonacciR(const int &n);
	virtual ~FibonacciR();
	void PrintFibonacci();
private:
	FibonacciR();
	int Fibonacci(const int &n);
	const int *n_;

};
 #endif 