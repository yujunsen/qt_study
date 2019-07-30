#ifndef WIDGET_H
#define WIDGET_H

#include <QDomDocument>
#include <QWidget>

class QStandardItemModel;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    enum DateTimeType{Time, Date, DateTime};
    QString getDateTime(DateTimeType type);
private slots:

    void on_sellTypeComboBox_currentIndexChanged(const QString &arg1);

    void on_sellBrandCombox_currentIndexChanged(const QString &arg1);

    void on_sellNumSpinBox_valueChanged(int arg1);

    void on_sellCancelBtn_clicked();

    void on_sellOKBtn_clicked();

    void on_managerBtn_clicked();

    void on_chartBtn_clicked();

    void on_typeCombox_currentIndexChanged(const QString &arg1);

    void on_updateBtn_clicked();

private:
    Ui::Widget *ui;
    QDomDocument doc;

    QStandardItemModel *chartModel;

private:
    bool docRead();
    bool docWrite();
    void writeXml();
    void createNodes(QDomElement &date);
    void showDailyList();

    void createChartModelView();
    void showChart();
};

#endif // WIDGET_H
