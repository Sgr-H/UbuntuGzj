#include "electricitymeter.h"
#include "ui_electricitymeter.h"
#include "gzjsqlite.h"

quint8 ElectricityMeter::getElecMaxAddr()
{
    return elecMaxAddr;
}

ElectricityMeter::ElecMeter *ElectricityMeter::getElecMeter()
{
    return em;
}

QSqlTableModel *ElectricityMeter::getModel()
{
    return model;
}

QByteArray ElectricityMeter::getElecAddrArray()
{
    return elecAddrArray;
}

ElectricityMeter::ElectricityMeter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElectricityMeter)
{
    ui->setupUi(this);

    QSqlQuery sql_query;
    QString select_sql = "select id ,addr,elecQ from elecM";
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();

    }
    else
    {
        bool ok;
        while(sql_query.next())
        {

            QString addr = sql_query.value(1).toString();
            em[addr.toUInt(&ok,10)].elecQ=sql_query.value(2).toDouble();
//            qDebug()<<em[addr.toUInt(&ok,10)].elecQ<<endl;
            elecAddrArray[elecMaxAddr++]=addr.toUInt(&ok,10);
            qDebug()<<addr.toUInt(&ok,10) <<"\t elecAddrArray: "<<elecAddrArray[elecMaxAddr-1]<<endl;
        }
    }

    QSqlDatabase sqlDatabase = QSqlDatabase::database("qt_sql_default_connection");
    //规定格式
    model = new QSqlTableModel(this, sqlDatabase);
    model->setTable("elecM");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(model->fieldIndex("id"),
                         Qt::Horizontal, tr("编号"));
    model->setHeaderData(model->fieldIndex("addr"),
                         Qt::Horizontal, tr("地址"));
    model->setHeaderData(model->fieldIndex("elecQ"),
                         Qt::Horizontal, tr("电量"));

    model->setHeaderData(model->fieldIndex("IA"),
                         Qt::Horizontal, tr("A电流"));
    model->setHeaderData(model->fieldIndex("IB"),
                         Qt::Horizontal, tr("B电流"));
    model->setHeaderData(model->fieldIndex("IC"),
                         Qt::Horizontal, tr("C电流"));

    model->setHeaderData(model->fieldIndex("VA"),
                         Qt::Horizontal, tr("A相电压"));
    model->setHeaderData(model->fieldIndex("VB"),
                         Qt::Horizontal, tr("B相电压"));
    model->setHeaderData(model->fieldIndex("VC"),
                         Qt::Horizontal, tr("C相电压"));

    model->setHeaderData(model->fieldIndex("VAB"),
                         Qt::Horizontal, tr("AB线电压"));
    model->setHeaderData(model->fieldIndex("VBC"),
                         Qt::Horizontal, tr("BC线电压"));
    model->setHeaderData(model->fieldIndex("VAC"),
                         Qt::Horizontal, tr("AC线电压"));

    model->setHeaderData(model->fieldIndex("TotalP"),
                         Qt::Horizontal, tr("正向有功总功率"));

    //        if(tableNameList.count()!=0)
    ui->electableView->setModel(model);


    connect(ui->elecReturnButton,&QPushButton::clicked,this,[=]{
        this->hide();
        emit showWidgetUI();
    });
}

ElectricityMeter::~ElectricityMeter()
{
    delete ui;
}
