#include "mywidget1.h"
#include "ui_mywidget1.h"

MyWidget1::MyWidget1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget1)
{
    ui->setupUi(this);
}

MyWidget1::~MyWidget1()
{
    delete ui;
}
