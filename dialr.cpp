#include "dialr.h"
#include "ui_dialr.h"

Dialr::Dialr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialr)
{
    ui->setupUi(this);
    Config general_config;
    ui->monitoringLineEdit->setText(QString::number(general_config.reg.getMonitoring()));
    ui->sensoringLineEdit->setText(QString::number(general_config.reg.getSensoring()));
    ui->trajectoryLineEdit->setText(QString::number(general_config.reg.getTrajectory()));
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

Dialr::~Dialr()
{
    delete ui;
}

void Dialr::on_buttonBox_accepted()
{
    Config general_config;
    general_config.reg.setMonitoring(ui->monitoringLineEdit->text().toInt());
    general_config.reg.setSensoring(ui->sensoringLineEdit->text().toInt());
    general_config.reg.setTrajectory(ui->trajectoryLineEdit->text().toInt());
}

