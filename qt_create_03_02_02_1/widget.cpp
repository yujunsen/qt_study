#include "widget.h"
#include "ui_widget.h"

#include <QDialog>
#include <QPushButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //connect(ui->showChildButton, &QPushButton::clicked, this, &Widget::showChildDialog);
    /*
     *  手动关联
     *  这里使用了connect（）函数将按钮的单击信号clicked（）与新建的槽进行关联。
     *  clicked（）信号在QPushButton类中定义，而connect（）是QObject类中的函数，
     *  因为MyWidget类继承自QObject，所以可以直接使用它。
     *  这个函数中的4个参数分别是发射信号的对象、发射的信号、接收信号的对象和要执行的槽。
     *  运行程序，然后单击主界面上的按钮就会弹出一个对话框。
    */
    /*
     *  自动关联就是将关联函数整合到槽命名中，
     *  比如前面的槽可以重命名为on_showChildButton_clicked（），
     *  就是由字符on、发射信号的部件对象名和信号名组成。
     *  这样就可以去掉connect（）关联函数
    */
}

Widget::~Widget()
{
    delete ui;
}

//void Widget::showChildDialog()
void Widget::on_showChildButton_clicked()
{
    QDialog * dialog = new QDialog(this);
    dialog->show();
}


