#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWizard>

namespace Ui {
class Widget;
}

class QErrorMessage;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::Widget *ui;
    QErrorMessage *errording;
    QWizardPage *createPage1();
    QWizardPage *createPage2();
    QWizardPage *createPage3();
};

#endif // WIDGET_H
