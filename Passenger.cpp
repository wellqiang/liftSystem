#include "Passenger.h"

Passenger::Passenger()
{
}

Passenger::Passenger(int M, int L, ElevatorLift * E[], Time * tm)
{
	NextFloor = (rand() % (40 - 1)) + 1 + 1;            //随机生成目标楼层
	status = LEAVE;                                     //状态为离开状态
	NowFloor = 1;                                       //初始楼层为1
	WaitTime = (rand() % (M * 60 - 1)) + 1;               //乘客初次等待时间
	Total = 0;                                          //总计等待时间
	times = L + 1;                                      //总乘梯次数  
	nowtime = tm;
	NextTime = (*nowtime + WaitTime);                   //设定下一次乘梯的时间
	for (int i = 0; i < 10; i++)
	{
		e[i] = E[i];
	}
	Select(group, which);
}


Passenger::~Passenger()
{
}

void Passenger::action()
{

	switch (status)
	{

	case  WAIT:
		//当前状态为等待，则查看电梯是否到达当前楼层，将状态置为 “乘坐”
		if (e[which]->people < e[which]->capacity)
		{   //如果电梯人数未满
			if (e[which]->NowFloor == NowFloor)
			{   //选定的电梯楼层与乘客所在楼层一致
				if (((NextFloor - NowFloor) > 0 && (e[which]->NextFloor - e[which]->NowFloor) >= 0) ||
					((NextFloor - NowFloor) < 0 && (e[which]->NextFloor - e[which]->NowFloor) <= 0))
				{   //并且方向一致
					status = TAKE;
					//统计等待
					Total = Total + (*nowtime - NextTime);
					//设定乘坐电梯的目标楼层
					if ((NextFloor - NowFloor) > 0)
					{
						e[which]->SetInsideUp(NextFloor, 1);   //设置目标楼层
						e[which]->SetUp(NowFloor, -1);         //撤销呼叫
						e[which]->people++;
					}
					else if ((NextFloor - NowFloor) < 0)
					{
						e[which]->SetInsideDown(NextFloor, 1);  //设置目标楼层
						e[which]->SetDown(NowFloor, -1);        //撤销呼叫
						e[which]->people++;
					}
					else
					{

					}
				}
			}
		}
		if ((*nowtime - NextTime) % 60 == 0)
		{
			//如果等待时间每超过一分钟 重新选择电梯
			//首先撤销上次的选择记录
			int  old_which = which;
			if ((NextFloor - NowFloor) > 0)
			{

				e[old_which]->SetUp(NowFloor, -1);   
			}
			else
			{
				e[old_which]->SetDown(NowFloor, -1);  ;
			}
			Select(group, which);  //如果电梯满员 重新选择电梯
			//重新设置新的电梯记录
			if ((NextFloor - NowFloor) > 0)
			{

				e[which]->SetUp(NowFloor, 1);    //Up[this->NowFloor] += 1;
			}
			else
			{
				e[which]->SetDown(NowFloor, 1);  //Down[this->NowFloor] += 1;
			}
		}

		break;
	case  TAKE:
		NowFloor = e[which]->NowFloor;        //更新当前乘坐电梯的楼层                               
	   //当前状态为乘坐，则查看是否到达目的楼层 ，将状态置为 “离开”或“停止”
		if (NowFloor == NextFloor)
		{
			times--;
			switch (times)
			{
			case 0:
				status = OVER;
				break;
			case 1:
				status = LEAVE;
				NextFloor = 1;
				NextTime = (*nowtime + 10);
				break;
			default:
				status = LEAVE;
				//设定新的目标楼层
				int temp = ((rand() % 40) + 1);
				while (temp == NowFloor)    //如果取出的数是当前楼层，则重新取随机数，直到不同
				{
					temp = ((rand() % 40) + 1);
				}
				NextFloor = temp;
				NextTime = (*nowtime + ((rand() % 111) + 10));     //生成下一次乘梯时间,随机停留10-120秒
				break;
			}
			e[which]->people--;

		}
		break;
	case LEAVE:
		//当前状态为离开，则查看是否到下次开始乘梯的时间 ，将状态置为 “等待”

		if (nowtime->second == NextTime.second && nowtime->minute == NextTime.minute &&nowtime->hour == NextTime.hour)
		{
			//改变状态
			status = WAIT;
			//选择乘坐的电梯组,与电梯
			Select(group, which);
			//设置电梯停靠楼层
			if ((NextFloor - NowFloor) > 0)
			{

				e[which]->SetUp(NowFloor, 1);    //Up[this->NowFloor] += 1;
			}
			else
			{
				e[which]->SetDown(NowFloor, 1);  //Down[this->NowFloor] += 1;
			}

		}
		break;
	case OVER:
		break;
	}

}
char * Passenger::GetStatus()
{
	switch (status)
	{

	case  WAIT:
		strcpy_s(str, "等待");
		break;
	case  TAKE:
		strcpy_s(str, "乘坐");
		break;
	case LEAVE:
		strcpy_s(str, "离开");
		break;
	case OVER:
		strcpy_s(str, "结束");
		break;
	}
	return str;
}

