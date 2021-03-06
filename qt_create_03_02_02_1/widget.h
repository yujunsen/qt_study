#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

public slots:
    //void showChildDialog();
    /*
     * 这里自定义了一个槽，槽一般使用slots关键字进行修饰（Qt4中必须使用，
     * Qt5使用新connect语法时可以不用，为了与一般函数进行区别，这里建议使用），
     * 这里使用了public slots，表明这个槽可以在类外被调用。
    */
    void on_showChildButton_clicked();
    //在编写程序时一般都使用第一种 connect方式
};

#endif // WIDGET_H
