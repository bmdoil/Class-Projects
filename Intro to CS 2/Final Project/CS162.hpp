/*******************************************************
**Program Filename: CS162.hpp
**Author: Brent Doil
**Date: 4/16/2016
**Description: CS162 helper functions interface
*********************************************************/

#ifndef CS162_HPP
#define CS162_HPP
#include <limits>
#include <sstream>
#include <string>
#include <iostream>

int validNum(const std::string &prompt, const std::string &failmsg, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max()); //Function to validate integer input
double validNum(const std::string &prompt, const std::string &failmsg, double min = std::numeric_limits<double>::min(), double max = std::numeric_limits<double>::max()); //Function to validate double input
double floatRand(double min, double max);

bool menu();
void description();
void hint();

#endif // !CS162_HPP

