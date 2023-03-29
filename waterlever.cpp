#include "waterlever.h"
#include "ui_waterlever.h"

WaterLever::WaterLever(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaterLever)
{
    ui->setupUi(this);

    connect(ui->waterLReturnButton,&QPushButton::clicked,this,[=]{
        this->hide();
        emit showWidgetUI();
    });
}

WaterLever::~WaterLever()
{
    delete ui;
}