int Passenger::getstatus()
{
	return status;
}

int Passenger::GetNextFloor()
{
	return NextFloor;
}

int Passenger::GetNowFloor()
{
	return NowFloor;
}

int Passenger::Getwhich()
{
	return which + 1;
}

int Passenger::Gettimes()
{
	return times;
}

int Passenger::Getgroup()
{
	return group + 1;
}

int Passenger::GetTotal()
{
	return Total;
}

void  Passenger::Select(int & group, int & which)
{
	int select[10];                  //设定决策权重数组
	for (int i = 0; i < 10; i++)      //初始化
	{
		select[i] = 0;
	}
	select[0] = 1;
	select[1] = 1;
	//如果当前楼层与目标楼层为1,25-40
	if (((25 <= NowFloor && NowFloor <= 40) || NowFloor == 1) && ((25 <= NextFloor && NextFloor <= 40) || NextFloor == 1))
	{
		select[2] += 1;
		select[3] = 1;
	}
	//如果当前楼层与目标楼层为1-25
	if ((1 <= NowFloor && NowFloor <= 25) && (1 <= NextFloor && NextFloor <= 25))
	{
		select[4] += 1;
		select[5] = 1;
	}
	//如果当前楼层与目标楼层为偶数
	if ((NowFloor % 2 == 0 || NowFloor == 1) && (NextFloor % 2 == 0 || NextFloor == 1))
	{
		select[6] += 1;
		select[7] = 1;
	}
	//如果当前楼层与目标楼层为奇数
	if ((NowFloor % 2 == 1) && (NextFloor % 2 == 1))
	{
		select[8] += 1;
		select[9] = 1;
	}
	for (int i = 0; i < 10; i++)
	{
		if (e[i]->people >= (e[i]->capacity)*0.8)
		{
			select[i] = 0;
		}
	}

	// 进一步选择
	int direction = NextFloor - NowFloor;  //设定乘梯方向  >0 向上 <0向下
	for (int i = 0; i < 10; i++)
	{
		//在满足条件的电梯组中选择
		if (select[i])
		{
			//如果乘客要去上面
			if (direction > 0)
			{
				//如果电梯停
				if (e[i]->NextFloor - e[i]->NowFloor == 0)
				{
					select[i] = select[i] + 40 - abs((NowFloor - e[i]->NowFloor));   //距离越近，权重越大
				}
				//如果电梯向上
				else if (e[i]->NextFloor - e[i]->NowFloor > 0)
				{
					//并且电梯位置低于乘客位置
					if (e[i]->NowFloor <= NowFloor)
					{
						select[i] = select[i] + 40 - abs((NowFloor - e[i]->NowFloor));   //距离越近，权重越大	
					}
					else   //电梯位置高于乘客
					{
						select[i] = select[i] - abs((NowFloor - e[i]->NowFloor));
					}
				}
				//如果电梯向下
				else
				{
					//并且电梯位置高于乘客位置
					if (e[i]->NowFloor >= NowFloor)
					{
						select[i] = select[i] - abs((NowFloor - e[i]->NowFloor));   //距离越近，权重越大	
					}
					else   //电梯位置低于乘客
					{
						select[i] = select[i] + abs((NowFloor - e[i]->NowFloor));
					}
				}
			}
			else   //如果乘客要去下面
			{
				//如果电梯停
				if (e[i]->NextFloor - e[i]->NowFloor == 0)
				{
					select[i] = select[i] + 40 - abs((NowFloor - e[i]->NowFloor));   //距离越近，权重越大
				}
				//如果电梯向上
				else if (e[i]->NextFloor - e[i]->NowFloor > 0)
				{
					//并且电梯位置低于乘客位置
					if (e[i]->NowFloor <= NowFloor)
					{
						select[i] = select[i] - abs((NowFloor - e[i]->NowFloor));   //距离越近，权重越大	
					}
					else   //电梯位置高于乘客
					{
						select[i] = select[i] + abs((NowFloor - e[i]->NowFloor));
					}
				}
				//如果电梯向下
				else
				{
					//并且电梯位置高于乘客位置
					if (e[i]->NowFloor >= NowFloor)
					{
						select[i] = select[i] + 40 - abs((NowFloor - e[i]->NowFloor));   //距离越近，权重越大	
					}
					else   //电梯位置低于乘客
					{
						select[i] = select[i] - abs((NowFloor - e[i]->NowFloor));
					}
				}

			}
		}
	}

	//在select数组中取最大值的下标，即为最优选择电梯组
	int max = 10;
	for (int i = 9; i >= 0; i--)
	{
		if (select[i] != 0 && (select[max] < select[i]))
		{
			max = i;
		}
	}
	which = max;
	group = (max / 2);

}

