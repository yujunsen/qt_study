#include <QApplication>
#include <QPropertyAnimation>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPushButton button("Animated Button");
    button.show();
    QPropertyAnimation animation(&button, "geometry");
    animation.setDuration(1000);
//    animation.setStartValue(QRect(0, 0, 120, 30));
//    animation.setEndValue(QRect(250, 250, 200, 60));
    animation.setKeyValueAt(0, QRect(0, 0, 120, 30));
    animation.setKeyValueAt(0.8, QRect(250, 250, 200, 60));
    animation.setKeyValueAt(1, QRect(0, 0, 120, 30));
    return  app.exec();
}
