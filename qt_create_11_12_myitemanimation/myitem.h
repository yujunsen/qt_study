#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsObject>



class MyItem : public QGraphicsObject
{
public:
    MyItem(QGraphicsObject *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // MYITEM_H
