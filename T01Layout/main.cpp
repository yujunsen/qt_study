#include "mywidget.h"
#include <QApplication>

class myqweight : public QWidget
{
    Q_OBJECT
public:
    myqweight()
    {

    }
    ~myqweight()
    {

    }
private:

};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mywidget w;
    w.show();

    return a.exec();
}
