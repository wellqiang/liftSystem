#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}
/*这个类主要用来获取用户输入的电梯系统参数，初始化电梯系统的数据类*/
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

signals:
    void liftRunSignal();

private:
    Ui::Dialog *ui;

private slots:
    void configureDone();

};

#endif // DIALOG_H
