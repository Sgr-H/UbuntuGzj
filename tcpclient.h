#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QDebug>
namespace Ui {
class TcpClient;
}

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = nullptr);
    ~TcpClient();

    QTcpSocket *tcpSocket;
    void sendMessages(QString tmpStr);
    void sendMessagesHex(QByteArray tmpBty);
    void toConnect(QString ip,quint16 port);
    QString getip();
    quint16 getport();
    QString getStrMsg();
    QByteArray getByteMsg();
    void toConnect();
signals:
    void showCommonSettingUI();
    void tcpToSeri();

    void sigReply(const QString &_string_context);

private slots:
    void on_tcpReturnButton_clicked();
    void toDisConnect();
    void connected();
    void disconnected();
    void clearTextBrowser();
    void receiveMessages();
    void sendMessages();
    void sendMessagesHex();

    void socketStateChange(QAbstractSocket::SocketState);

    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
private:
    Ui::TcpClient *ui;
    QString tcpRevStrMsg;
    QByteArray tcpRevByteMsg;
    QList<QHostAddress>IPlist;
    void getLocalHostIP();
};

#endif // TCPCLIENT_H
