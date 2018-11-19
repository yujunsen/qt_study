#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}

/*
 * QAbstractSlider类用于提供区间内的一个整数值，它有一个滑块，可以定位到一个整数区间的任意值。
 * 该类是一个抽象基类，它有3个子类QScrollBar、QSlider和QDial。
 * 其中，滚动条QScrollBar多数是用在QScrollArea类中来实现滚动区域；
 * QSider就是常见的音量控制或多媒体播放进度等滑块部件；QDial是一个刻度表盘部件。
 * 这些部件可以参考Sliders示例程序。
*/
