#include "widget.h"
#include "ui_widget.h"

#include <QDateTimeEdit>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置时间为现在的时间系统
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    //设置时间显示格式
    ui->dateTimeEdit->setDisplayFormat(tr("yyyy年MM月dd日 ddd HH时 mm分 ss秒"));
    /*
     * 这里使用代码设置了dateTimeEdit中的日期和时间。
     *  简单说明一下：
     *  y表示年；M表示月；d表示日；而ddd表示星期；H表示小时，使用24h制显示，而h也表示小时，
     *  如果最后有AM或者PM的，则是12h制显示，否则使用24h制；
     *  m表示分；s表示秒；还有一个z可以用来表示毫秒。
     *  更多的格式可以参考QDateTime类。现在运行程序查看效果。
     *  还要说明，可以使用该部件的text（）函数获取设置的值，它返回QString类型的字符串；
     *  也可以使用date Time（）函数，它返回的是QDateTime类型数据。
    */
    ui->timeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    ui->spinBox->setValue(20);
}

Widget::~Widget()
{
    delete ui;
}

/*
 * spinBox的属性有：
 *  后缀suffix属性，可以设置为“%”，这样就可以显示百分数了；
 *  前缀prefix属性，比如表示金钱时前面有“￥”字符；
 *  最小值minimum属性，设置其最小值；最大值maximum属性设置其最大值；
 *  单步值singleStep属性设置每次增加的数值，默认为1；value为现在显示的数值。
 *  而doubleSpinBox又增加了一个小数位数decimals属性，用来设置小数点后面的位数。
 * 可以在代码中使用value（）函数来获取设置的数值。
*/
