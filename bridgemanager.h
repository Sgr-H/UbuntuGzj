#ifndef BRIDGEMANAGER_H
#define BRIDGEMANAGER_H

#include <QObject>
#include "serialsetting.h"
#include "electricitymeter.h"
#include "tcpclient.h"
#include "tcpclientmanager.h"
#include "commonsetting.h"
#include "gzjsqlite.h"
#include "businesslogicmanager.h"
#include "serialsettingmanager.h"
#include "watermeter.h"
#include "environment.h"
#include "firep.h"
#include "waterlever.h"
#include "liftmanager.h"
#include <QDateTime>


class BridgeManager : public QObject
{
    Q_OBJECT

public:
    static BridgeManager& instance();

    // 得到 实例
    BusinessLogicManager* businessLMINS()const;
    SerialSetting* serialIns()const;
    ElectricityMeter* electrityMIns()const;
    TcpClient* tcpCIns()const;
    CommonSetting* commonSINS()const;
    GzjSqlite* gzjSqliteINS()const;
    SerialSettingManager* serialSMINS()const;
    WaterMeter* waterMIns()const;
    Environment* environmentMIns()const;
    FireP *firePINS()const;
    WaterLever *waterLIns()const;
    LiftManager *liftMIns()const;
    tcpClientManager* tcpCMINS()const;

    void test();


    explicit BridgeManager(QObject *parent=nullptr);
    ~BridgeManager();
signals:
    void signtest();
private slots:
    void slotsTest();
private:
    //变量
    SerialSettingManager *m_serialSM=nullptr;
    BusinessLogicManager *m_businessLM=nullptr;
    GzjSqlite *m_gzjSqlite=nullptr;
    CommonSetting *m_commonSetting=nullptr;
    ElectricityMeter *m_electricityMeter=nullptr;
    SerialSetting *m_serialSetting = nullptr;
    TcpClient *m_tcpClient=nullptr;
    WaterMeter *m_waterMeter=nullptr;
    Environment *m_environment=nullptr;
    FireP *m_fireP=nullptr;
    WaterLever *m_waterLever=nullptr;
    LiftManager *m_liftManager=nullptr;
    tcpClientManager *m_tcpCM=nullptr;

    //函数
    void init();
    void UIconnect();
};

#endif // BRIDGEMANAGER_H
