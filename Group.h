#pragma once
#include "ElevatorLift.h"
/*此类主要用来将电梯两两分组，实现电梯的联动效果*/
class Group
{
public:
	Group(ElevatorLift *e1, ElevatorLift *e2);
	~Group();
	void action();
private:
	ElevatorLift *e1;
	ElevatorLift *e2;
	friend class Passenger;

};
