#ifndef LIFT_H
#define LIFT_H
#include "ElevatorLift.h"
#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#include <time.h>
#include <QTime>

#include "Passenger.h"
#include "Group.h"
#include "mainwindow.h"
class myLift{
public:
    myLift();

    //设定全局变量
    ElevatorLift  * E[10];                //电梯指针
    Passenger     * P[1000];              //乘客指针
    Group         * G[5];                 //电梯组指针
    Time Nowtime;
    int K = 13;                   //电梯的最大载客数量         10<K<18
    int N = 200;                 //乘客数量                   0<N<1000
    int M = 0;                  //初始等待时间    （分钟）   0<M<10
    int L = 4;                   //乘客的乘梯次数             1<L<10
    int S = 1;                   //电梯速度    单位 :秒/层    1<s<5
    int T = 1;                   //乘客上下电梯的时间         2<T<10

private:
    friend class MainWindow;
};

void myTimerProc(myLift* l);

#endif // LIFT_H
