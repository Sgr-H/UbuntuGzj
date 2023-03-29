#include "commonsetting.h"
#include "ui_commonsetting.h"
#include "bridgemanager.h"

CommonSetting::CommonSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonSetting)
{
    ui->setupUi(this);
    init();
}

CommonSetting::~CommonSetting()
{
    delete ui;
}

void CommonSetting::init()
{

    //通用设置界面 ---> 串口设置界面
    connect(ui->serialPushButton,&QPushButton::clicked,this,[=]{
        this->hide();
        BridgeManager::instance().serialIns()->show();
    });

    //通用设置界面 ---> 网络设置界面
    connect(ui->networkPushButton,&QPushButton::clicked,this,[=]{
        this->hide();
        BridgeManager::instance().tcpCIns()->show();
    });



}



void CommonSetting::on_close_clicked()
{
    if (!(QMessageBox::information(this,tr("exit tip"),tr("Do you really want exit ?"),tr("Yes"),tr("No"))))
    {
        QApplication* app;
        app->exit(0);
    }
}

void CommonSetting::on_return_2_clicked()
{
    this->hide();
    emit showWidgetUI();
}

void CommonSetting::on_pushButton_3_clicked()
{
    emit signtest();
}
