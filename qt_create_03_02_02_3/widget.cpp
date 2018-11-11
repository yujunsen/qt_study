#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QColorDialog>
#include <QErrorMessage>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    this->setWindowTitle("Widget");
    ui->setupUi(this);
    errording = new QErrorMessage(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    //QColor color = QColorDialog::getColor(Qt::red, this, tr("颜色对话") ,QColorDialog::ShowAlphaChannel);
    //qDebug() << "color " << color ;
    /*
     * 这里使用了QColorDialog的静态函数getColor（）来获取颜色，
     *  它的3个参数的作用分别是：
     *      设置初始颜色、
     *      指定父窗口和
     *      设置对话框标题。
     * 这里的Qt:：red是Qt预定义的颜色对象，
     *  可以直接单击该字符串，然后按下F1查看其快捷帮助，或者在帮助索引中通过Qt:：GlobalColor关键字，
     *  从而查看到所有的预定义颜色列表。getColor（）函数返回一个QColor类型数据。
     * 这里的4个数值分别代表透明度（alpha）、红色（red）、绿色（green）和蓝色（blue）。
     * 它们的数值都是从0.0~1.0，有效数字为6位。
     * 对于alpha来说，1.0表示完全不透明，这是默认值，而0.0表示完全透明。
     * 对于三基色红、绿、蓝的数值，还可以使用0~255来表示，
     * 颜色对话框中就是使用这种方法。
     *      其中，0表示颜色最浅，255表示颜色最深。在0~255与0.0～1.0之间可以通过简单的数学运算来对应，
     *      其中0对应0.0，255对应1.0。在颜色对话框中还可以添加对alpha的设置，
     * 就是在getColor（）函数中再使用最后一个参数：
     *      QColorDialog:：ShowAlphaChannel用来显示alpha设置
    */
    QColorDialog dialog(Qt::red, this);//创建对象、
    dialog.setOption(QColorDialog::ShowAlphaChannel);//显示aplha选项
    dialog.exec();    //模态方式运行对话框
    QColor color = dialog.currentColor();//获取当前颜色
    qDebug() << color;      //输出颜色信息
    //这样的代码与前面的实现效果是等效的。
}

#include <QFileDialog>

void Widget::on_pushButton_2_clicked()
{
    // QString fileName =  QFileDialog::getOpenFileName(this, //父窗口
    //                                                 tr("文件对话"),//对话框标题
    //                                                 "D:/", //默认打开路径
    //
    //tr("图片文件(* png * jpg);;文本类型(*.txt)"));//文件过滤器
    QStringList fileName = QFileDialog::getOpenFileNames(this, tr("文件对话"), "D:/", tr("图片文件(* png * jpg);;文本类型(*.txt)"));
    /*
     * 这里使用了QFileDialog类中的getOpenFileName（）函数来获取选择的文件名，
     * 这个函数会以模态方式运行一个文件对话框。
     * 打开后选择一个文件，单击“打开”按钮后，这个函数便可以返回选择的文件的文件名。
     * 它的4个参数的作用分别是：指定父窗口、设置对话框标题、指定默认打开的目录路径和设置文件类型过滤器。
     * 如果不指定文件过滤器，则默认选择所有类型的文件。
     * 这里指定了只选择png和jpg两种格式的图片文件
     * （注意，代码中*png和*jpg之间需要一个空格），
     * 那么在打开的文件对话框中只能显示目录下这两种格式的文件。
     * 还可以设置多个不同类别的过滤器，
     * 不同类别间使用两个分号“；；”隔开，例如，添加文本文件类型：
     * 图片文件(*.png *.jpg)空格变;了 图片文件（*；png；*jpg）
     * 前面这个程序只能选择单个文件，要同时选择多个文件，则可以使用getOpenFileNames（）函数
    */
    qDebug() << fileName;
    /*
     * 运行程序就可以同时选择多个图片文件了，多个文件名存放在QStringList类型变量中。
     * 当然也可以不使用这些静态函数，而是建立对话框对象来操作。
     * 除了上面的两个函数外，QFileDialog类还提供了getSaveFileName（）
     * 函数来实现保存文件对话框和文件另存为对话框，
     * 还有getExistingDirectory（）函数来获取一个已存在的文件夹路径。
     * 因为它们的用法与上面的例子类似，这里就不再举例。
    */
}

