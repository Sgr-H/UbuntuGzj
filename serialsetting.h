#ifndef SERIALSETTING_H
#define SERIALSETTING_H

#include <QWidget>
#include <QSerialPort>      //串口类
#include <QSerialPortInfo>  //串口信息类
#include <QTimer>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QDebug>



namespace Ui {
class SerialSetting;
}

class SerialSetting : public QWidget
{
    Q_OBJECT

public:
    explicit SerialSetting(QWidget *parent = nullptr);
    ~SerialSetting();

    QSerialPort * serialPort1=new QSerialPort(this);
    QSerialPort * serialPort2=new QSerialPort(this);
    QSerialPort * serialPort3=new QSerialPort(this);
    QSerialPort * serialPort4=new QSerialPort(this);
    QVector<QSerialPort*> VectorSerialPort;
    QVector<QPushButton*> VectorPushBotton;
    QVector<QString> VectorPortName;
    QVector<QByteArray> VectorClcCmd;

    struct Settings {
        int parity = QSerialPort::NoParity;
        int baud = QSerialPort::Baud9600;
        int dataBits = QSerialPort::Data8;
        int stopBits = QSerialPort::OneStop;
    };
    Settings *settings() const;
    void elecPollingStart();

    void collectTimerctl(const quint32 &_timeout);

signals:
    void showCommonSettingUI();
    void sigReply(const QByteArray &_collect_ba, const QByteArray &_byte_array);
private slots:
    void bufferData();
    void bufferData1();
    void readData();
    void readData1();


    void on_applyButton_5_clicked();

    void on_serial1PushButton_clicked();

    void on_closePushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_serial2PushButton_clicked();

    void on_serial3PushButton_clicked();

    void on_serial4PushButton_clicked();

private:
    //变量
    Settings *m_settings=nullptr;

    QTimer *readTimer=nullptr;
    QTimer *readTimer1=nullptr;
    QTimer *sendTimer=nullptr;
    QTimer *collectTimer=nullptr;

    QComboBox *parityCombo[4];
    QComboBox *baudCombo[4];
    QComboBox *dataBitsCombo[4];
    QComboBox *stopBitsCombo[4];

    QByteArray buffArray;
    QByteArray buffArray1;

    quint8 cmdcount=0;

    //函数
    void serialControl(quint8 ,QString ,bool );//打开串口
    void Init();//初始化函数
    void elecClc();//电量信息收集

private:
    Ui::SerialSetting *ui;
};

#endif // SERIALSETTING_H
