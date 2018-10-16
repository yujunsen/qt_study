#include "mydialog.h"
#include "ui_mydialog.h"

#include <QFileDialog>
#include <QDebug>


MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent)//,
    //ui(new Ui::MyDialog)
{
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
    //ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    //delete ui;
}
