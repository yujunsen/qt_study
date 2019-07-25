#include <QApplication>
#include <QPropertyAnimation>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPushButton button("Animated Button");
    button.show();
    QPropertyAnimation animation(&button, "geometry");//获取geometry属性
    animation.setDuration(10000);   //动画的持续时间 10s
//    animation.setStartValue(QRect(0, 0, 120, 30));  //设置开始的geometry
//    animation.setEndValue(QRect(250, 250, 200, 60));//设置结束的geometry

    animation.setKeyValueAt(0, QRect(0, 0, 120, 30));
    animation.setKeyValueAt(0.8, QRect(250, 250, 200, 60));//8s 边城QRect
    animation.setKeyValueAt(1, QRect(0, 0, 120, 30));   //2s 变回原样
/*动画中间设值
 * setKeyValueAt(qreal step, const QVariant &value)
 * step 0.0-1.0 0.0开始位置 1.0结束位置
*/
    animation.start();
    return  app.exec();
}
