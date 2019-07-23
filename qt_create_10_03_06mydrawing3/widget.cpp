#include "widget.h"
#include "ui_widget.h"

#include <QWindow>
#include <QScreen>
#include <QDesktopWidget>
#include <QLabel>
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //屏幕截图
    QWindow window;
    QPixmap grab =  window.screen()->grabWindow(QApplication::desktop()->winId());
    grab.save("./screen.png");
    QLabel *label = new QLabel(this);
    label->resize(400, 200);
    QPixmap pix = grab.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(pix);
    label->move(0, 100);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/yafeilinux.png");
    painter.drawPixmap(0, 0, pix.width(), pix.height(), pix);
    painter.setBrush(QColor(255, 255, 255, 100));
    painter.drawRect(0, 0, pix.width(), pix.height());
    painter.drawPixmap(100, 0, pix.width(), pix.height(), pix);
    painter.setBrush(QColor(0, 0, 255, 100));
    painter.drawRect(100, 0, pix.width(), pix.height());
}
