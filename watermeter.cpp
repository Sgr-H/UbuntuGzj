#include "watermeter.h"
#include "ui_watermeter.h"
#include "gzjsqlite.h"
#include "QScroller"
#include "bridgemanager.h"
quint8 WaterMeter::getWaterMaxAddr()
{
    return waterMaxAddr;
}

QSqlTableModel *WaterMeter::getModel()
{
    return model;
}

void WaterMeter::modelSelect()
{
    model->select();
}

WaterMeter::WaterMeter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaterMeter)
{
    ui->setupUi(this);

    QSqlQuery sql_query;
    QString select_sql = "select id ,addr from waterM";
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
            waterAddrArray[waterMaxAddr++]=addr.toUInt(&ok,10);
            qDebug()<<addr.toUInt(&ok,10) <<"\t waterAddrArray: "<<waterAddrArray[waterMaxAddr-1]<<endl;
        }
    }


    QSqlDatabase sqlDatabase = QSqlDatabase::database("qt_sql_default_connection");
    //规定格式
    model = new QSqlTableModel(this, sqlDatabase);
    //    model->setTable("waterM");
//    model->setTable("elecMh");
//    model->setTable("configuration");
    model->setTable("deviceInfo");

    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
//    model->setHeaderData(model->fieldIndex("id"),
//                         Qt::Horizontal, tr("编号"));
//    model->setHeaderData(model->fieldIndex("addr"),
//                         Qt::Horizontal, tr("地址"));
//    model->setHeaderData(model->fieldIndex("waterQ"),
//                         Qt::Horizontal, tr("用水量"));

    //        if(tableNameList.count()!=0)
    ui->watertableView->setModel(model);


    connect(ui->waterReturnButton,&QPushButton::clicked,this,[=]{
        this->hide();
        emit showWidgetUI();
    });

    //刷新

    connect(ui->waterTestButton,&QPushButton::clicked,this,[=]{
        BridgeManager::instance().serialIns()->collectTimerctl(0);
        modelSelect();
    });
    //启动循环采集定时器;
    connect(ui->waterAdvanceButton,&QPushButton::clicked,this,[=]{
        BridgeManager::instance().serialIns()->collectTimerctl(5000);
        modelSelect();
    });

    //滑动
    QScroller *scl = QScroller::scroller(ui->watertableView);
    scl->grabGesture(ui->watertableView,QScroller::LeftMouseButtonGesture);
    ui->watertableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
//    QScrollerProperties properties = scl->scrollerProperties();
//    properties.setScrollMetric(QScrollerProperties::DragVelocitySmoothingFactor,0.1);//滑动
//    properties.setScrollMetric(QScrollerProperties::FrameRate,QScrollerProperties::Fps60);
//    properties.setScrollMetric(QScrollerProperties::SnapTime,0.1);//设置滚动曲线的时间因子。设置滚动的时长,值越小，滚动时间越长
//    properties.setScrollMetric(QScrollerProperties::MaximumVelocity,0.1);//设置自动滚动能达到得最大速度，m/s
//    scl->setScrollerProperties(properties);

}

WaterMeter::~WaterMeter()
{
    delete ui;
}
