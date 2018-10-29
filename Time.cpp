#ifndef TIME_CPP
#define TIME_CPP

#include <iostream>
#include "Time.hpp"

using namespace std;

int Time::time=1;//Initialize time to 1

void Time::changetime()//Function for the "Time" command to update time
{
	int number;
	cout<<"Enter the number of days to time travel."<<endl;//Prompts user for a number
	cout<<"> ";
	cin>>number;//Stores it in number
	if(cin.fail() || number<1)//Makes sure user input is a number and a valid number
	{
		cout<<"Invalid value"<<endl;//If not a number or valid number
		cout<<""<<endl;
		cin.clear();
		cin.ignore(256, '\n');
	}
	else	
	{
		cout<<"Travelled "<<number<<" days through time ("<<time;//Display
		time=time+number;//Update time to its new time
		cout<<" --> "<<time<<")."<<endl;//Display
		cout<<""<<endl;
	}			
}

#endif