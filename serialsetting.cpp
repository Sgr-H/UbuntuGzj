#include "serialsetting.h"
#include "ui_serialsetting.h"
#include <QMessageBox>
#include <QDebug>
#include "bridgemanager.h"

SerialSetting::SerialSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialSetting)
{
    ui->setupUi(this);
    //初始化
    Init();

    //信号槽
    connect(VectorSerialPort.at(0),SIGNAL(readyRead()),this,SLOT(bufferData()));
    connect(readTimer,&QTimer::timeout,this,&SerialSetting::readData);

    connect(VectorSerialPort.at(1),SIGNAL(readyRead()),this,SLOT(bufferData1()));
    connect(readTimer1,&QTimer::timeout,this,&SerialSetting::readData1);

    connect(sendTimer,&QTimer::timeout,this,&SerialSetting::elecClc);
    connect(collectTimer,&QTimer::timeout,this,[=]{
        BridgeManager::instance().waterMIns()->getModel()->select();
        elecPollingStart();
    });
}

SerialSetting::~SerialSetting()
{
    delete ui;
}

SerialSetting::Settings *SerialSetting::settings() const
{
    return m_settings;
}

void SerialSetting::elecPollingStart()
{
    sendTimer->start(500);
}

void SerialSetting::collectTimerctl(const quint32 &_timeout)
{
    if(_timeout)
        collectTimer->start(_timeout);
    else
        collectTimer->stop();
}

void SerialSetting::on_applyButton_5_clicked()
{

    for (int var = 0; var < 4; ++var) {
        m_settings[var].parity = parityCombo[var]->currentIndex();
        if (m_settings[var].parity > 0)
            m_settings[var].parity++;
        m_settings[var].baud = baudCombo[var]->currentText().toInt();
        m_settings[var].dataBits = dataBitsCombo[var]->currentText().toInt();
        m_settings[var].stopBits = stopBitsCombo[var]->currentText().toInt();
    }
    qDebug()<<m_settings[0].baud<<endl;
    //    this->hide();
}

void SerialSetting::Init()
{
    m_settings=new Settings[4];
    VectorSerialPort.append(serialPort1);
    VectorSerialPort.append(serialPort2);
    VectorSerialPort.append(serialPort3);
    VectorSerialPort.append(serialPort4);

    VectorPushBotton.append(ui->serial1PushButton);
    VectorPushBotton.append(ui->serial2PushButton);
    VectorPushBotton.append(ui->serial3PushButton);
    VectorPushBotton.append(ui->serial4PushButton);

    parityCombo[0]=ui->parityCombo10;
    parityCombo[1]=ui->parityCombo11;
    parityCombo[2]=ui->parityCombo12;
    parityCombo[3]=ui->parityCombo13;

    baudCombo[0]=ui->baudCombo10;
    baudCombo[1]=ui->baudCombo11;
    baudCombo[2]=ui->baudCombo12;
    baudCombo[3]=ui->baudCombo13;

    dataBitsCombo[0]=ui->dataBitsCombo10;
    dataBitsCombo[1]=ui->dataBitsCombo11;
    dataBitsCombo[2]=ui->dataBitsCombo12;
    dataBitsCombo[3]=ui->dataBitsCombo13;

    stopBitsCombo[0]=ui->stopBitsCombo10;
    stopBitsCombo[1]=ui->stopBitsCombo11;
    stopBitsCombo[2]=ui->stopBitsCombo12;
    stopBitsCombo[3]=ui->stopBitsCombo13;

    //初始化采集指令集合
    QByteArray senddata;
    senddata.resize(8);
    senddata = QByteArray::fromHex("01 01 03 0003 0002 01");
    VectorClcCmd.append(senddata);
    senddata = QByteArray::fromHex("01 01 03 003F 0002 01");
    VectorClcCmd.append(senddata);
    senddata = QByteArray::fromHex("01 01 03 0025 0009 01");
    VectorClcCmd.append(senddata);
    //初始化定时器
    readTimer=new QTimer(this);             //3.5个字符读取时间  控制每次读取时间
    readTimer1=new QTimer(this);
    sendTimer=new QTimer(this);             //500ms 控制每次发送时间
    collectTimer=new QTimer(this);          //5s 一次采集

    //初始控件
    for (int var = 0; var < 4; ++var) {
        parityCombo[var]->setCurrentIndex(0);
        baudCombo[var]->setCurrentText(QString::number(m_settings[var].baud));
        dataBitsCombo[var]->setCurrentText(QString::number(m_settings[var].dataBits));
        stopBitsCombo[var]->setCurrentText(QString::number(m_settings[var].stopBits));
    }

    //扫描本机的串口，并且添加到下拉框里
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->serialComboBox->addItem(info.portName());
        VectorPortName.append(info.portName());
    }
    for (int var = 0; var < VectorPortName.count(); ++var) {
        serialControl(var,VectorPortName.at(var),0);
    }
}

