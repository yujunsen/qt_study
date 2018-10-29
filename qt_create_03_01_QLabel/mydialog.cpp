#include "mydialog.h"
#include "ui_mydialog.h"
#include <QDialog>

MyDialog::MyDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);

    //auto dialog = new QDialog(this);
    //在MyWidget类的构造函数中定义了一个QDialog类对象，
    //还指定了dialog的父窗口为MyWidget类对象（即this参数的作用），
    //最后调用show（）函数让其显示
    //dialog->show();
    //dialog对象指明了父窗口，所以就没有必要使用delete来释放该对象了

    //不用指针
    //QDialog dialog(this);
    //dialog.exec();
    /*
     * MyWidget窗口并没有出来，当关闭对话框后，MyWidget窗口才弹出来。
     * 这个对话框与前面那个对话框的效果不同，称它为模态对话框，
     * 而前面那种对话框称为非模态对话框。
     * 模态对话框就是在没有关闭它之前，不能再与同一个应用程序的其他窗口进行交互，
     *  比如新建项目时弹出的对话框。而对于非模态对话框，既可以与它交互，也可以与
     *  同一程序中的其他窗口交互，
     *  如Microsoft Word中的查找替换对话框。
     * 就像前面看到的，要想使一个对话框成为模态对话框，则只需要调用它的exec（）函数；
     * 而要使其成为非模态对话框，则可以使用new操作来创建，然后使用show（）函数来显示。
     */
     //其实使用show（）函数也可以建立模态对话框，只须在其前面使用setModal（）函数即可。
     // 例如：
     QDialog *dialog = new QDialog(this);
     dialog->setModal(true);
     dialog->show();

    /*
     * 运行程序后可以看到，生成的对话框是模态的。
     * 但是，它与用exec（）函数时的效果是不一样的，因为现在的MyWidget窗口也显示出来了。
     * 这是因为调用完show（）函数后会立即将控制权交给调用者，程序可以继续往下执行。
     * 而调用exec（）函数却不同，只有当对话框被关闭时才会返回。
     * 与setModal（）函数相似的还有一个setWindowModality()
     *  Qt:NonModal（不阻塞任何窗口，就是非模态）、
     *  Qt:：WindowModal（阻塞它的父窗口、所有祖先窗口以及它们的子窗口）或
     *  Qt:：ApplicationModal（阻塞整个应用程序的所有窗口）。
     *  而setModal（）函数默认设置的是Qt:：ApplicationModal。
    */

}

MyDialog::~MyDialog()
{
    delete ui;
}
