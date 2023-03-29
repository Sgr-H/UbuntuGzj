#include "serialsettingmanager.h"
#include <QDebug>
#include "bridgemanager.h"



SerialSettingManager::SerialSettingManager(QObject *parent) : QObject(parent)
{
    //    SerialSetting *_serial=new SerialSetting();
    //    BridgeManager::instance().serialIns();
    //    connect(_serial,&SerialSetting::sigReply,[this](const quint8 &_serial_port, const QByteArray &_byte_array) {
    //        qDebug()<<_serial_port<<"   "<<_byte_array<<endl;
    //    });
    connect(this,&SerialSettingManager::on_comming_msg,[this](const quint8 &_serial_port, const QByteArray &_byte_array) {
        qDebug()<<_serial_port<<" "<<_byte_array.toHex()<<endl;
    });

}

SerialSettingManager::~SerialSettingManager()
{

}

void SerialSettingManager::test(const QByteArray &_collect_ba, const QByteArray &_byte_array)
{
//    bool ok;
//    quint8 targetId=_collect_ba.at(0);
//    quint8 port =_collect_ba.at(1);
//    QString dataSeg=QString(_collect_ba.mid(2,_collect_ba.size()-3).toHex());
//    QByteArray addr=_collect_ba.right(1);
//    qDebug()<<targetId<<port<<addr<<"  "<<dataSeg<<endl;
//    quint64 tmpDataseg = dataSeg.toULongLong(&ok,16);
//    quint32 tmpremainder = dataSeg.right(4).toUInt(&ok,16);
//    QString dataUpper = QString::number((tmpDataseg + (tmpremainder-1)*65536 - (tmpremainder-1)),16).toUpper();
//    QString dataDowner= QString::number((tmpDataseg - (tmpremainder-1)),16).toUpper();
//    qDebug()<< tmpDataseg<<dataUpper<<" "<<dataDowner<<endl;

//    //查询数据
//    QSqlQuery sql_query(BridgeManager::instance().gzjSqliteINS()->sqlDatabase);
//    QString select_sql = QString("select target_type, collect_instruct, analytic_package, data_base_type,"
//                                 "start_idx, take_count, mutiple, calculation_formula from configuration where "
//                                 "collect_instruct <= '%1' AND collect_instruct >= '%2' ").arg(dataUpper, 10, QLatin1Char('0')).arg(dataDowner, 10, QLatin1Char('0'));
//    if(!sql_query.exec(select_sql))
//    {
//        qDebug()<<sql_query.lastError();
//    }
//    else
//    {
//        while(sql_query.next())
//        {
//            QString tmpTT   = sql_query.value(0).toString();
//            QString tmpCI   = sql_query.value(1).toString();
//            QString tmpAP   = sql_query.value(2).toString();
//            QString tmpDBT  = sql_query.value(3).toString();
//            QString tmpSI   = sql_query.value(4).toString();
//            QString tmpTC   = sql_query.value(5).toString();
//            QString tmpM    = sql_query.value(6).toString();
//            QString tmpCF   = sql_query.value(7).toString();

//            if(!tmpAP.compare("1")){
//                if(!tmpDBT.compare("8")){
//                    QByteArray tmpRDS =  _byte_array.mid(2*(tmpCI.mid(2,4).toInt(&ok,16)-dataDowner.mid(1,4).toInt(&ok,16))+tmpSI.toUInt(&ok,16)-1,tmpTC.toUInt(&ok,10));
//                    if(!tmpCF.compare("00")){
//                        QString tmpvalue = QString::number(tmpRDS.toHex().toUInt(&ok,16)*tmpM.toDouble());
//                        qDebug()<<"tmpTT: "<< tmpTT<<"  tmpValue: "<<tmpvalue<<endl;
//                        BridgeManager::instance().gzjSqliteINS()->insert(addr.toHex().toUInt(&ok,16),tmpTT,tmpvalue,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),"elecMh");

//                    }
//                    else if(!tmpCF.compare("03")){
//                        QString tmpvalue = QString::number(tmpRDS.toHex().toUInt(&ok,16)*tmpM.toDouble());
//                        qDebug()<<"tmpTT: "<< tmpTT<<"  tmpValue: "<<tmpvalue<<endl;
//                        BridgeManager::instance().gzjSqliteINS()->insert(addr.toHex().toUInt(&ok,16),tmpTT,tmpvalue,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),"elecMh");

//                    }
//                    else if(!tmpCF.compare("05")){
//                        QString tmpvalue = QString::number(tmpRDS.toHex().toUInt(&ok,16)*tmpM.toDouble());
//                        qDebug()<<"tmpTT: "<< tmpTT<<"  tmpValue: "<<tmpvalue<<endl;
//                        BridgeManager::instance().gzjSqliteINS()->insert(addr.toHex().toUInt(&ok,16),tmpTT,tmpvalue,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),"elecMh");

//                    }
//                }
//            }
//        }
//    }





    //    bool ok;
    //    bool flag=false;
    //    quint8 basize=_byte_array.size();
    //    if(basize>6){
    //        qDebug()<<basize<<endl;
    //        QString elecAddr = QString("%1").arg(_byte_array.at(0)&0xFF,2,16,QLatin1Char('0'));
    //        //判断该地址是否存在
    //        QByteArray elecAddrSM=BridgeManager::instance().electrityMIns()->getElecAddrArray();
    //        for(quint8 i=0;i<elecAddrSM.size();++i)
    //        {
    //            if(elecAddr.toUShort(&ok,16)==elecAddrSM.at(i))
    //                flag=true;
    //        }
    //        //功能码03
    //        if(_byte_array.at(1)==0x03){
    //            //取电量值
    //            if(_byte_array.at(2)==0x04){
    //                //取电量值转String
    //                QString elecHH = QString("%1").arg(_byte_array[3]&0xFF,2,16,QLatin1Char('0'));
    //                QString elecHL = QString("%1").arg(_byte_array[4]&0xFF,2,16,QLatin1Char('0'));
    //                QString elecLH = QString("%1").arg(_byte_array[5]&0xFF,2,16,QLatin1Char('0'));
    //                QString elecLL = QString("%1").arg(_byte_array[6]&0xFF,2,16,QLatin1Char('0'));
    //                //计算总电量
    //                double elecsum;
    //                elecsum=(elecHH. toUInt(&ok,16)*16777216+elecHL.toUInt(&ok,16)*65536+elecLH.toUInt(&ok,16)*256+elecLL.toUInt(&ok,16))/100.0;
    //                qDebug()<<elecsum;
    //                BridgeManager::instance().electrityMIns()->getElecMeter()[elecAddr.toUInt(&ok,16)].addr=elecAddr.toUInt(&ok,16);
    //                BridgeManager::instance().electrityMIns()->getElecMeter()[elecAddr.toUInt(&ok,16)].elecQ=elecsum;

    //                QSqlQuery sql_query(BridgeManager::instance().gzjSqliteINS()->sqlDatabase);
    //                if(!flag){
    //                    BridgeManager::instance().electrityMIns()->getElecAddrArray().append(elecAddr.toUShort(&ok,16));
    //                    qDebug()<<"elecaddr:"<<elecAddr;
    //                    //插入数据
    //                    QString insert_sql = "insert into elecM values (?, ?, ?)";

    //                    sql_query.prepare(insert_sql);
    //                    sql_query.addBindValue(1);
    //                    sql_query.addBindValue(elecAddr.toInt(&ok,16));
    //                    sql_query.addBindValue(QString("%1").arg(BridgeManager::instance().electrityMIns()->getElecMeter()[elecAddr.toUInt(&ok,16)].elecQ));
    //                    if(!sql_query.exec())
    //                    {
    //                        qDebug() << sql_query.lastError();
    //                    }
    //                    else
    //                    {
    //                        qDebug() << "inserted!";
    //                    }
    //                    BridgeManager::instance().electrityMIns()->getModel()->select();
    //                }
    //                //更新数据
    //                else{
    //                    QString update_sql = "update elecM set elecQ = :elecQ where addr = :addr";
    //                    sql_query.prepare(update_sql);
    //                    sql_query.bindValue(":elecQ", BridgeManager::instance().electrityMIns()->getElecMeter()[elecAddr.toUInt(&ok,16)].elecQ);
    //                    sql_query.bindValue(":addr", elecAddr.toInt(&ok,16));
    //                    if(!sql_query.exec())
    //                    {
    //                        qDebug() << sql_query.lastError();
    //                    }
    //                    else
    //                    {
    //                        qDebug() << "updated!";
    //                    }
    //                    BridgeManager::instance().electrityMIns()->getModel()->select();
    //                }
    //            }
    //        }
    //    }
}