void SerialSetting::elecClc()
{
    serialPort1->write(QByteArray::fromHex("6666"));
    serialPort2->write("6666");
//    if(cmdcount>=VectorClcCmd.size()){
//        sendTimer->stop();
//        cmdcount=0;
//        return;
//    }
//    QByteArray text=VectorClcCmd.at(cmdcount);
//    quint8 targetId=text.at(0);
//    quint8 port =text.at(1);
//    QByteArray dataSeg=text.mid(2,text.size()-3);
//    QByteArray addr=text.right(1);
//    QByteArray sendByteArray;
//    sendByteArray.append(addr);
//    sendByteArray.append(dataSeg);
//    VectorSerialPort[1]->write(sendByteArray);
//    qDebug()<<targetId<<"  "<<port<<endl;
//    qDebug()<<sendByteArray;
}

void SerialSetting::bufferData()
{

    //定时50ms
    readTimer->start(quint32(38.5/m_settings[0].baud*1000+1));
    buffArray.append(VectorSerialPort.at(0)->readAll());
}

void SerialSetting::bufferData1()
{
    //定时50ms
    readTimer1->start(quint32(38.5/m_settings[1].baud*1000+1));
    buffArray1.append(VectorSerialPort.at(1)->readAll());
}

void SerialSetting::readData()
{
    readTimer->stop();
    ui->textBrowser->append("服务端："+buffArray.toHex());
    emit sigReply(VectorClcCmd.at(cmdcount++),buffArray);
    buffArray.clear();
}

void SerialSetting::readData1()
{
    readTimer1->stop();
    ui->textBrowser->append("服务端："+buffArray1.toHex());
    emit sigReply(VectorClcCmd.at(cmdcount++),buffArray1);
    buffArray1.clear();
}



//serialNum为串口编号，portName为串口名，flag为1则有开关串口功能，flag为0则只有打开串口功能）
void SerialSetting::serialControl(quint8 serialNum,QString portName,bool flag)
{
    //查看串口是否连接
    if(!VectorSerialPort.at(serialNum)->isOpen()){
        //实现串口连接
        VectorSerialPort.at(serialNum)->setPortName(portName);
        VectorSerialPort.at(serialNum)->setBaudRate(m_settings[serialNum].baud);
        VectorSerialPort.at(serialNum)->setStopBits(QSerialPort::StopBits(m_settings[serialNum].stopBits));
        VectorSerialPort.at(serialNum)->setDataBits(QSerialPort::DataBits(m_settings[serialNum].dataBits));
        VectorSerialPort.at(serialNum)->setParity(QSerialPort::Parity(m_settings[serialNum].parity));
        VectorSerialPort.at(serialNum)->setFlowControl(QSerialPort::NoFlowControl);
        if(!VectorSerialPort.at(serialNum)->open(QIODevice::ReadWrite)){
            QMessageBox::about(this,"erro",QString("serialPort%1 open fail").arg(serialNum+1));
            qDebug()<<"serial1 open fail!";
            return;
        }
        else{
            qDebug()<<"serial1 open!";
            if(flag)
                QMessageBox::about(this,"erro","open");
            VectorPushBotton.at(serialNum)->setText(tr("关闭串口"));
            VectorPushBotton.at(serialNum)->setStyleSheet(tr("QPushButton{background-color: rgb(204, 0, 0);}"));
        }
    }
    else{
        if(flag){
            //断开连接
            VectorSerialPort.at(serialNum)->close();
            QMessageBox::about(this,"success","close");
            VectorPushBotton.at(serialNum)->setText(tr("打开串口"));
            VectorPushBotton.at(serialNum)->setStyleSheet(tr("QPushButton{background-color: rgb(115, 210, 22);}"));
        }
    }
}

