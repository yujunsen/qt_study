#include "mydialog.h"
#include "ui_mydialog.h"

#include <QFileDialog>
#include <QDebug>
#include <QLabel>

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
#if 0
    QString strFilename = QFileDialog::getSaveFileName(nullptr, "Select file for save", _strDir, "pic file (*.png *.jpg)");
    //null open in Explorer file
    if(strFilename.isEmpty())
    {
        qDebug() << "select none";
        return ;
    }

    qDebug() << strFilename;
    QFileInfo fileInfo(strFilename);
    _strDir = fileInfo.filePath();
    qDebug() << _strDir;
#endif

    auto label = new QLabel(this);
    label->setText(QObject::tr("调用QObject::tr 显示中文"));
    label->resize(480, 300);//设置大小
    //label->move(120, 120);  //改变位置
    this->setWindowTitle(QObject::tr("dd"));//更改标题

    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    //delete ui;
}
