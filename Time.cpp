#include "Time.h"


Time::Time()
{
	this->hour = 0;
	this->minute = 0;
	this->second = 0;
}

Time::Time(int hour,  int minute,  int second)
{
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}


//重载+ 号
Time Time::operator+ ( int sec)
{
	Time time;
	time.hour = this->hour;
	time.minute = this->minute ;
	time.second=this->second;
	if (sec < 0)
		return time;
	time.second = time.second + sec;
	if (time.second >= 60)
	{
		time.minute = time.minute + time.second / 60;
		time.second = time.second % 60;
		if (time.minute >= 60)
		{
			time.hour = time.hour + time.minute / 60;
			time.minute = time.minute % 60;
			if (time.hour >= 24)
			{
				time.hour = time.hour - 24;
			}
		}
	}
	
	return time;
}
//重载 -
long Time::operator-(Time & sub)
{ 
	long a;   //被减数
	long b;   //减数
	a = this->hour * 3600 + this->minute * 60 + this->second;
	b = sub.hour * 3600 + sub.minute * 60 + sub.second;
	return a - b;
}

void Time::set( int hour,  int minute, int second)
{
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}





Time::~Time()
{
}
