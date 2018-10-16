#include "mydialog.h"
#include <QApplication>
#include <QFileDialog>
#include <QDebug>


int main(int argc, char ** argv)
{
    QApplication app(argc,argv);
    MyDialog w;
    w.show();

    return app.exec();
}
