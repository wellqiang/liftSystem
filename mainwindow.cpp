#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lift.h"
#include <QTimer>
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QDialog>
#include "dialog.h"

myLift lift;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setLabelColor();
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(configureLift())); //调出配置页面
    connect(ui->pushButton_1, SIGNAL(clicked(bool)), this, SLOT(summaryLift())); //计算电梯总用时
    timeOutHandl();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::timeOutHandl()
{
    myTimerProc(&lift);
    MainWindow::showLiftState();
}
void MainWindow::showLiftState()
{
    //更新电梯的实时状态
     ui->label_18->setText(QString::fromStdString(lift.E[0]->GetStatus()));
     ui->label_19->setText(QString::number(lift.E[0]->GetNowFloor()));
     ui->label_20->setText(QString::number(lift.E[0]->GetNextFloor()));
     ui->label_21->setText(QString::number(lift.E[0]->Getpeople()));

     ui->label_22->setText(QString::fromStdString(lift.E[1]->GetStatus()));
     ui->label_23->setText(QString::number(lift.E[1]->GetNowFloor()));
     ui->label_24->setText(QString::number(lift.E[1]->GetNextFloor()));
     ui->label_25->setText(QString::number(lift.E[1]->Getpeople()));

     ui->label_26->setText(QString::fromStdString(lift.E[2]->GetStatus()));
     ui->label_27->setText(QString::number(lift.E[2]->GetNowFloor()));
     ui->label_28->setText(QString::number(lift.E[2]->GetNextFloor()));
     ui->label_29->setText(QString::number(lift.E[2]->Getpeople()));

     ui->label_30->setText(QString::fromStdString(lift.E[3]->GetStatus()));
     ui->label_31->setText(QString::number(lift.E[3]->GetNowFloor()));
     ui->label_32->setText(QString::number(lift.E[3]->GetNextFloor()));
     ui->label_33->setText(QString::number(lift.E[3]->Getpeople()));

     ui->label_34->setText(QString::fromStdString(lift.E[4]->GetStatus()));
     ui->label_35->setText(QString::number(lift.E[4]->GetNowFloor()));
     ui->label_36->setText(QString::number(lift.E[4]->GetNextFloor()));
     ui->label_37->setText(QString::number(lift.E[4]->Getpeople()));

     ui->label_38->setText(QString::fromStdString(lift.E[5]->GetStatus()));
     ui->label_39->setText(QString::number(lift.E[5]->GetNowFloor()));
     ui->label_40->setText(QString::number(lift.E[5]->GetNextFloor()));
     ui->label_41->setText(QString::number(lift.E[5]->Getpeople()));

     ui->label_42->setText(QString::fromStdString(lift.E[6]->GetStatus()));
     ui->label_43->setText(QString::number(lift.E[6]->GetNowFloor()));
     ui->label_44->setText(QString::number(lift.E[6]->GetNextFloor()));
     ui->label_45->setText(QString::number(lift.E[6]->Getpeople()));

     ui->label_46->setText(QString::fromStdString(lift.E[7]->GetStatus()));
     ui->label_47->setText(QString::number(lift.E[7]->GetNowFloor()));
     ui->label_48->setText(QString::number(lift.E[7]->GetNextFloor()));
     ui->label_49->setText(QString::number(lift.E[7]->Getpeople()));

     ui->label_50->setText(QString::fromStdString(lift.E[8]->GetStatus()));
     ui->label_51->setText(QString::number(lift.E[8]->GetNowFloor()));
     ui->label_52->setText(QString::number(lift.E[8]->GetNextFloor()));
     ui->label_53->setText(QString::number(lift.E[8]->Getpeople()));

     ui->label_54->setText(QString::fromStdString(lift.E[9]->GetStatus()));
     ui->label_55->setText(QString::number(lift.E[9]->GetNowFloor()));
     ui->label_56->setText(QString::number(lift.E[9]->GetNextFloor()));
     ui->label_57->setText(QString::number(lift.E[9]->Getpeople()));
     //显示当前时间
     QDateTime time = QDateTime::currentDateTime();
     QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
     ui->label_17->setText(str);

}
void MainWindow::setLabelColor()
{
    QPalette color1;//设置框体颜色
    color1.setColor(QPalette::WindowText,Qt::red);

    ui->label_18->setPalette(color1);
    ui->label_22->setPalette(color1);
    ui->label_26->setPalette(color1);
    ui->label_30->setPalette(color1);
    ui->label_34->setPalette(color1);
    ui->label_38->setPalette(color1);
    ui->label_42->setPalette(color1);
    ui->label_46->setPalette(color1);
    ui->label_50->setPalette(color1);
    ui->label_54->setPalette(color1);


    ui->label_60->setPalette(color1);
    ui->label_61->setPalette(color1);
    ui->label_62->setPalette(color1);
    ui->label_63->setPalette(color1);

    ui->label_64->setPalette(color1);
    ui->label_65->setPalette(color1);

    ui->label_66->setPalette(color1);
    ui->label_67->setPalette(color1);
    ui->label_68->setPalette(color1);
    ui->label_69->setPalette(color1);

    ui->label_70->setPalette(color1);
    ui->label_71->setPalette(color1);
    ui->label_72->setPalette(color1);
    ui->label_73->setPalette(color1);

    ui->label_74->setPalette(color1);
    ui->label_75->setPalette(color1);

    ui->label_76->setPalette(color1);
    ui->label_77->setPalette(color1);

    ui->label_78->setPalette(color1);
    ui->label_79->setPalette(color1);

    //设置时间显示的颜色
    QPalette color2;
    color2.setColor(QPalette::WindowText,Qt::blue);
    ui->label_17->setPalette(color2);
}

void MainWindow::summaryLift()
{
    /*填写标签*/
    ui->label_60->setText(QString::number(lift.E[0]->Getbusy()));
    ui->label_61->setText(QString::number(lift.E[0]->Getvacant()));

    ui->label_62->setText(QString::number(lift.E[1]->Getbusy()));
    ui->label_63->setText(QString::number(lift.E[1]->Getvacant()));

    ui->label_64->setText(QString::number(lift.E[2]->Getbusy()));
    ui->label_65->setText(QString::number(lift.E[2]->Getvacant()));

    ui->label_66->setText(QString::number(lift.E[3]->Getbusy()));
    ui->label_67->setText(QString::number(lift.E[3]->Getvacant()));

    ui->label_68->setText(QString::number(lift.E[4]->Getbusy()));
    ui->label_69->setText(QString::number(lift.E[4]->Getvacant()));

    ui->label_70->setText(QString::number(lift.E[5]->Getbusy()));
    ui->label_71->setText(QString::number(lift.E[5]->Getvacant()));

    ui->label_72->setText(QString::number(lift.E[6]->Getbusy()));
    ui->label_73->setText(QString::number(lift.E[6]->Getvacant()));

    ui->label_74->setText(QString::number(lift.E[7]->Getbusy()));
    ui->label_75->setText(QString::number(lift.E[7]->Getvacant()));

    ui->label_76->setText(QString::number(lift.E[8]->Getbusy()));
    ui->label_77->setText(QString::number(lift.E[8]->Getvacant()));

    ui->label_78->setText(QString::number(lift.E[9]->Getbusy()));
    ui->label_79->setText(QString::number(lift.E[9]->Getvacant()));

}

void MainWindow::configureLift()
{
    Dialog d;
    connect(&d, SIGNAL(liftRunSignal()), this, SLOT(liftRun()));
    d.exec();
    d.show();
}

void MainWindow::liftRun()
{
    id = QObject::startTimer(1000);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == id)
        timeOutHandl();
}
