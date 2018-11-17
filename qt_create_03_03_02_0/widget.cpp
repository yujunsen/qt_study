#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QPushButton>
#include <QMenu>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushBtn1->setText(tr("&nihao"));//这样便指定了Alt+N为加速键
    ui->pushBtn2->setText(tr("帮助&(H)"));
    ui->pushBtn2->setIcon(QIcon("v001_24.png"));
    ui->pushBtn3->setText(tr("z&oom"));
    QMenu * menu = new QMenu(this);
    menu->addAction(QIcon("v013_12.png"), tr("放大"));
    ui->pushBtn3->setMenu(menu);
    /*
     * 字母前加上“8”符号，则可以将这个按钮的加速键设置为Alt加上这个字母。
     * 如果要在文本中显示“8”符号，可以使用“&&”。也可使用setlcon（）函数来给按钮添加图标，
     * 这里的图片文件使用了相对路径（当然也可以在设计模式通过更改icon属性来实现）。
     * 对于pushBtn3，这里为其添加了下拉菜单，现在这个菜单什么功能也没实现。
    */
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushBtn1_clicked(bool checked)//按钮是否处于被按下状态
{
    qDebug() << tr("检查按键是否按下:") << checked;
}
