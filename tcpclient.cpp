#include "tcpclient.h"
#include "ui_tcpclient.h"
#include "bridgemanager.h"

TcpClient::TcpClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    this->setWindowTitle("客户端");
    tcpSocket=new QTcpSocket(this);
    getLocalHostIP();
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveMessages()));
    connect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this,SLOT(socketStateChange(QAbstractSocket::SocketState)));

    toConnect();
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::on_tcpReturnButton_clicked()
{
    this->hide();
    emit showCommonSettingUI();
}

void TcpClient::getLocalHostIP()
{
    QList<QNetworkInterface> list
            = QNetworkInterface::allInterfaces();

    /* 遍历 list */
    foreach (QNetworkInterface interface, list) {

        /* QNetworkAddressEntry 类存储 IP 地址子网掩码和广播地址 */
        QList<QNetworkAddressEntry> entryList
                = interface.addressEntries();

        /* 遍历 entryList */
        foreach (QNetworkAddressEntry entry, entryList) {
            /* 过滤 IPv6 地址，只留下 IPv4 */
            if (entry.ip().protocol() ==
                    QAbstractSocket::IPv4Protocol) {
                ui->comboBox_2->addItem(entry.ip().toString());
                /* 添加到 IP 列表中 */
                IPlist<<entry.ip();
            }
        }
    }
    //    ui->comboBox_2->addItem("192.168.173.223");
}

void TcpClient::toConnect()
{
    if(tcpSocket->state()!=tcpSocket->ConnectedState){
        tcpSocket->connectToHost(ui->lineEdit->text()/*ui->comboBox_2->currentText()*//*IPlist[ui->comboBox_2->currentIndex()]*/,
                                 quint16(ui->spinBox_2->value()));
    }

}

void TcpClient::toConnect(QString ip, quint16 port)
{
    if(tcpSocket->state()!=tcpSocket->ConnectedState){
        tcpSocket->connectToHost(ip,
                                 port);
    }
}

QString TcpClient::getip()
{
    return ui->lineEdit->text();
}

quint16 TcpClient::getport()
{
    return ui->spinBox_2->value();
}

QString TcpClient::getStrMsg()
{
    return tcpRevStrMsg;
}

QByteArray TcpClient::getByteMsg()
{
    return tcpRevByteMsg;
}

void TcpClient::toDisConnect()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

}

void TcpClient::connected()
{
    ui->textBrowser->append("已经连上服务端");
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(true);
    ui->comboBox_2->setEnabled(false);
    ui->spinBox_2->setEnabled(false);
    ui->lineEdit->setEnabled(false);

}

void TcpClient::disconnected()
{
    ui->textBrowser->append("已经断开服务端");
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_6->setEnabled(false);
    ui->comboBox_2->setEnabled(true);
    ui->spinBox_2->setEnabled(true);
    ui->lineEdit->setEnabled(true);
}

void TcpClient::clearTextBrowser()
{
    ui->textBrowser->clear();
}

void TcpClient::receiveMessages()
{
    //    QByteArray tmpBty=tcpSocket->readAll();
    //    ui->textBrowser->append("服务端："+tmpBty.toHex());


    QString message=tcpSocket->readAll();
    ui->textBrowser->append("服务端："+message);

    emit sigReply(message);

    tcpRevStrMsg=message;
    //    tcpRevByteMsg=tmpBty;
    //emit tcpToSeri();
}

void TcpClient::sendMessages()
{

    if(nullptr==tcpSocket)
        return;
    if(tcpSocket->state()==tcpSocket->ConnectedState){
        ui->textBrowser->append("客户端："+ui->lineEdit_2->text());
        tcpSocket->write(ui->lineEdit_2->text().toUtf8().data());

    }
}

void TcpClient::sendMessagesHex(QByteArray tmpBty)
{
    if(nullptr==tcpSocket)
        return;
    if(tcpSocket->state()==tcpSocket->ConnectedState){
        ui->textBrowser->append("客户端："+tmpBty.toHex());
        tcpSocket->write(tmpBty);
    }
}

void TcpClient::sendMessagesHex()
{
    if(nullptr==tcpSocket)
        return;
    if(tcpSocket->state()==tcpSocket->ConnectedState){
        ui->textBrowser->append("客户端："+ui->lineEdit_3->text());

        tcpSocket->write(QByteArray::fromHex(ui->lineEdit_3->text().toLatin1()));
    }
}

void TcpClient::sendMessages(QString tmpStr)
{
    if(nullptr==tcpSocket)
        return;
    if(tcpSocket->state()==tcpSocket->ConnectedState){
        ui->textBrowser->append("客户端："+tmpStr);
        tcpSocket->write(tmpStr.toUtf8().data());

    }
}

void TcpClient::socketStateChange(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::UnconnectedState:
        ui->textBrowser->append("socket状态：UnconnectedState");
        break;
    case QAbstractSocket::ConnectedState:
        ui->textBrowser->append("socket状态：ConnectedState");
        break;
    default:
        break;

    }
}


void TcpClient::on_pushButton_5_clicked()
{
    toConnect();
}

void TcpClient::on_pushButton_6_clicked()
{
    toDisConnect();
}

void TcpClient::on_pushButton_7_clicked()
{
    clearTextBrowser();
}

void TcpClient::on_pushButton_8_clicked()
{
    sendMessages();
}

void TcpClient::on_pushButton_9_clicked()
{
    sendMessagesHex();
}

