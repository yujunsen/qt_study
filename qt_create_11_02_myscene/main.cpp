#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "myitem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    MyItem *item = new MyItem;
    scene.addItem(item);

    QGraphicsView view(&scene);
    scene.setForegroundBrush(QColor(255, 255, 0, 100));
    scene.setBackgroundBrush(QPixmap("://background.png"));

    view.resize(400, 300);
    view.show();

    QGraphicsView view2(&scene);
    view2.resize(400, 300);
    view2.show();


    return a.exec();
}
