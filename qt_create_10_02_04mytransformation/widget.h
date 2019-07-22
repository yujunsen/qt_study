#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class QTimer;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QTimer *timer;
    int angle;

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // WIDGET_H
