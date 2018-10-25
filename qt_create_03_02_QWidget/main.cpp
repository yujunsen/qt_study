#include <QApplication>
#include <QWidget>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget widget;
    widget.resize(400, 300);    //窗口大小
    widget.move(200, 100);      //设置窗口位置
    widget.show();

    int x = widget.x();
    qDebug("x:%d", x);
    int y = widget.y();
    qDebug("y:%d", y);
    QRect geometry = widget.geometry();
    QRect frame = widget.frameGeometry();
    qDebug() << "geometry: " << geometry << " frame: " << frame;
    qDebug() << "pos:" << widget.pos() << endl
    //pos（）函数返回窗口的位置，是一个坐标值，上面的x（）、y（）函数返回的就是它的x、y坐标值；
             << "rect: " << widget.rect() << endl
    //rect（）函数返回不包含边框的窗口内部矩形，窗口内部左上角是（0，0）点；
             << "size:" << widget.size() << endl
    //size（）函数返回不包含边框的窗口大小信息；
             <<"width:" << widget.width()<< endl <<"height:" << widget.height();
    //width（）和height（）函数分别返回窗口内部的宽和高。
    //从数据可以看到，前面使用的调整窗口大小的resize（）函数是设置的不包含边框的窗口大小。
    return a.exec();
}
/*
 * 要使用qDebug（）函数，就要添加#include<QDebug>头文件。
 * 这里使用了两种输出方法，
 *      一种是直接将字符串当作参数传给qDebug（）函数，例如上面使用这种方法输出x和y的值。
 *      另一种方法是使用输出流的方式一次输出多个值，它们的类型可以不同，
 *      如程序中输出geometry和frame的值。
 * 如果只使用第一种方法，就不需要添加<QDebug>头文件；
 * 如果使用第二种方法就必须添加该头文件。
 * 因为第一种方法很麻烦，所以经常使用第二种方法。
 * 程序中还添加了设置窗口大小和位置的代码。下面运行程序，
 * 在应用程序输出窗口可以看到输出信息
*/


#if 0

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
#endif
