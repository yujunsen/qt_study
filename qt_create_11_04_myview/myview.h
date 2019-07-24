#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>



class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QKeyEvent *event);
};

#endif // MYVIEW_H
