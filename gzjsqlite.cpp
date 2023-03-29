#include "gzjsqlite.h"
#include <QDateTime>
GzjSqlite::GzjSqlite(QObject *parent) : QObject(parent)
{
    initSql();;
    initTable();
    initManageTable();
}

GzjSqlite::~GzjSqlite()
{
    sqlDatabase.close();
}

void GzjSqlite::insert(const quint16 &_addr_Sql, const QString &_property_Sql, const  QString &_values_Sql, const QString &_creatTime_Sql, const QString &_table_Name)
{
    // 50个数据提交一次事务，也就是说一万条之前先把数据存储在内存中
    if(addrSql.size() == 50){
        commit();
    }
    if(addrSql.size() == 0){
        transaction();
    }
    addrSql << _addr_Sql;
    propertySql << _property_Sql;
    valuesSql << _values_Sql;
    creatTimeSql << _creatTime_Sql;
    tableName.append(_table_Name);
}

void GzjSqlite::insertConfiguration(const quint16 &_model_Id, const QString &_target_Type, const quint16 &_protocol, const QString &_collect_Instruct, const quint16 &_analytic_Package, const quint16 &_read_base, const quint16 &_parse_base, const quint16 &_data_base_type, const quint16 &_start_idx, const quint16 &_take_count, const QString &_data_type, const double &_mutiple, const QString &_calculation_Form)
{
    cfgModelId << _model_Id;
    cfgTargetType << _target_Type;
    cfgProtocol << _protocol;
    cfgCollectInstruct << _collect_Instruct;
    cfgAnalyticPackage << _analytic_Package;
    cfgReadBase << _read_base;
    cfgParseBase << _parse_base;
    cfgDataBaseType << _data_base_type;
    cfgStartIdx << _start_idx;
    cfgTakeCount << _take_count;
    cfgDataType << _data_type;
    cfgMutiple << _mutiple;
    cfgCalculationForm << _calculation_Form;
}

void GzjSqlite::insertDeviceInfo(const quint16 &_model_Id, const QString &_target_Type, const quint16 &_device_Address, const quint16 &_serial_Port, const quint16 &_upload_Mode, const quint16 &_upload_Frequence)
{
    deviceInfoMI << _model_Id;
    deviceInfoTT << _target_Type;
    deviceInfoDA << _device_Address;
    deviceInfoSr << _serial_Port;
    deviceInfoUM << _upload_Mode;
    deviceInfoUF << _upload_Frequence;
}

void GzjSqlite::transaction()
{
    sqlDatabase.transaction();
}

void GzjSqlite::commit()
{
    for (int var = 0; var < 50; ++var) {
        QString commit_Sql=QString("insert into %1 values(null,?,?,?,?)").arg(tableName.value(var));
        sql_query.prepare(commit_Sql);
        sql_query.addBindValue(addrSql.at(var));
        sql_query.addBindValue(propertySql.at(var));
        sql_query.addBindValue(valuesSql.at(var));
        sql_query.addBindValue(creatTimeSql.at(var));
        if(!sql_query.exec()){
            qDebug() << "exec fail:" << sql_query.lastError().text();
            if(!sqlDatabase.rollback()){
                qDebug() << "rollback fail:" << sqlDatabase.lastError().text();
            }
            addrSql.clear();
            propertySql.clear();
            valuesSql.clear();
            creatTimeSql.clear();
            return;
        };
    }

    if(!sqlDatabase.commit()){
        qDebug() << "commit fail:" << sqlDatabase.lastError().text();

    }
    else
    {
        qDebug() << "commit Success" << addrSql.size();
    }

    addrSql.clear();
    propertySql.clear();
    valuesSql.clear();
    creatTimeSql.clear();
}

void GzjSqlite::commitConfiguration()
{
    //开启事物
    transaction();
    QString commit_Sql=QString("insert into configuration values(null,?,?,?,?,?, ?,?,?,?,?, ?,?,?)");
    sql_query.prepare(commit_Sql);
    sql_query.addBindValue(cfgModelId);
    sql_query.addBindValue(cfgTargetType);
    sql_query.addBindValue(cfgProtocol);
    sql_query.addBindValue(cfgCollectInstruct);
    sql_query.addBindValue(cfgAnalyticPackage);

    sql_query.addBindValue(cfgReadBase);
    sql_query.addBindValue(cfgParseBase);
    sql_query.addBindValue(cfgDataBaseType);
    sql_query.addBindValue(cfgStartIdx);
    sql_query.addBindValue(cfgTakeCount);

    sql_query.addBindValue(cfgDataType);
    sql_query.addBindValue(cfgMutiple);
    sql_query.addBindValue(cfgCalculationForm);

    if(!sql_query.execBatch()){
        qDebug() << "execBatch fail:" << sql_query.lastError().text();
        if(!sqlDatabase.rollback()){
            qDebug() << "rollback fail:" << sqlDatabase.lastError().text();
        }
        cfgModelId.clear();cfgTargetType.clear();cfgProtocol.clear();cfgCollectInstruct.clear();
        cfgAnalyticPackage.clear();cfgReadBase.clear();cfgParseBase.clear();cfgDataBaseType.clear();
        cfgStartIdx.clear();cfgTakeCount.clear();cfgDataType.clear();cfgMutiple.clear();
        cfgCalculationForm.clear();
        return;
    };
    if(!sqlDatabase.commit()){
        qDebug() << "commitConfiguration fail:" << sqlDatabase.lastError().text();
    }
    else
    {
        qDebug() << "commit Success" << cfgModelId.size();
    }
    cfgModelId.clear();cfgTargetType.clear();cfgProtocol.clear();cfgCollectInstruct.clear();
    cfgAnalyticPackage.clear();cfgReadBase.clear();cfgParseBase.clear();cfgDataBaseType.clear();
    cfgStartIdx.clear();cfgTakeCount.clear();cfgDataType.clear();cfgMutiple.clear();
    cfgCalculationForm.clear();
}

