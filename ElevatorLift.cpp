#include "ElevatorLift.h"
#include <math.h>
#include <time.h>
#include <QDebug>

ElevatorLift::ElevatorLift()
{
}
ElevatorLift::ElevatorLift(int S, int K, int T, Time *tm)
{
	status = STOP;                       //初始电梯停止
	NowFloor = (rand() % (40 - 1)) + 1;  // 随机生成电梯停靠位置 
	NextFloor = NowFloor;                //电梯停止时目标楼层与当前楼层一致
	nowfloor = NowFloor;                 //用于计算的位置
	speed = 1 / (float)S;                  //设置速度  s的单位为秒/层   speed 单位为 层/秒
	StopTime = T;                        // 每个乘客上下电梯的时间  
	capacity = K;                        //电梯的容量
	people = 0;                          //当前电梯的人数
	vacant = 0;                            //电梯空闲时间
	busy = 0;                              //电梯运行时间
	nowtime = tm;
	Over = *nowtime;
	//初始化
	for (int i = 0; i < 41; i++)
	{

		Up[i] = 0;
		Down[i] = 0;
		InsideUp[i] = 0;
		InsideDown[i] = 0;
	}

}


ElevatorLift::~ElevatorLift()
{
}

void ElevatorLift::action()
{
	UpdateNowFloor();       // 更新当前电梯所在楼层
	UpdateDestination();    // 更新电梯下一站的目的楼层
	ChangeStatus();         // 判断改变当前电梯状态
	Run();                  // 电梯运行
}

char * ElevatorLift::GetStatus()
{

	switch (status)
	{
	case UP:
        strcpy_s(str, "up");
		break;
	case UPSTOP:
        strcpy_s(str, "up_s");
		break;
	case DOWN:
        strcpy_s(str, "down");
		break;
	case DOWNSTOP:
        strcpy_s(str, "down_s");
		break;
	case STOP:
        strcpy_s(str, "stop");
		break;
	default:
		break;
	}
	return str;
}

int ElevatorLift::GetNextFloor()
{
	return NextFloor;
}

int ElevatorLift::GetNowFloor()
{
	return NowFloor;
}

int ElevatorLift::Getpeople()
{
	return people;
}

int ElevatorLift::Getbusy()
{
	return busy;
}

int ElevatorLift::Getvacant()
{
	return vacant;
}

void ElevatorLift::SetUp(int floor, int n)
{
	Up[floor] += n;
}

void ElevatorLift::SetDown(int floor, int n)
{
	Down[floor] += n;
}

void ElevatorLift::SetInsideUp(int floor, int n)
{
	InsideUp[floor] += n;
}

void ElevatorLift::SetInsideDown(int floor, int n)
{
	InsideDown[floor] += n;
}





void ElevatorLift::UpdateNowFloor()
{
	NowFloor = (int)nowfloor;
}
void ElevatorLift::UpdateDestination()
{
	switch (status)
	{
	case UP:
		for (int i = NowFloor; i < Max; i++)   //从当前楼层上一层开始查询，如果有停靠记录，取最近的楼层为目标楼层
		{
			if (Up[i] || InsideUp[i])
			{
				NextFloor = i;
				break;
			}
		}
		break;
	case UPSTOP:
		for (int i = NowFloor; i < Max; i++)   //从当前楼层开始查询，如果有停靠记录，取最近的楼层为目标楼层
		{
			if (Up[i] || InsideUp[i] || Down[i])
			{
				NextFloor = i;
				break;
			}
		}
		break;
	case DOWN:
		for (int i = NowFloor; i > 0; i--)   //从当前楼层开始查询，如果有停靠记录，取最近的楼层为目标楼层
		{
			if (Down[i] || InsideDown[i])
			{
				NextFloor = i;
				break;
			}
		}
		break;
	case DOWNSTOP:
		for (int i = NowFloor; i > 0; i--)   //从当前楼层开始查询，如果有停靠记录，取最近的楼层为目标楼层
		{
			if (Down[i] || InsideDown[i] || Up[i])
			{
				NextFloor = i;
				break;
			}
		}
		break;
	case STOP:
		if (IsTake())                   //如果电梯停下来，以后还有目标楼层
		{
			NextFloor = IsTake();
		}
		else
		{                                //没人乘坐的话，查询呼叫
			if (call())                  //如果有人呼叫电梯
				NextFloor = call();
		}
		break;
	default:
		break;
	}

}

