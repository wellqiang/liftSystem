#include "Group.h"

/*构造函数*/
Group::Group(ElevatorLift * e1, ElevatorLift * e2)
{
	this->e1 = e1;
	this->e2 = e2;
}

Group::~Group()
{
}
/*电梯组更新状态*/
void Group::action()
{
	e1->action();
	e2->action();
}

