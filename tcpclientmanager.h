#ifndef TCPCLIENTMANAGER_H
#define TCPCLIENTMANAGER_H

#include <QObject>

class tcpClientManager: public QObject
{
    Q_OBJECT
public:
    explicit tcpClientManager(QObject *parent = nullptr);
    ~tcpClientManager();
signals:

public slots:
    void test(const QString &_string_context);
};

#endif // TCPCLIENTMANAGER_H