void GzjSqlite::commitDeviceInfo()
{
    //开启事物
    transaction();
    QString commit_Sql=QString("insert into deviceInfo values(null, ?,?,?,?,?,?)");
    sql_query.prepare(commit_Sql);
    sql_query.addBindValue(deviceInfoMI);
    sql_query.addBindValue(deviceInfoTT);
    sql_query.addBindValue(deviceInfoDA);
    sql_query.addBindValue(deviceInfoSr);
    sql_query.addBindValue(deviceInfoUM);
    sql_query.addBindValue(deviceInfoUF);


    if(!sql_query.execBatch()){
        qDebug() << "execBatch fail:" << sql_query.lastError().text();
        if(!sqlDatabase.rollback()){
            qDebug() << "rollback fail:" << sqlDatabase.lastError().text();
        }
        deviceInfoMI.clear();deviceInfoTT.clear();deviceInfoDA.clear();deviceInfoSr.clear();
        deviceInfoUM.clear();deviceInfoUF.clear();
        return;
    };
    if(!sqlDatabase.commit()){
        qDebug() << "commit fail:" << sqlDatabase.lastError().text();
    }
    else
    {
        qDebug() << "commitDeviceInfo Success" << deviceInfoMI.size();
    }
    deviceInfoMI.clear();deviceInfoTT.clear();deviceInfoDA.clear();deviceInfoSr.clear();
    deviceInfoUM.clear();deviceInfoUF.clear();
}

void GzjSqlite::clear(/*const QString &_table_name*/)
{
    sqlDatabase.commit();
    QString clear_Sql=QString("delete from %1").arg("elecMH");
    sql_query.prepare(clear_Sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "clear success";
    }
}

void GzjSqlite::initSql()
{
    //查看系统已存在数据库
    QStringList drivers = QSqlDatabase::drivers();
    foreach(QString driver, drivers) {
        qDebug()<<driver;
    }
    //检查数据库连接，若无则新建
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        sqlDatabase = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        sqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
        sqlDatabase.setDatabaseName("gzjsqlite.db");
        sqlDatabase.setUserName("sgrh");
        sqlDatabase.setPassword("123456");
    }
    //连接数据库
    if (!sqlDatabase.open())
        qDebug()<<"连接数据库错误"<<sqlDatabase.lastError()  <<endl;
    sql_query=QSqlQuery(sqlDatabase);
}