void ElevatorLift::ChangeStatus()
{
	switch (status)
	{
	case STOP:                         //状态为停止，则检查是否改变状态到“上”或“下”

		if (NextFloor != NowFloor)    //如果发现目标楼层与当前楼层不一致，则需要启动电梯
		{
			if (NextFloor - NowFloor > 0)
			{
				status = UP;
				vacant += (*nowtime - Over);
				Start = *nowtime;
			}
			else
			{
				status = DOWN;
				vacant += (*nowtime - Over);
				Start = *nowtime;
			}
		}
		break;
	case UP:          //状态为向上运行，则检查是否改变状态到“上停”
		if (NextFloor == NowFloor)     //如果到达停靠楼层
		{
			status = UPSTOP;
			NextStart = (*nowtime + (1 + Up[NowFloor] + InsideUp[NowFloor])*StopTime);  //计算停留时间
			InsideUp[NowFloor] = 0;                                               //乘客上下电梯

		}
		break;
	case UPSTOP:
		if (NextStart.hour == nowtime->hour&&NextStart.minute == nowtime->minute&&NextStart.second == nowtime->second)
		{
			if (NextFloor > NowFloor)
			{
				status = UP;
			}
			else
			{
				status = STOP;
				busy += (*nowtime - Start);
				Over = *nowtime;
			}
		}
		break;
	case DOWN:
		if (NextFloor == NowFloor)     //如果到达停靠楼层
		{
			status = DOWNSTOP;
			NextStart = (*nowtime + (1 + Down[NowFloor] + InsideDown[NowFloor])*StopTime);  //计算停留时间
			InsideDown[NowFloor] = 0;
		}
		break;
	case DOWNSTOP:
		if (NextStart.hour == nowtime->hour&&NextStart.minute == nowtime->minute&&NextStart.second == nowtime->second)
		{
			if (NextFloor >= NowFloor)
			{
				status = STOP;
				busy += (*nowtime - Start);
				Over = *nowtime;
			}
			else
			{
				status = DOWN;
			}
		}
		break;

	default:
		break;
	}
    //qDebug()<<status;
}

void ElevatorLift::Run()
{


	if (status == UP)      //如果电梯向上运行
	{

		nowfloor += speed;    //speed为电梯每秒的运行速度
		//int temp = 0;
		//for (int i = NowFloor; i < 41; i++)
		//{
		//	temp += InsideUp[i];
		//}//统计人数
		//people = temp;
	}
	else if (status == DOWN)   //向下运行
	{
		nowfloor -= speed;//
		//int temp = 0;
		//for (int i = NowFloor; i > 0; i--)
		//{
		//	temp += InsideDown[i];
		//}//统计人数
		//people = temp;
	}
	else if (status == UPSTOP)
	{
		//int temp = 0;
		//for (int i = NowFloor; i < 41; i++)
		//{
		//	temp += InsideUp[i];
		//}//统计人数
		//people = temp;                            // 1.电梯制动
											// 2.使电梯位置与楼层地面相平
	}
	else if (status == DOWNSTOP)   //向下运行
	{
		//int temp = 0;
		//for (int i = NowFloor; i > 0; i--)
		//{
		//	temp += InsideDown[i];
		//}//统计人数
		//people = temp;
	}
	else
	{

	}

}


int ElevatorLift::call()
{
	for (int i = 1; i < Max; i++)
	{
		if (Up[i] || Down[i])
			return i;
	}
	return 0;
}

int ElevatorLift::IsTake()
{
	for (int i = 1; i < Max; i++)
	{
		if (InsideUp[i] || InsideDown[i])
			return i;
	}
	return 0;
}





E1::E1(int S, int K, int T, Time * tm)
{
	status = STOP;                       //初始电梯停止
	NowFloor = (rand() % (40 - 1)) + 1;  // 随机生成电梯停靠位置 
	NextFloor = NowFloor;                //电梯停止时目标楼层与当前楼层一致
	nowfloor = NowFloor;                 //用于计算的位置
	speed = 1 / (float)S;                  //设置速度  s的单位为秒/层   speed 单位为 层/秒
	StopTime = T;                        // 每个乘客上下电梯的时间  
	capacity = K;                        //电梯的容量
	people = 0;                          //当前电梯的人数
	vacant = 0;                            //电梯空闲时间
	busy = 0;                              //电梯运行时间
	nowtime = tm;
	Over = *nowtime;
	//初始化
	for (int i = 0; i < 41; i++)
	{

		Up[i] = 0;
		Down[i] = 0;
		InsideUp[i] = 0;
		InsideDown[i] = 0;
	}
}

E4::E4(int S, int K, int T, Time * tm)
{
	status = STOP;                       //初始电梯停止
	NowFloor = (rand() % (40 - 1)) + 1;  // 随机生成电梯停靠位置 
	NextFloor = NowFloor;                //电梯停止时目标楼层与当前楼层一致
	nowfloor = NowFloor;                 //用于计算的位置
	speed = 1 / (float)S;                  //设置速度  s的单位为秒/层   speed 单位为 层/秒
	StopTime = T;                        // 每个乘客上下电梯的时间  
	capacity = K;                        //电梯的容量
	people = 0;                          //当前电梯的人数
	vacant = 0;                            //电梯空闲时间
	busy = 0;                              //电梯运行时间
	nowtime = tm;
	Over = *nowtime;
	//初始化
	for (int i = 0; i < 41; i++)
	{

		Up[i] = 0;
		Down[i] = 0;
		InsideUp[i] = 0;
		InsideDown[i] = 0;
	}
}

