#include <QApplication>
#include <QPushButton>
#include <QStateMachine>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QFinalState>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton button("State Machine");
    QPushButton quitButton("Quit");
    // 创建状态机和三个状态，并将三个状态添加到状态机中
    QStateMachine machine;
    QState *s1 = new QState(&machine);
    QState *s11 = new QState(s1);
    QState *s12 = new QState(s1);
    QState *s13 = new QState(s1);
    s1->setInitialState(s11);
    s11->assignProperty(&button, "geometry", QRect(100, 100, 120, 50));
    s12->assignProperty(&button, "geometry", QRect(300, 100, 120, 50));
    s13->assignProperty(&button, "geometry", QRect(200, 200, 120, 50));
    // 使用按钮部件的单击信号来完成三个状态的切换
   QSignalTransition *transition1 = s11->addTransition(&button, &QPushButton::clicked, s12);
   QSignalTransition *transition2 = s12->addTransition(&button, &QPushButton::clicked, s13);
   QSignalTransition *transition3 = s13->addTransition(&button, &QPushButton::clicked, s11);

   s12->addTransition(&quitButton, &QPushButton::clicked, s12);


    QPropertyAnimation *animation = new QPropertyAnimation(&button, "geometry");
    transition1->addAnimation(animation);
    transition2->addAnimation(animation);
    transition3->addAnimation(animation);
    QObject::connect(s13, &QState::entered, &button, &QPushButton::showMinimized);

    QFinalState *s2 = new QFinalState(&machine);
    s1->addTransition(&quitButton, &QPushButton::clicked, s2);
    QObject::connect(&machine, &QStateMachine::finished, qApp, &QApplication::quit);

    // 设置状态机的初始状态并启动状态机
    machine.setInitialState(s1);
    machine.start();
    button.show();
    quitButton.move(300, 300);
    quitButton.show();

    return app.exec();
}
