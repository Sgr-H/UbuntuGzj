#include "bridgemanager.h"
#include <QDebug>
#include <QThread>


BridgeManager::BridgeManager(QObject *parent) :
    QObject(parent)
{
    init();
    UIconnect();

    connect(m_serialSetting,&SerialSetting::sigReply,m_serialSM,&SerialSettingManager::test/*on_comming_msg*/);
    connect(m_tcpClient,&TcpClient::sigReply,m_tcpCM,&tcpClientManager::test);
    connect(m_commonSetting,&CommonSetting::signtest,this,&BridgeManager::slotsTest);
    connect(this,&BridgeManager::signtest,this,&BridgeManager::slotsTest);
    /*串口类收到数据向其他类传递信号*/
    connect(m_serialSM,&SerialSettingManager::process_msg,m_fireP,&FireP::process_fpMsg);
}

BridgeManager::~BridgeManager()
{

}

void BridgeManager::slotsTest()
{
    while(1){
    qDebug()<<"test:"<<QThread::currentThreadId();
    }
}

void BridgeManager::init()
{
    m_gzjSqlite=new GzjSqlite();
    m_serialSetting = new SerialSetting();
    m_electricityMeter =new ElectricityMeter();
    m_tcpClient=new TcpClient();
    m_commonSetting=new CommonSetting();
    m_businessLM=new BusinessLogicManager();
    m_serialSM=new SerialSettingManager();
    m_waterMeter=new WaterMeter();
    m_environment=new Environment();
    m_fireP=new FireP();
    m_waterLever=new WaterLever();
    m_liftManager=new LiftManager();
    m_tcpCM=new tcpClientManager();

    qDebug()<<QThread::currentThreadId();
}

void BridgeManager::UIconnect()
{
    //串口设置界面 ---> 通用设置界面
    connect(m_serialSetting,&SerialSetting::showCommonSettingUI,m_commonSetting,&CommonSetting::show);

    //网络设置界面 ---> 通用设置界面
    connect(m_tcpClient,&TcpClient::showCommonSettingUI,m_commonSetting,&CommonSetting::show);

}

void BridgeManager::test()
{
    qDebug()<<"test:"<<QThread::currentThreadId();

}

BridgeManager& BridgeManager::instance()
{
    static BridgeManager _uniqueInstance(Q_NULLPTR);
    return _uniqueInstance;
}

BusinessLogicManager *BridgeManager::businessLMINS() const
{
    return m_businessLM;
}

SerialSetting* BridgeManager::serialIns()const
{
    return m_serialSetting;
}

ElectricityMeter *BridgeManager::electrityMIns() const
{
    return m_electricityMeter;
}

TcpClient *BridgeManager::tcpCIns() const
{
    return m_tcpClient;
}

CommonSetting *BridgeManager::commonSINS() const
{
    return m_commonSetting;
}

GzjSqlite *BridgeManager::gzjSqliteINS() const
{
    return m_gzjSqlite;
}

SerialSettingManager *BridgeManager::serialSMINS() const
{
    return m_serialSM;
}

WaterMeter *BridgeManager::waterMIns() const
{
    return m_waterMeter;
}

Environment *BridgeManager::environmentMIns() const
{
    return m_environment;
}

FireP *BridgeManager::firePINS() const
{
    return m_fireP;
}

WaterLever *BridgeManager::waterLIns() const
{
    return m_waterLever;
}

LiftManager *BridgeManager::liftMIns() const
{
    return m_liftManager;
}

tcpClientManager *BridgeManager::tcpCMINS() const
{
    return m_tcpCM;
}
