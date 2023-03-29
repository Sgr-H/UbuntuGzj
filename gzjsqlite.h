#ifndef GZJSQLITE_H
#define GZJSQLITE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QDebug>
#include <QDialog>


class GzjSqlite : public QObject
{
    Q_OBJECT
public:
    explicit GzjSqlite(QObject *parent = nullptr);
    ~GzjSqlite();

    QSqlDatabase sqlDatabase;
    QSqlQuery sql_query;

    //电表历史数据插入；
    void insert(const quint16 &_addr_Sql,const QString &_property_Sql, const QString &_values,
                const QString &_creatTime_Sql, const QString &_table_Name);

    //配置表数据插入;
    void insertConfiguration(const quint16 &_model_Id, const QString &_target_Type, const quint16 &_protocol,
                             const QString &_collect_Instruct, const quint16 &_analytic_Package,
                             const quint16 &_read_base, const quint16 &_parse_base,const quint16 &_data_base_type,
                             const quint16 &_start_idx, const quint16 &_take_count,const QString &_data_type,
                             const double &_mutiple,const QString &_calculation_Form);
    //配置设备数据插入;
    void insertDeviceInfo(const quint16 &_model_Id, const QString &_target_Type,const quint16 &_device_Address,
                          const quint16 &_serial_Port, const quint16 &_upload_Mode, const quint16 &_upload_Frequence);

    void transaction();
    void commit();
    void commitConfiguration();
    void commitDeviceInfo();
//    int count();
    void clear(/*const QString &_table_name*/);

signals:

public slots:
    void initSql();
    void initTable();
    void initManageTable();

private:
    //配置表的数据
    QVariantList cfgModelId,cfgTargetType,cfgProtocol,cfgCollectInstruct,cfgAnalyticPackage,cfgReadBase,
                 cfgParseBase,cfgDataBaseType,cfgStartIdx,cfgTakeCount,cfgDataType,cfgMutiple,cfgCalculationForm;
    //配置设备的数据
    QVariantList deviceInfoMI,deviceInfoTT,deviceInfoDA,deviceInfoSr,deviceInfoUM,deviceInfoUF;

    //电表历史数据
    QVariantList addrSql,propertySql,valuesSql,creatTimeSql;

    QVector<QString> tableName;
    QString ss="eeeef";
};

#endif // GZJSQLITE_H
