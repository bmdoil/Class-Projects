/*******************************************************
**Program Filename: CS162.hpp
**Author: Brent Doil
**Date: 4/9/2016
**Description: CS162 helper functions interface
*********************************************************/

#ifndef CS162_HPP
#define CS162_HPP
#include <limits>
#include <sstream>
#include <string>
#include <iostream>

int validInt(const std::string &prompt, const std::string &failmsg, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max()); //Function to validate integer input

bool menu();

#endif // !CS162_HPP

