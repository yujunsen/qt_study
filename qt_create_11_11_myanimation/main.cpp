#include <QApplication>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPushButton button("Animated Button");
    button.show();
    //按钮部件1动画
    QPropertyAnimation *animation1 = new QPropertyAnimation(&button, "geometry");//获取geometry属性
    animation1->setDuration(2000);
    animation1->setStartValue(QRect(250, 0, 120, 30));
    animation1->setEndValue(QRect(250, 300, 120, 30));
    animation1->setEasingCurve(QEasingCurve::OutBounce);//缓和曲线
    //按钮部件2动画
    QPropertyAnimation* animation2 = new QPropertyAnimation(&button, "geometry");
    animation2->setDuration(1000);
    animation2->setStartValue(QRect(400, 300, 120, 30));
    animation2->setEndValue(QRect(400, 300, 200, 60));
    //串行动画组
    QSequentialAnimationGroup group;
    //QParallelAnimationGroup group;//并行动画组
    group.addAnimation(animation1);
    group.addAnimation(animation2);
    group.start();

    return  app.exec();
}
