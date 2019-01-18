#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
namespace Ui {
class MainWindow;
}
/*电梯的主界面，主要显示电梯的实时状态以及统计电梯总的运行和空闲时间*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTimer *timer;
    void showLiftState();//显示电梯运行状态
    void timeOutHandl();//定时器溢出处理函数
    friend class myLift;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    int id;
    Ui::MainWindow *ui;
    void setLabelColor();
    virtual void timerEvent( QTimerEvent *event);

private slots:

    void summaryLift();//统计空闲时间
    void configureLift();//配置电梯
    void liftRun();//电梯开始运行
};

#endif // MAINWINDOW_H