#include <QFontDialog>

void Widget::on_pushButton_3_clicked()
{
    //ok用于标记是否单击ok按钮
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok) ui->pushButton_3->setFont(font);
    else qDebug() << tr("没有选择字体");
    /*
     * 这里使用了QFileDialog类的getFont（）静态函数来获取选择的字体。
     * 这个函数的第一个参数是bool类型变量，用来存放按下的按钮状态，
     *  比如在打开的字体对话框中单击了OK按钮，那么这里的ok就为true，
     * 这样来告诉程序已经选择了字体。
    */
}


#include <QInputDialog>
void Widget::on_pushButton_4_clicked()
{
    bool ok;
    //获取字符串
    QString string = QInputDialog::getText(this, tr("输入字符串对话框"), tr("请输入用户名"), QLineEdit::Normal,
                                           tr("admin"), &ok);
    if(ok) qDebug() << "string:" << string;
    //获取整数
    int value1 = QInputDialog::getInt(this,tr("输入整数对话"),
                                      tr("please input-1000 to 1000 number"), 100, -1000,
                                      1000, 10, &ok);
    if(ok) qDebug() << "value1:" << value1;
    //获取浮点型
    double value2 = QInputDialog::getDouble(this, tr("输入浮点型对话框"), tr("please input-1000 to 1000 number"),
                                            0.00, -1000, 1000, 2, &ok);
    if(ok) qDebug() << "value2:" << value2;
    QStringList items;
    items << tr("条目1") << tr("条目2");
    //获取条目
    QString item = QInputDialog::getItem(this,tr("输入条目对话"),tr("请选择或输入一个条"), items, 0, true, &ok);
    if(ok) qDebug() << "item:" << item;
    /*
     * 这里一共创建了4个不同类型的输入对话框。
     * getText（）函数可以提供一个可输入字符串的对话框，
     *  各参数的作用分别是：
     *      指定父窗口、
     *      设置窗口标题、
     *      设置对话框中的标签显示文本、
     *      设置输入字符串的显示模式（例如密码可以显示成小黑点，这里选择了显示用户输入的实际内容）、
     *      设置输入框中的默认字符串和设置获取按下按钮信息的bool变量；
     * getInt（）函数可以提供一个输入整型数值的对话框，
     *      其中的参数100表示默认的数值是100，
     *      一1000表示可输入的最小值是一1000，
     *      1000表示可输入的最大值是1000，
     *      10表示使用箭头按钮，数值每次变化10；
     * getDouble（）函数可以提供一个输入浮点型数值的对话框，
     *      其中的参数2表示小数的位数为2；
     * getltem（）函数提供一个可以输入一个条目的对话框，需要先给它提供一些条目，
     *  例如这里定义的QStringList类型的items，
     *  其中参数0表示默认显示列表中的第0个条目（0就是第一个），
     *  参数true设置条目是否可以被更改，true就是可以被更改。
     *  这里使用了静态函数，不过也可以自己定义对象，然后使用相关的函数进行设置。
    */
}

#include<QMessageBox>

void Widget::on_pushButton_5_clicked()
{
    //问题对话框
    int ret = QMessageBox::question(this,tr("问题对话"),tr("你了解qt?"),
                                    QMessageBox::Yes, QMessageBox::No);
    if(ret == QMessageBox::Yes) qDebug() << tr("问题");
    //提示对话框
    ret = QMessageBox::information(this, tr("提示对话"),tr("这是书上代码"), QMessageBox::Yes);
    if(ret == QMessageBox::Yes) qDebug() << tr("提示");
    //警告对话
    ret = QMessageBox::warning(this, tr("警告对话"), tr("不能提前结束"), QMessageBox::Abort);
    if(ret == QMessageBox::Abort) qDebug() << tr("警告");
    //错误对话
    ret = QMessageBox::critical(this, tr("错误对话"), tr("发现严重错误！关闭所有文件！"), QMessageBox::YesAll);
    if(ret == QMessageBox::YesAll) qDebug() << tr("错误");
    //关于对话
    QMessageBox::about(this,tr("关于对话"),tr("学习"));

    /*
     * 这里创建了4个不同类型的消息对话框，分别拥有不同的图标还有提示音（这个是操作系统设置的），
     *  几个参数分别用于
     *  设置父窗口、标题栏、显示信息和拥有的按钮。
     *  这里使用的按钮都是QMessageBox类提供的标准按钮。
     *  这几个静态函数的返回值就是那些标准按钮，由QMessageBox:：StandardButton枚举类型指定，
     *  可以使用返回值来判断用户按下了哪个按钮。
     *  about（）函数没有返回值，因为它默认只有一个按钮，与其相似的还有一个aboutQt（）函数，
     *  用来显示现在使用的Qt版本等信息。如果想使用自定义的图标和按钮，
     *  那么可以创建QMessageBox类对象，然后使用相关函数进行操作。
    */

}

