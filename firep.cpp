#include "firep.h"
#include "ui_firep.h"

FireP::FireP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FireP)
{
    ui->setupUi(this);



    connect(ui->fireReturnButton,&QPushButton::clicked,this,[=]{
        this->hide();
        emit showWidgetUI();
    });

    connect(this,&FireP::process_fpMsg,[=](const quint8 &_info_port,const QString &_string_data){
        if(_info_port==1)
            ui->label_12->setText(_string_data);
    });
}

FireP::~FireP()
{
    delete ui;
}
