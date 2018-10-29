#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>

using namespace std;

class Time
{
public:

	//Time(){}
	static void changetime();//For "TIME" command
	static int gettime()//Function that will retrieve the current time;
	{
		return time;
	}

private:
	
	static int time;//Static cause time is global, only 1 time is needed
};

// #include "Time.cpp"
#endif