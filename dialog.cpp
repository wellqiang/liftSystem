#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    /*连接按钮与配置电梯的槽*/
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(configureDone()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::configureDone()
{
    //发射开始运行电梯的信号
    emit liftRunSignal();
    this->hide();
   //qDebug()<<"OK";
}