E2::E2(int S, int K, int T, Time * tm)
{
	status = STOP;                       //初始电梯停止
	NowFloor = (rand() % (40 - 1)) + 1;  // 随机生成电梯停靠位置 
	NextFloor = NowFloor;                //电梯停止时目标楼层与当前楼层一致
	nowfloor = NowFloor;                 //用于计算的位置
	speed = 1 / (float)S;                  //设置速度  s的单位为秒/层   speed 单位为 层/秒
	StopTime = T;                        // 每个乘客上下电梯的时间  
	capacity = K;                        //电梯的容量
	people = 0;                          //当前电梯的人数
	vacant = 0;                            //电梯空闲时间
	busy = 0;                              //电梯运行时间
	nowtime = tm;
	Over = *nowtime;
	//初始化
	for (int i = 0; i < 41; i++)
	{

		Up[i] = 0;
		Down[i] = 0;
		InsideUp[i] = 0;
		InsideDown[i] = 0;
	}
}

E3::E3(int S, int K, int T, Time * tm)
{
	status = STOP;                       //初始电梯停止
	NowFloor = (rand() % (40 - 1)) + 1;  // 随机生成电梯停靠位置 
	NextFloor = NowFloor;                //电梯停止时目标楼层与当前楼层一致
	nowfloor = NowFloor;                 //用于计算的位置
	speed = 1 / (float)S;                  //设置速度  s的单位为秒/层   speed 单位为 层/秒
	StopTime = T;                        // 每个乘客上下电梯的时间  
	capacity = K;                        //电梯的容量
	people = 0;                          //当前电梯的人数
	vacant = 0;                            //电梯空闲时间
	busy = 0;                              //电梯运行时间
	nowtime = tm;
	Over = *nowtime;
	//初始化
	for (int i = 0; i < 41; i++)
	{

		Up[i] = 0;
		Down[i] = 0;
		InsideUp[i] = 0;
		InsideDown[i] = 0;
	}
}


void E1::SetUp(int floor, int n)
{
	if ((floor <= 40 && 25 <= floor) || floor == 1)
	{
		Up[floor] += n;
	}
}

void E1::SetDown(int floor, int n)
{
	if ((floor <= 40 && 25 <= floor) || floor == 1)
	{
		Down[floor] += n;
	}
}

void E1::SetInsideUp(int floor, int n)
{
	if ((floor <= 40 && 25 <= floor) || floor == 1)
	{
		InsideUp[floor] += n;
	}
}

void E1::SetInsideDown(int floor, int n)
{
	if ((floor <= 40 && 25 <= floor) || floor == 1)
	{
		InsideDown[floor] += n;
	}
}

void E2::SetUp(int floor, int n)
{
	if (floor <= 25 && 1 <= floor)
	{
		Up[floor] += n;
	}
}

void E2::SetDown(int floor, int n)
{
	if (floor <= 25 && 1 <= floor)
	{
		Down[floor] += n;
	}
}

void E2::SetInsideUp(int floor, int n)
{
	if (floor <= 25 && 1 <= floor)
	{
		InsideUp[floor] += n;
	}
}

void E2::SetInsideDown(int floor, int n)
{
	if (floor <= 25 && 1 <= floor)
	{
		InsideDown[floor] += n;
	}
}

void E3::SetUp(int floor, int n)
{
	if (floor % 2 ==  0 || floor == 1)
	{
		Up[floor] += n;
	}
}

void E3::SetDown(int floor, int n)
{
	if (floor % 2 == 0 || floor==1)
	{
		Down[floor] += n;
	}
}

void E3::SetInsideUp(int floor, int n)
{
	if (floor % 2 == 0 || floor == 1)
	{
		InsideUp[floor] += n;
	}
}

void E3::SetInsideDown(int floor, int n)
{
	if (floor % 2 == 0 || floor == 1)
	{
		InsideDown[floor] += n;
	}
}

void E4::SetUp(int floor, int n)
{
	if (floor % 2 == 1)
	{
		Up[floor] += n;
	}
}

void E4::SetDown(int floor, int n)
{
	if (floor % 2 == 1)
	{
		Down[floor] += n;
	}
}

void E4::SetInsideUp(int floor, int n)
{
	if (floor % 2 == 1)
	{
		InsideUp[floor] += n;
	}
}

void E4::SetInsideDown(int floor, int n)
{
	if (floor % 2 == 1)
	{
		InsideDown[floor] += n;
	}
}