void SerialSetting::on_closePushButton_clicked()
{
    for (int var = 0; var < 4; ++var) {

        switch (m_settings[var].parity) {
        case 0:
            parityCombo[var]->setCurrentIndex(0);
            break;
        case 2:
            parityCombo[var]->setCurrentIndex(1);
            break;
        case 3:
            parityCombo[var]->setCurrentIndex(2);
            break;
        case 4:
            parityCombo[var]->setCurrentIndex(3);
            break;
        case 5:
            parityCombo[var]->setCurrentIndex(4);
            break;
        default:
            break;
        }

        switch (m_settings[var].baud) {
        case 1200:
            baudCombo[var]->setCurrentIndex(0);
            break;
        case 2400:
            baudCombo[var]->setCurrentIndex(1);
            break;
        case 4800:
            baudCombo[var]->setCurrentIndex(2);
            break;
        case 9600:
            baudCombo[var]->setCurrentIndex(3);
            break;
        case 19200:
            baudCombo[var]->setCurrentIndex(4);
            break;
        case 38400:
            baudCombo[var]->setCurrentIndex(5);
            break;
        case 57600:
            baudCombo[var]->setCurrentIndex(6);
            break;
        case 115200:
            baudCombo[var]->setCurrentIndex(7);
            break;
        default:
            break;
        }

        switch (m_settings[var].dataBits) {
        case 5:
            dataBitsCombo[var]->setCurrentIndex(0);
            break;
        case 6:
            dataBitsCombo[var]->setCurrentIndex(1);
            break;
        case 7:
            dataBitsCombo[var]->setCurrentIndex(2);
            break;
        case 8:
            dataBitsCombo[var]->setCurrentIndex(3);
            break;

        default:
            break;
        }

        switch (m_settings[var].stopBits) {
        case 1:
            stopBitsCombo[var]->setCurrentIndex(0);
            break;
        case 2:
            stopBitsCombo[var]->setCurrentIndex(1);
            break;
        case 3:
            stopBitsCombo[var]->setCurrentIndex(2);
            break;

        default:
            break;
        }

    }

    qDebug()<<m_settings[0].baud<<endl;
    this->hide();
    emit showCommonSettingUI();
}

void SerialSetting::on_pushButton_3_clicked()
{
    qDebug()<<ui->serialComboBox->currentIndex();
    ui->lineEdit->clear();
}

void SerialSetting::on_pushButton_2_clicked()
{
    if(nullptr==serialPort1&&nullptr==serialPort2&&nullptr==serialPort3&&nullptr==serialPort4)
        return;
    if(ui->serialComboBox->currentText()==VectorPortName.at(0)){
        if(serialPort1->isOpen()){
            ui->textBrowser->append("客户端："+ui->lineEdit->text());
            serialPort1->write(QByteArray::fromHex(ui->lineEdit->text().toLatin1()));
        }
    }
    else if(ui->serialComboBox->currentText()==VectorPortName.at(1)){
        if(serialPort2->isOpen()){
            ui->textBrowser->append("客户端："+ui->lineEdit->text());
            serialPort2->write(QByteArray::fromHex(ui->lineEdit->text().toLatin1()));
        }
    }


    //    switch (ui->serialComboBox->currentText()) {
    //    case VectorPortName.at(0):
    //        break;
    //    default:
    //        break;
    //    }

}


void SerialSetting::on_serial1PushButton_clicked()
{
    serialControl(0,VectorPortName.at(0),1);
}

void SerialSetting::on_serial2PushButton_clicked()
{
    if (VectorPortName.count()>1)
        serialControl(1,VectorPortName.at(1),1);
    else
        QMessageBox::about(this,"erro","串口不存在或异常");
}

void SerialSetting::on_serial3PushButton_clicked()
{
    if (VectorPortName.count()>2)
        serialControl(2,VectorPortName.at(2),1);
    else
        QMessageBox::about(this,"erro","串口不存在或异常");
}

void SerialSetting::on_serial4PushButton_clicked()
{
    if (VectorPortName.count()>3)
        serialControl(3,VectorPortName.at(3),1);
    else
        QMessageBox::about(this,"erro","串口不存在或异常");
}
