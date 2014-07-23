#include "dialt.h"
#include "ui_dialt.h"
#include <qstring.h>

Dialt::Dialt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialt)
{
    ui->setupUi(this);
    Config general_config;
    ui->sensorPriorityLineEdit->setText(QString::number(general_config.reg.getSensorPriority()));
    ui->controlPriorityLineEdit->setText(QString::number(general_config.reg.getControlPriority()));
    ui->actuatorPriorityLineEdit->setText(QString::number(general_config.reg.getActuatorPriority()));
    ui->serialPriorityLineEdit->setText(QString::number(general_config.reg.getSerialPriority()));
    ui->sensorPeriodLineEdit->setText(QString::number(general_config.reg.getSensorPeriod()));
    ui->controlPeriodLineEdit->setText(QString::number(general_config.reg.getControlPeriod()));
    ui->actuatorPeriodLineEdit->setText(QString::number(general_config.reg.getActuatorPeriod()));
    ui->serialPeriodLineEdit->setText(QString::number(general_config.reg.getSerialPeriod()));
    if (general_config.reg.getSensorEnable())
    {
        ui->sensorEnable->setChecked(true);
        ui->sensorPeriodLineEdit->setDisabled(true);
        ui->sensorPriorityLineEdit->setDisabled(true);
    }
    if (general_config.reg.getControlEnable())
    {
        ui->controlEnable->setChecked(true);
        ui->controlPeriodLineEdit->setDisabled(true);
        ui->controlPriorityLineEdit->setDisabled(true);
    }
    if (general_config.reg.getActuatorEnable())
    {
        ui->actuatorEnable->setChecked(true);
        ui->actuatorPeriodLineEdit->setDisabled(true);
        ui->actuatorPriorityLineEdit->setDisabled(true);
    }
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

Dialt::~Dialt()
{
    delete ui;
}

void Dialt::on_sensorCheck_stateChanged(int arg1)
{
    if (arg1!=0){
        ui->sensorEnable->setDisabled(false);
        if(ui->sensorEnable->isChecked())
        {
            ui->sensorPeriodLineEdit->setDisabled(false);
            ui->sensorPriorityLineEdit->setDisabled(false);
        }
        else
        {
            ui->sensorPeriodLineEdit->setDisabled(true);
            ui->sensorPriorityLineEdit->setDisabled(true);
        }
    } else {
        ui->sensorEnable->setDisabled(true);
        ui->sensorPeriodLineEdit->setDisabled(true);
        ui->sensorPriorityLineEdit->setDisabled(true);
    }
}

void Dialt::on_controlCheck_stateChanged(int arg1)
{
    if (arg1!=0){
        ui->controlEnable->setDisabled(false);
        if(ui->controlEnable->isChecked())
        {
            ui->controlPeriodLineEdit->setDisabled(false);
            ui->controlPriorityLineEdit->setDisabled(false);
        }
        else
        {
            ui->controlPeriodLineEdit->setDisabled(true);
            ui->controlPriorityLineEdit->setDisabled(true);
        }
    }
    else
    {
        ui->controlEnable->setDisabled(true);
        ui->controlPeriodLineEdit->setDisabled(true);
        ui->controlPriorityLineEdit->setDisabled(true);
    }
}

void Dialt::on_actuatorCheck_stateChanged(int arg1)
{
    if (arg1!=0){
        ui->actuatorEnable->setDisabled(false);
        if(ui->actuatorEnable->isChecked())
        {
            ui->actuatorPeriodLineEdit->setDisabled(false);
            ui->actuatorPriorityLineEdit->setDisabled(false);
        }
        else
        {
            ui->actuatorPeriodLineEdit->setDisabled(true);
            ui->actuatorPriorityLineEdit->setDisabled(true);
        }
    } else {
        ui->actuatorEnable->setDisabled(true);
        ui->actuatorPeriodLineEdit->setDisabled(true);
        ui->actuatorPriorityLineEdit->setDisabled(true);
    }
}

void Dialt::on_serialCheck_stateChanged(int arg1)
{
    if (arg1!=0){
        ui->serialEnable->setDisabled(false);
        if(ui->serialEnable->isChecked())
        {
            ui->serialPeriodLineEdit->setDisabled(false);
            ui->serialPriorityLineEdit->setDisabled(false);
        }
        else
        {
            ui->serialPeriodLineEdit->setDisabled(true);
            ui->serialPriorityLineEdit->setDisabled(true);
        }
    } else {
        ui->serialEnable->setDisabled(true);
        ui->serialEnable->setChecked(false);
        ui->serialPeriodLineEdit->setDisabled(true);
        ui->serialPriorityLineEdit->setDisabled(true);
    }
}

void Dialt::on_sensorEnable_stateChanged(int arg1)
{
    if (arg1!=0 && ui->sensorCheck){
        ui->sensorPeriodLineEdit->setDisabled(false);
        ui->sensorPriorityLineEdit->setDisabled(false);
    } else {
        ui->sensorPeriodLineEdit->setDisabled(true);
        ui->sensorPriorityLineEdit->setDisabled(true);
    }
}

void Dialt::on_controlEnable_stateChanged(int arg1)
{
    if (arg1!=0 && ui->controlCheck){
        ui->controlPeriodLineEdit->setDisabled(false);
        ui->controlPriorityLineEdit->setDisabled(false);
    } else {
        ui->controlPeriodLineEdit->setDisabled(true);
        ui->controlPriorityLineEdit->setDisabled(true);
    }
}

void Dialt::on_actuatorEnable_stateChanged(int arg1)
{
    if (arg1!=0 && ui->actuatorCheck){
        ui->actuatorPeriodLineEdit->setDisabled(false);
        ui->actuatorPriorityLineEdit->setDisabled(false);
    } else {
        ui->actuatorPeriodLineEdit->setDisabled(true);
        ui->actuatorPriorityLineEdit->setDisabled(true);
    }
}

void Dialt::on_serialEnable_stateChanged(int arg1)
{
    if (arg1!=0){
        ui->serialPeriodLineEdit->setDisabled(false);
        ui->serialPriorityLineEdit->setDisabled(false);
    } else {
        ui->serialPeriodLineEdit->setDisabled(true);
        ui->serialPriorityLineEdit->setDisabled(true);
    }
}

void Dialt::on_buttonBox_accepted()
{
    Config general_config;
    if(ui->sensorCheck->isChecked())
    {
        general_config.reg.setSensorEnable(ui->sensorEnable->isChecked());
        general_config.reg.setSensorPeriod(ui->sensorPeriodLineEdit->text().toInt());
        general_config.reg.setSensorPriority(ui->sensorPriorityLineEdit->text().toInt());
    }
    if(ui->actuatorCheck->isChecked())
    {
        general_config.reg.setActuatorEnable(ui->actuatorEnable->isChecked());
        general_config.reg.setActuatorPeriod(ui->actuatorPeriodLineEdit->text().toInt());
        general_config.reg.setActuatorPriority(ui->actuatorPriorityLineEdit->text().toInt());
    }
    if(ui->controlCheck->isChecked())
    {
        general_config.reg.setControlEnable(ui->controlEnable->isChecked());
        general_config.reg.setControlPeriod(ui->controlPeriodLineEdit->text().toInt());
        general_config.reg.setControlPriority(ui->controlPriorityLineEdit->text().toInt());
    }
    general_config.reg.setSerialPeriod(ui->serialPeriodLineEdit->text().toInt());
    general_config.reg.setSerialPriority(ui->serialPriorityLineEdit->text().toInt());
    this->destroy();
}

void Dialt::on_buttonBox_rejected()
{
    this->destroy();
}
