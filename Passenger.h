#pragma once
#include <stdlib.h>
#include "Time.h"
#include <Windows.h>
#include "ElevatorLift.h"
#include <time.h>
#include "Group.h"
class Passenger
{

public:
	Passenger();
	Passenger(int M, int L, ElevatorLift * E[], Time *tm);    //构造函数
	~Passenger();
	void action();											  //乘客的活动			
	void Select(int &group, int &which);                      //决策选乘的电梯组
	char * GetStatus();	                                      //get放法
	int getstatus();
	int GetNextFloor();
	int GetNowFloor();
	int Getwhich();
	int Gettimes();
	int Getgroup();
	int GetTotal();
	Time   NextTime;                      //下一次乘梯时间
private:
	enum Status
	{
		TAKE,     // 乘坐  
		LEAVE,    // 离开
		WAIT,     // 等待
		OVER      // 停止乘梯活动
	};
	Status status;                        //乘客状态
	int    WaitTime;                      //乘客初次等待时间
	int    NowFloor;                      //当前楼层
	int    NextFloor;                     //目标楼层
	int    which;                         //乘坐的电梯
	int    group;                         //选定的组号
	long   Total;                         //总计等待时间   （单位：秒)
	char   str[10];                       //存放电梯状态的字符串
	Time   *nowtime;                      //当前时间指针
	ElevatorLift * e[10];                 //电梯的指针
	Group * g[5];                         //电梯组的指针
	unsigned int times;                   //总乘梯次数


};

