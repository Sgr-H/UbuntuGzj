#ifndef WATERMETER_H
#define WATERMETER_H

#include <QWidget>
#include <QSqlTableModel>
#include <QModelIndex>

namespace Ui {
class WaterMeter;
}

class WaterMeter : public QWidget
{
    Q_OBJECT

public:
    quint8 getWaterMaxAddr();
    QSqlTableModel* getModel();
    void modelSelect();

    explicit WaterMeter(QWidget *parent = nullptr);
    ~WaterMeter();
signals:
    void showWidgetUI();
private:
    QByteArray waterAddrArray;
    quint8 waterMaxAddr=0;


    QSqlTableModel *model=nullptr;

    Ui::WaterMeter *ui;
};

#endif // WATERMETER_H
