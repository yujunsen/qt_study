#include "widget.h"
#include <QApplication>

#include "connection.h"
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 必须在创建数据库之前使用，不然无法在数据库中使用中文
    //QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    if(!createConnection() || !createXml()) return 0;

    Widget w;
    LoginDialog dlg;
    if(dlg.exec() == QDialog::Accepted)
        w.show();
    else
        return 0;

    return a.exec();
}