void GzjSqlite::initTable()
{
    //连接数据库
    if (!sqlDatabase.open())
        qDebug()<<"连接数据库错误"<<sqlDatabase.lastError()  <<endl;
    else{
        qDebug()<<"连接数据库成功"<<endl;
        //查询表个数
        QStringList tableNameList   = sqlDatabase.tables();
        qDebug() << "查询的表名的个数= " << tableNameList.count();
        for (int var = 0; var < tableNameList.count(); ++var) {
            qDebug()<<tableNameList.at(var)<<endl;
        }

        //表中是否有elecM，无则创建
        if(!tableNameList.contains("elecM")){
            //            使用sql语句创建表并且初始化字段
            QString createTable_sql = "create table elecM (id int , addr int primary key,elecQ varchar(15),"
                                      "IA varchar(15),IB varchar(15),IC varchar(15),VA varchar(15),VB varchar(15),VC varchar(15),"
                                      "VAB varchar(15),VBC varchar(15),VAC varchar(15),TotalP varchar(15))";
            sql_query.prepare(createTable_sql);
            if(!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }
            else
            {
                qDebug() << "create elecM table!";
            }
        }
        //表中是否有waterM，无则创建
        if(!tableNameList.contains("waterM")){
            //            使用sql语句创建表并且初始化字段
            QString createTable_sql = "create table waterM (id int , addr int primary key,waterQ varchar(15))";
            sql_query.prepare(createTable_sql);
            if(!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }
            else
            {
                qDebug() << "create waterM table!";
            }
        }
        //表中是否有elecMH，无则创建
        if(!tableNameList.contains("elecMH")){
            //            使用sql语句创建表并且初始化字段
            QString createTable_sql = "create table elecMH (id integer primary key Autoincrement,addr int NOT NULL,property varchar(15) NOT NULL,"
                                      "value varchar(15) NOT NULL,creatTime timestamp DEFAULT (datetime('now','localtime')) )";
            sql_query.prepare(createTable_sql);
            if(!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }
            else
            {
                qDebug() << "create elecMH table!";
            }
        }
        //表中是否有configuration，无则创建
        if(!tableNameList.contains("configuration")){
            //            使用sql语句创建表并且初始化字段
            QString createTable_sql = "create table configuration ("
                                      "id integer primary key Autoincrement,model_Id int NOT NULL,target_Type varchar(32) NOT NULL,"
                                      "protocol int NOT NULL,collect_Instruct varchar(32) NOT NULL,analytic_Package int NOT NULL,"
                                      "READ_BASE int NOT NULL, PARSE_BASE int NOT NULL,DATA_BASE_TYPE int NOT NULL,START_IDX int NOT NULL,"
                                      "TAKE_COUNT int NOT NULL,DATA_TYPE varchar(32) NOT NULL,MUTIPLE double NOT NULL,"
                                      "CALCULATION_FORMULA varchar(32) NOT NULL"
                                      ")";
            sql_query.prepare(createTable_sql);
            if(!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }
            else
            {
                qDebug() << "create Configuration table!";
            }
        }

        //表中是否有deviceInfo，无则创建
        if(!tableNameList.contains("deviceInfo")){
            //            使用sql语句创建表并且初始化字段
            QString createTable_sql = "create table deviceInfo ("
                                      "id integer primary key Autoincrement,model_Id int NOT NULL,target_Type varchar(32) NOT NULL,"
                                      "device_Addr int NOT NULL,serial_Port int NOT NULL,"
                                      "upload_mode int NOT NULL, upload_frequency int NOT NULL"
                                      ")";
            sql_query.prepare(createTable_sql);
            if(!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }
            else
            {
                qDebug() << "create deviceInfo table!";
            }
        }



    }
}

void GzjSqlite::initManageTable()
{
    //查询表是否为空
    QString select_sql = "select id from Configuration";
    QVariantList id;
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            id << sql_query.value(0).toInt();
        }
    }

    if(!id.size()){
        sqlDatabase.commit();
        insertConfiguration(1,"010100010001",1,"0300030001",1,16,10,8,4,2,"UINT16",1.0,"00");
        insertConfiguration(1,"010100010002",1,"0300040001",1,16,10,8,4,2,"UINT16",1.0,"00");
        insertConfiguration(1,"010100010003",1,"0300230001",1,16,10,8,4,1,"BYTE",1.0,"01");
        insertConfiguration(1,"010100010004",1,"0300230001",1,16,10,8,5,1,"BYTE",1.0,"01");
        insertConfiguration(1,"010100010005",1,"0300240001",1,16,2,2,12,1,"BIT",1.0,"02");
        insertConfiguration(1,"010100010006",1,"0300240001",1,16,10,8,4,1,"BYTE",1.0,"01");
        insertConfiguration(1,"010100010007",1,"0300250001",1,16,10,8,4,2,"UINT16",1.0,"03");
        insertConfiguration(1,"010100010008",1,"0300260001",1,16,10,8,4,2,"UINT16",1.0,"03");
        insertConfiguration(1,"010100010009",1,"0300270001",1,16,10,8,4,2,"UINT16",1.0,"03");
        insertConfiguration(1,"01010001000A",1,"0300280001",1,16,10,8,4,2,"UINT16",1.0,"03");
        insertConfiguration(1,"01010001000B",1,"0300290001",1,16,10,8,4,2,"UINT16",1.0,"03");
        insertConfiguration(1,"01010001000C",1,"03002A0001",1,16,10,8,4,2,"UINT16",1.0,"03");
        insertConfiguration(1,"01010001000D",1,"03002B0001",1,16,10,8,4,2,"UINT16",1.0,"03");
        insertConfiguration(1,"01010001000E",1,"03002C0001",1,16,10,8,4,2,"UINT16",1.0,"03");
        insertConfiguration(1,"01010001000F",1,"03002D0001",1,16,10,8,4,2,"UINT16",1.0,"03");
        insertConfiguration(1,"010100010010",1,"0300310001",1,16,10,8,4,2,"UINT16",1.0,"04");
        insertConfiguration(1,"010100010011",1,"03003F0002",1,16,10,8,4,4,"UINT32",0.001,"05");
        commitConfiguration();
    }
}

