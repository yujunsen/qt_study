#include <QApplication>
#include <QGraphicsScene>
#include <QTime>
#include <QTimer>

#include "myitem.h"
#include "myview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(static_cast<uint>(QTime(0, 0, 0).secsTo(QTime::currentTime())));
    QGraphicsScene scene;
    scene.setSceneRect(-200, -150, 400, 300);
    for(int i = 0; i < 5; ++i)
    {
        MyItem * item = new MyItem;
        item->setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
        item->setPos(i * 50 - 90, -50);
        scene.addItem(item);
    }
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(300);

    MyView view;
    view.setScene(&scene);
    view.setBackgroundBrush(QPixmap("://background.png"));
    view.show();


    return a.exec();
}
