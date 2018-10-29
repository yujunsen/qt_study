#include "dialog.h"
#include "widget.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    Dialog dialog;
    if(dialog.exec() == QDialog::Accepted)  //如果是按下了“进入主界面”按钮，则显示主界面
    {
        w.show();
        return a.exec();    //程序正常运行
    }

    return 0;
}
