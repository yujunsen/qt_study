#include "mydialog.h"
#include <QApplication>
#include <QFileDialog>
#include <QDebug>


//RC_ICONS = g2.ico
//配置文件 更改图标

int main(int argc, char ** argv)
{
    QApplication app(argc,argv);
    MyDialog w;
    w.show();

    return app.exec();
}
