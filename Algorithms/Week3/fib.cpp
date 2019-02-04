#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <iostream>
#include <gmpxx.h>
#include <chrono>
#include <ctime>


using namespace std::chrono;

//O(n)
mpz_class fib(unsigned long long n)
{
    mpz_class f[n+1];
    int i;
    f[0] = 0; f[1] = 1;
    for (i = 2; i <= n; i++)
    {
        f[i] = f[i-1] + f[i-2];
    }
    return f[n];
}
// O(2^n)  T(n) = T(n-1) + T(n-2) + O(1)
mpz_class fibNaive(unsigned long long n)
{
    mpz_class f[n+1];
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibNaive(n-1) + fibNaive(n-2); 
}

int main(int argc, char* argv[]) {
    unsigned long long num;
    if (argc == 2) num = atoi(argv[1]);
    else num = 9;
    mpz_class result;
    mpz_class naiveResult;
    auto startTime = high_resolution_clock::now();
    result = fib(num);
    auto stopTime = high_resolution_clock::now();
    auto timeElapsed = duration_cast<nanoseconds>(stopTime - startTime);
    std::cout << "Fib of n=" << num << ": " <<  timeElapsed.count() << "ns" << std::endl;
    /*
    startTime = high_resolution_clock::now();
    naiveResult = fibNaive(num);
    stopTime = high_resolution_clock::now();
    timeElapsed = duration_cast<nanoseconds>(stopTime - startTime);    
    
    std::cout << "Naive of n=" << num << ": " <<  timeElapsed.count() << "ns" << std::endl;
    */
   return 0;

}