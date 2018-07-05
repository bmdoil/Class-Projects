#ifndef TRAFFIC_HPP
#define TRAFFIC_HPP

#include "Queue.hpp"

class Traffic
{
private:
	Queue* lane;
	int waitTime;
	int carCount;
	std::string direction;
	bool showOutput;
	
public:
	Traffic(std::string);
	~Traffic();
	void arriving(int);
	void departing(int);
	int getWait() const;
	void setOutPut(bool);
};

#endif // !TRAFFIC_HPP
