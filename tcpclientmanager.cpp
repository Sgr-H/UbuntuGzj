#include "tcpclientmanager.h"
#include <QDebug>
#include "bridgemanager.h"
tcpClientManager::tcpClientManager(QObject *parent) : QObject(parent)
{

}

tcpClientManager::~tcpClientManager()
{

}

void tcpClientManager::test(const QString &_string_context)
{
    QStringList cmdList = _string_context.split(";");
    int iSize = cmdList.size();
    QString tmpsCmd=NULL;
    bool ok;
    if(cmdList.at(0)=="5758AAA1"&&cmdList.at(iSize-1)=="475A4A1234BBDD"){
        //清表清自增configuration
        QSqlQuery sql_deleteC(BridgeManager::instance().gzjSqliteINS()->sqlDatabase);
        QString query_sql = "delete from configuration";
        sql_deleteC.prepare(query_sql);
        if(!sql_deleteC.exec()){
            qDebug()<<sql_deleteC.lastError();
        }
        query_sql = "update sqlite_sequence SET seq = 0 where name ='configuration'";
        sql_deleteC.prepare(query_sql);
        if(!sql_deleteC.exec()){
            qDebug()<<sql_deleteC.lastError();
        }

        for (int i=1; i<iSize-1;i++)
        {
            QString s = cmdList.at(i);
            QStringList sCmdList=s.split(",");
            if(sCmdList.size()>=13){
                tmpsCmd=sCmdList.at(0);quint16 model_Id=tmpsCmd.toUInt(&ok,10);
                QString target_Type=sCmdList.at(1);
                tmpsCmd=sCmdList.at(2);quint16 protocol=tmpsCmd.toUInt(&ok,10);
                QString collect_Instruct=sCmdList.at(3);
                tmpsCmd=sCmdList.at(4);quint16 analytic_Package=tmpsCmd.toUInt(&ok,10);
                tmpsCmd=sCmdList.at(5);quint16 read_base=tmpsCmd.toUInt(&ok,10);
                tmpsCmd=sCmdList.at(6);quint16 parse_base=tmpsCmd.toUInt(&ok,10);
                tmpsCmd=sCmdList.at(7);quint16 data_base_type=tmpsCmd.toUInt(&ok,10);
                tmpsCmd=sCmdList.at(8);quint16 start_idx=tmpsCmd.toUInt(&ok,10);
                tmpsCmd=sCmdList.at(9);quint16 take_count=tmpsCmd.toUInt(&ok,10);
                QString data_type=sCmdList.at(10);
                tmpsCmd=sCmdList.at(11);double mutiple=tmpsCmd.toDouble(&ok);
                QString calculation_Form=sCmdList.at(12);
                BridgeManager::instance().gzjSqliteINS()->insertConfiguration(model_Id,target_Type,protocol,collect_Instruct,analytic_Package,read_base,
                                                                              parse_base,data_base_type,start_idx,take_count,data_type,mutiple,calculation_Form);
            }
            //        for (int var = 0; var < sCmdList.size(); ++var) {
            //            QString s1=sCmdList.at(var);
            //            qDebug()<<s1<<endl;
            //        }
            //                bool ok;
            //                int iHexnum = s.toInt(&ok, 16);
            //                chCmd[i] = iHexnum;
        }
        BridgeManager::instance().gzjSqliteINS()->commitConfiguration();
    }


    if(cmdList.at(0)=="5758AAA2"&&cmdList.at(iSize-1)=="475A4A1234BBDD"){
        //清表清自增deviceInfo
        QSqlQuery sql_deleteC(BridgeManager::instance().gzjSqliteINS()->sqlDatabase);
        QString query_sql = "delete from deviceInfo";
        sql_deleteC.prepare(query_sql);
        if(!sql_deleteC.exec()){
            qDebug()<<sql_deleteC.lastError();
        }
        query_sql = "update sqlite_sequence SET seq = 0 where name ='deviceInfo'";
        sql_deleteC.prepare(query_sql);
        if(!sql_deleteC.exec()){
            qDebug()<<sql_deleteC.lastError();
        }

        for (int i=1; i<iSize-1;i++)
        {
            QString s = cmdList.at(i);
            QStringList sCmdList=s.split(",");
            if(sCmdList.size()>=6){
                tmpsCmd=sCmdList.at(0);quint16 model_Id=tmpsCmd.toUInt(&ok,10);
                QString target_Type=sCmdList.at(1);
                tmpsCmd=sCmdList.at(2);quint16 device_Address=tmpsCmd.toUInt(&ok,10);
                tmpsCmd=sCmdList.at(3);quint16 serial_Port=tmpsCmd.toUInt(&ok,10);
                tmpsCmd=sCmdList.at(4);quint16 upload_Mode=tmpsCmd.toUInt(&ok,10);
                tmpsCmd=sCmdList.at(5);quint16 upload_frequence=tmpsCmd.toUInt(&ok,10);

                BridgeManager::instance().gzjSqliteINS()->insertDeviceInfo(model_Id,target_Type,device_Address,serial_Port,upload_Mode,upload_frequence);
            }

        }
        BridgeManager::instance().gzjSqliteINS()->commitDeviceInfo();
    }



    //    qDebug()<<tmpBty.toHex()<<"  "<<tmpBty.count()<<endl;
    //    quint8 byteLen=tmpBty.count();
    //    if (byteLen>8){
    //        if(tmpBty.at(0)==0x57 && tmpBty.at(1)==0x58){
    //            bool ok;
    //            QString elecAddrtmp=QString::number(tmpBty.at(7),10);
    //            qDebug()<<elecAddrtmp.toUInt()<<"  "<<elecAddrtmp<<endl;
    //            double elecba=BridgeManager::instance().electrityMIns()->getElecMeter()[elecAddrtmp.toUInt(&ok,10)].elecQ;
    //            sendMessages(QString::number(elecba));
    //        }
    //        else
    //        {
    //            qDebug()<<"不匹配"<<endl;
    //        }
    //    }
}
