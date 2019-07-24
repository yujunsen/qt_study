#include "myitem.h"

#include <QMouseEvent>
#include <QPainter>
#include <QCursor>
#include <QKeyEvent>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsBlurEffect>

MyItem::MyItem()
{
    brushColor = Qt::red;

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF MyItem::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10 - adjust, -10 - adjust,
                  20 + adjust, 20 + adjust);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    if(hasFocus())
        painter->setPen(QPen(QColor(255,255,255,200)));
    else
        painter->setPen(QPen(QColor(100, 100, 100, 100)));
    painter->setBrush(brushColor);
    painter->drawRect(-10, -10, 20, 20);
}

void MyItem::setColor(const QColor &color)
{
    brushColor = color;
}

// 键盘按下事件处理函数，判断是否是向下方向键，如果是，则向下移动图形项
void MyItem::keyPressEvent(QKeyEvent *event)
{
//    if(event->key() == Qt::Key_Down)
//            moveBy(0, 10);
    switch (event->key())
    {
        case Qt::Key_1:
        {
            //模糊效果
            QGraphicsBlurEffect * blurEffect = new QGraphicsBlurEffect;
            blurEffect->setBlurHints(QGraphicsBlurEffect::QualityHint);//设置执行方式
            blurEffect->setBlurRadius(8);//细节等级 默认半径5
            setGraphicsEffect(blurEffect);
            break;
        }
        case Qt::Key_2:
        {
            //染色效果 默认浅蓝QColor(0, 0, 192)
            QGraphicsColorizeEffect *colorizeEffect = new QGraphicsColorizeEffect;
            colorizeEffect->setColor(Qt::white);
            colorizeEffect->setStrength(0.6);//效果强度 0-1.0 默认1.0
            setGraphicsEffect(colorizeEffect);
            break;
        }
        case Qt::Key_3:
        {
            //阴影效果 默认透明的黑灰色QColor(63, 63, 63, 180)
            QGraphicsDropShadowEffect *dropShadowEffect = new QGraphicsDropShadowEffect;
            dropShadowEffect->setColor(QColor(63, 63, 63, 100));
            dropShadowEffect->setBlurRadius(2);//阴影模糊半径 默认1
            dropShadowEffect->setOffset(10);//阴影偏移值 默认右下方8像素
            setGraphicsEffect(dropShadowEffect);
            break;
        }
        case Qt::Key_4:
        {
            //透明效果
            QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
            opacityEffect->setOpacity(0.4);//透明度 0-1 0.0完全透明 1.0完全不透明
            setGraphicsEffect(opacityEffect);
            break;
        }
        case Qt::Key_5:
            graphicsEffect()->setEnabled(false);
            break;
    }
}

// 鼠标按下事件处理函数，设置被点击的图形项获得焦点，并改变光标外观
void MyItem::mousePressEvent(QGraphicsSceneMouseEvent */*event*/)
{
    setFocus();
    setCursor(Qt::ClosedHandCursor);
}

// 悬停事件处理函数，设置光标外观和提示
void MyItem::hoverEnterEvent(QGraphicsSceneHoverEvent */*event*/)
{
    setCursor(Qt::OpenHandCursor);
    setToolTip("I am item");
}

// 右键菜单事件处理函数，为图形项添加一个右键菜单
void MyItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *moveAction = menu.addAction("move back");
    QAction *selectedAction = menu.exec(event->screenPos());
    if(selectedAction == moveAction)
    {
        setPos(0, 0);
    }

}

