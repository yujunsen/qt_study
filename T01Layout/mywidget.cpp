#include "mywidget.h"
#include "ui_mywidget.h"

mywidget::mywidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mywidget)
{
    ui->setupUi(this);
}

mywidget::~mywidget()
{
    delete ui;
}
