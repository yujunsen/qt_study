#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QIntValidator>
#include <QRegExp>
#include <QCompleter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //新建验证器，指定范围为100-999
    //QValidator * validator = new QIntValidator(100, 999, this);
    //正则表达式
    QRegExp rx("-? \\d{1,3}");
    QValidator *validator = new QRegExpValidator(rx, this);
    //在行编辑器中使用验证器
    ui->lineEdit3->setValidator(validator);

    //4 自动补全
    /*
     * QLineEdit中也提供了强大的自动补全功能，这是利用QCompleter类实现的。
    */
    QStringList wordlist;
    wordlist <<"Qt" <<"Qt Creater" << tr("你好");
    QCompleter *completer = new QCompleter(wordlist, this); //新建自动完成器
    completer->setCaseSensitivity(Qt::CaseInsensitive);     //设置大小写不敏感
    ui->lineEdit4->setCompleter(completer);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_lineEdit2_returnPressed()
{
    ui->lineEdit3->setFocus();                  //让lineEidt3获得焦点
    qDebug() << ui->lineEdit2->text();          //输出1ineEdit2的内容
    qDebug() << ui->lineEdit2->displayText();   //输出lineEdit2显示内容

}

/*
 * 字符（必须输入）    |    字符（可留空）    |    含义
 * A                |       a           |   只能输入A~Z，a～z
 * N                |       n           |   只能输入A~Z，a~z，0～9
 * X                |       x           |   可以输入任意字符
 * 9                |       0           |   只能输入0～9
 * D                |       d           |   只能输入1～9
 *                  |       #           |   只能输入加号（+），减号（一），0～9
 * H                |       h           |   只能输入十六进制字符，A~F，a~f，0～9
 * B                |       b           |   只能输入二进制字符，0或1
 * >                                    |   后面的字母字符自动转换为大写
 * <                                    |   后面的字母字符自动转换为小写
 * !                                    |   停止字母字符的大小写转换
 * \                                    |   将该表中的特殊字符正常显示用作分隔符
 *lineEdit2的inputMask属性设置为“>AA-90-bb-！aa\#H；*”，
 *  其含义为：
 *  “>”号表明后面输入的字母自动转为大写；
 *  “AA”表明开始必须输人两个字母，因为有前面的“>”号的作用，所以输入的这两个字母会自动变为大写；
 *  “一”号为分隔符，直接显示，该位不可输入；
 *  “9”表示必须输入一个数字；
 *  “0”表示输入一个数字，或者留空；
 *  “bb”表示这两位可以留空，或者输入两个二进制字符，即0或1；
 *  “！”表明停止大小写转换，就是在最开始的“>”号不再起作用；
 *  “aa”表示可以留空，或者输入两个字母；“\#”表示将“#”号作为分隔符，因为“#”号在这里有特殊含义，所以前面要加上“\”号；
 *  “H”表明必须输入一个十六进制的字符；
 *  “；*”表示用“*”号来填充空格。
 *  另外，也可以使用setInputMask（）函数在代码中来设置输入掩码。
*/

void Widget::on_lineEdit3_returnPressed()
{
    qDebug() << ui->lineEdit3->displayText();
}
