#include "liftmanager.h"
#include "ui_liftmanager.h"

LiftManager::LiftManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LiftManager)
{
    ui->setupUi(this);
    connect(ui->liftReturnButton,&QPushButton::clicked,this,[=]{
        this->hide();
        emit showWidgetUI();
    });
}

LiftManager::~LiftManager()
{
    delete ui;
}
