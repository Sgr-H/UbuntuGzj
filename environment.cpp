#include "environment.h"
#include "ui_environment.h"

Environment::Environment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Environment)
{
    ui->setupUi(this);
}

Environment::~Environment()
{
    delete ui;
}

void Environment::on_envReturnButton_clicked()
{
    this->hide();
    emit showWidgetUI();
}
