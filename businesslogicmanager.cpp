#include "businesslogicmanager.h"
#include "bridgemanager.h"
BusinessLogicManager::BusinessLogicManager(QObject *parent) : QObject(parent)
{
    businessLogicMThread = new QThread();
    this->moveToThread(businessLogicMThread);
}
BusinessLogicManager::~BusinessLogicManager()
{

}
