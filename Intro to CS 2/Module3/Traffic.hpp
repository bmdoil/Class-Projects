#ifndef TRAFFIC_HPP
#define TRAFFIC_HPP
#include <queue>
#include <ctime>
#include <string>
#include <iostream>


class Traffic
{
private:
	std::queue<int> lane;
	int waitTime;
	int carCount;
	std::string direction;
	bool showOutput;
	
public:
	Traffic(std::string);	
	void arriving(int);
	void departing(int);
	int getWait() const;
	void setOutPut(bool);
};

#endif // !TRAFFIC_HPP
