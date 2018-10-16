#include "mywidget.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
mywidget::mywidget(QWidget *parent):QWidget(parent)
{
#if 0
    QLineEdit * edit1 = new QLineEdit();
    QLineEdit * edit2 = new QLineEdit();
    QLineEdit * edit3 = new QLineEdit();
    QHBoxLayout * Hlayout = new QHBoxLayout();//竖直  控件向下添加
    auto Vlayout = new QVBoxLayout();//平行 控件列向右添加
    auto Glayout = new QGridLayout();
    Hlayout->addWidget(edit1,1);
    Vlayout->addWidget(edit2,2);
    Vlayout->addWidget(edit3,3);
    Glayout->addLayout(Hlayout, 1, 1);
    //添加空间    QLayout *, int row, int column, int rowSpan
    //Glayout->addLayout(Vlayout, 1, 2);
    //edit1->setText("dasd");
    // Glayout->addWidget(edit1);
    //Glayout->addWidget(edit2);
    this->setLayout(Glayout);
#endif
    QLineEdit *edit1 = new QLineEdit();
    QLineEdit *edit2 = new QLineEdit();
    QLineEdit *edit3 = new QLineEdit();

    QHBoxLayout *layout = new QHBoxLayout();
    QVBoxLayout *Vlayout = new QVBoxLayout();
    QGridLayout *Glayout = new QGridLayout();

    //this->setLayout(layout);
    layout->addWidget(edit1, 1);
    edit1->setMinimumWidth(50);//设置最小宽度
    layout->addWidget(edit2, 2);
    edit2->setMinimumWidth(100);
    layout->addWidget(edit3, 3);
    edit3->setMinimumWidth(150);
    layout->addStretch(1);  //留下layout比例大小的空白 分配布局大小比例
    //函数的作用是在布局器中增加一个伸缩量，里面的参数表示QSpacerItem的个数，默认值为零，会将你放在layout中的空间压缩成默认的大小。
    //layout
    Vlayout->addLayout(layout);
    //Vlayout->addStretch(1);
    Glayout->addLayout(Vlayout, 1, 1);
    Glayout->setColumnStretch(1, 1);
    Glayout->setRowStretch(2, 1);
    this->setLayout(Glayout);
}
