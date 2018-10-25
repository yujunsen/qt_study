#include <QtWidgets>
//QApplication、QWidget等，都包含在QtWidgets模块中
//#include <QLabel>

#if 0
#include "mywidget1.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget1 w;
    w.show();

    return a.exec();
}
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //新建Widget类对象 默认parent=nullptr 所以是一个窗口
    //auto widget = new QWidget();
    auto widget = new QWidget(nullptr, Qt::Dialog | Qt::FramelessWindowHint);
    //Qt::FramelessWindowHint用来产生一个没有边框的窗口

    widget->setWindowTitle(QObject::tr("我是widget"));
    //新建label类对象 默认parent=nullptr 所以是一个窗口
    //auto label = new QLabel();
    auto label = new QLabel(nullptr, Qt::SplashScreen | Qt::WindowStaysOnTopHint);
    //Qt::WindowStaysOnTopHint用来使该窗口停留在所有其他窗口上面
    label->setWindowTitle(QObject::tr("我是label"));
    label->setText(QObject::tr("label:我是窗口"));
    //改变布局大小，以便显示完整内容
    label->resize(250, 20);
    //labe2指定父窗口为widget，所以不是窗口
    auto label2 = new QLabel(widget);
    label2->setText(QObject::tr("label2：我不是独立窗口 我是widget的子部件"));
    label2->resize(250, 20);
    //屏幕显示
    label->show();
    widget->show();
    int ret = app.exec();
    delete label;
    delete widget;

    return ret;
}

/*
 * 在Qt的示例程序的按钮程序中有一个Window Flags程序演示了所有窗口类型，
 * 可以直接在Qt Creator的迎模式中打开它。
 * QWidget中还有一个setWindowState（）函数用来设置窗口的状态
 *  其参数由Qt:：WindowStates指定，
 * 是Qt:：WindowState枚举类型值的或组合。
 * 窗状态Qt:：WindowState包括最大化Qt:：WindowMaximized、
 * 最小化Qt:：Win dowMinimized、全屏显示
 * Qt:：WindowFulScreen和
 * 活动窗口Qt:：Window Active等默认值为
 * 正常状态Qt:：WindowNoState。
*/
