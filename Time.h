#pragma once
/*此类主要用来处理与时间相关的事件，例如获取当前时间，时间的累加
重载了+、—号
*/
class Time
{
    public:
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	Time();
	Time( int hour, int minute, int second );
	Time operator + (int sec);   //时间+，单位为秒
	long operator - (Time & sub);
	void set( int hour,int minute,  int second);
	//void operator =(Time &time);
	~Time();
};

