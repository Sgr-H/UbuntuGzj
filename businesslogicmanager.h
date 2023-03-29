#ifndef BUSINESSLOGICMANAGER_H
#define BUSINESSLOGICMANAGER_H

#include <QObject>
#include <QThread>

class BusinessLogicManager : public QObject
{
    Q_OBJECT
public:
    explicit BusinessLogicManager(QObject *parent = nullptr);
    ~BusinessLogicManager();
signals:
public slots:
private:
    QThread *businessLogicMThread=nullptr;
};

#endif // BUSINESSLOGICMANAGER_H
