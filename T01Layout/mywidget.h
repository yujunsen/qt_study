#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>


class mywidget : public QWidget
{
    Q_OBJECT
public:

    //声明explicit的构造函数不能在隐式转换中使用
    explicit mywidget(QWidget *parent = nullptr);

    ~mywidget()
    {}

private:

};

#endif // MYWIDGET_H
