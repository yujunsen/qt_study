#include "widget.h"
#include "ui_widget.h"
#include "dialog.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    this->setWindowTitle(QObject::tr("Widget"));
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    //先关闭主界面，其实它是隐藏起来了，并没有真正退出。然后新建MyDialog对象
    close();
    Dialog dialog;
    if(dialog.exec() == QDialog::Accepted)
    {
        this->show();
    }
}
/*
 * 需要说明的是那个close（）槽，它不一定使程序退出，
 * 只有当只剩下最后一个主界面了（就是没有父窗口的界面），
 * 这时调用close（）槽，程序才会退出；
 * 而其他情况下界面只是隐藏起来了，并没有被销毁。
*/
