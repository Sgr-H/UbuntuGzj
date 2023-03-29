#ifndef ELECTRICITYMETER_H
#define ELECTRICITYMETER_H

#include <QWidget>
#include <QSqlTableModel>
#include <QModelIndex>
namespace Ui {
class ElectricityMeter;
}

class ElectricityMeter : public QWidget
{
    Q_OBJECT

public:
    //电表结构体
    struct ElecMeter {
        quint8 type;
        quint8 addr;
        double elecQ;

    };
    //变量定义

    quint8 getElecMaxAddr();
    ElecMeter* getElecMeter();
    QSqlTableModel* getModel();
    QByteArray getElecAddrArray();

    explicit ElectricityMeter(QWidget *parent = nullptr);
    ~ElectricityMeter();




signals:
    void showWidgetUI();


private:
    QByteArray elecAddrArray;
    ElecMeter em[256];
    quint8 elecMaxAddr=0;

    QSqlTableModel *model=nullptr;
    Ui::ElectricityMeter *ui;
};

#endif // ELECTRICITYMETER_H