#include <QProgressDialog>

//进度对话框
void Widget::on_pushButton_8_clicked()
{
    QProgressDialog dialog(tr("文件复制进度"), tr("取消"), 0, 50000, this);
    dialog.setWindowTitle("进度对话");  //设置窗口标题
    dialog.setWindowModality(Qt::WindowModal);  //将对话框设置为模态
    dialog.show();
    for(int i = 0; i < 50000; i++)              //演示复制进度
    {
        dialog.setValue(i);                     //设置进度条的当前值
        QCoreApplication::processEvents();      //避免界面冻结
        if(dialog.wasCanceled()) break;         //按下取消中断
    }
    dialog.setValue(50000);                     //这样才能显示100%，因为for循环中少加了一个数
    qDebug() << tr("复制结束");
    /*
     * 这里首先创建了一个QProgressDialog类对象dialog，
     *  构造函数的参数分别用于设置对话框的标签内容、取消按钮的显示文本、最小值、最大值和父窗口。
     *  然后将对话框设置为模态并进行显示。
     *  for（）循环语句模拟了文件复制过程，setValue（）函数使进度条向前推进；
     *  为了避免长时间操作而使用户界面冻结，必须不断地调用QCoreApplication类的静态函数processEvents（），
     *  可以将它放在for（）循环语句中。使用QProgressDialog的wasCanceled（）函数来判断用户是否按下了“取消”按钮，
     *  如果是，则中断复制过程。这里使用了模态对话框，QProgressDialog还可以实现非模态对话框，不过它需要定时器等的帮助。
    */
}


//错误信息对话框
void Widget::on_pushButton_7_clicked()
{
    errording->setWindowTitle(tr("错误消息对话"));
    errording->showMessage(tr("这是出错消息"));
    /*
     * 这里首先新建了一个QErrorMessage对话框，并且调用它的showMessage（）函数来显示错误信息，
     * 调用这个函数时对话框会以非模态的形式显示出来。错误信息对话框中默认有一个Show this message again复选框，
     * 可以选择以后是否还要显示相同错误信息；为了这个复选框的功能有效，不能像前面几个例子一样在槽中直接创建对话框。
    */

}

QWizardPage *Widget::createPage1()//向导页面1
{
    QWizardPage *page = new QWizardPage;
    page->setWindowTitle(tr("介绍"));
    return page;
}
QWizardPage *Widget::createPage2()//向导页面2
{
    QWizardPage *page = new QWizardPage;
    page->setWindowTitle(tr("用户选择信息"));
    return page;
}
QWizardPage *Widget::createPage3()//向导页面3
{
    QWizardPage *page = new QWizardPage;
    page->setWindowTitle(tr("结束"));
    return page;
}

void Widget::on_pushButton_6_clicked()
{
    QWizard wizard(this);
    wizard.setWindowTitle(tr("向导对话"));
    wizard.addPage(createPage1());
    wizard.addPage(createPage2());
    wizard.addPage(createPage3());
    wizard.exec();
    /*
     * 这里新建了QWizard类对象，然后使用addPage（）函数为其添加了3个页面。
     * 这里的参数是QWizardPage类型的指针，可以直接调用生成向导页面函数。
     * 运行程序可以看到，向导页面出现的顺序和添加向导页面的顺序是一致的。
     * 上面程序中的向导页面是线性的，而且什么内容也没有添加。
     * 如果想设计自己的向导页面，或添加图片、自定义按钮，或设置向导页面顺序等，那么就需要再多了解一下
    */
}
