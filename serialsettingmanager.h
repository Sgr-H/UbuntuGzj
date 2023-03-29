#ifndef SERIALSETTINGMANAGER_H
#define SERIALSETTINGMANAGER_H


#include <QObject>
class SerialSettingManager : public QObject
{
    Q_OBJECT
public:
    explicit SerialSettingManager(QObject *parent = nullptr);
    ~SerialSettingManager();
signals:
    void on_comming_msg(const quint8 &_serial_port,const QByteArray &_byte_array);
    void process_msg(const quint8 &_info_port,const QString &_string_data);
public slots:
    void test(const QByteArray &_collect_ba, const QByteArray &_byte_array);
};

#endif // SERIALSETTINGMANAGER_H
