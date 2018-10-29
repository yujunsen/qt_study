#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    accept();
    /*
     * accept（）函数是QDialog类中的一个槽，对于一个使用exec（）函数实现的模态对话框，
     * 执行了这个槽就会隐藏这个模态对话框，并返回QDialog:：Accepted值
     * 使用这个值来判断是哪个按钮被按下了
     * 与其对应的还有一个reject（）槽，它可以返回一个QDialog:：Rejected值，
     * 前面的“退出程序”按钮也可以关联这个槽。
    */
}
