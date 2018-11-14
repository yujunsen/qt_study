#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QMovie>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->frame->setFrameShape(QFrame::Box);
    ui->frame->setFrameShadow(QFrame::Sunken);
    //以上俩个函数可以用ui->frame->setFrameStyle(QFrame::Box | QFrame::Sunken);代替
    ui->frame->setLineWidth(5);
    ui->frame->setMidLineWidth(10);

    QFont font;
    font.setFamily("微软雅黑");
    font.setPointSize(20);
    font.setBold(true);
    font.setItalic(true);
    ui->label->setFont(font);
    /*
     * QFont类提供了对字体的设置，这里使用了“微软雅黑”字体族、
     * 大小为20、加粗、斜体，通过QLabel的setFont（）函数可以使用新建的字体。
    */

    QString string = tr("标题太长,需要进行省略!");
    QString str = ui->label->fontMetrics().elidedText(string, Qt::ElideRight, 180);
    ui->label->setText(str);
    /*
     * QLabel属性栏中的wordWrap属性可以实现文本的自动换行。
     * 如果文本过长时不想自动换行，而是在后面自动省略，
     * 那么可以使用QFontMetrics类，该类用来计算给定字体的字符或字符串的大小，
     * 其中包含了多个实用函数。要使用QFontMetrics，
     * 则可以通过创建对象的方式，或通过QWidget；；fontMetrics（）
     * 来返回当前部件字体的QFontMetrics对象。：
     * QFontMetrics类的elidedText（）函数用来进行文本省略，第
     *      一个参数用来指定要省略的文本；
     *      第二个参数是省略模式，就是“..”省略号出现的位置，包括
     *      Qt；：ElideLeft出现在文本开头、Qt:：ElideMiddle出现在文本中间，
     * 以及这里使用的Qt；：ElideRight出现在文本末尾；
     *  第三个参数是文本的长度，单位是像素，只要第一个参数指定的文本的长度超过了这个值，
     *  就会进行省略。可以运行程序，调整参数值，从而查看不同参数的效果。
    */
    ui->label->setPixmap(QPixmap("D:/code/qt_git/qt_create_03_03_01_0/ss.png"));
    QMovie * movie = new QMovie("D:/code/qt_git/qt_create_03_03_01_0//ww.gif");
    ui->label->setMovie(movie);
    movie->start();
    ui->lcdNumber->display(55.5);
}

Widget::~Widget()
{
    delete ui;
}
