#include "dialcomm.h"
#include "ui_dialcomm.h"
#include "config.h"

DialComm::DialComm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialComm)
{
    ui->setupUi(this);
    ui->baudRateLineEdit->setText(QString::number(Config::reg.getBaud()));
    ui->ipLineEdit->setText(Config::reg.getIp());
    ui->machineIDLineEdit->setText(QString::number(Config::reg.getMachineId()));
    ui->portLineEdit->setText(QString::number(Config::reg.getPort()));
    updateSerial();
    if(Config::reg.getSerialOn())
    {
        ui->serialButton->setChecked(true);
        ui->baudRateLineEdit->setEnabled(true);
        ui->machineIDLineEdit->setEnabled(true);
        ui->ipLineEdit->setEnabled(false);
        ui->portLineEdit->setEnabled(false);
        ui->serialCombo->setEnabled(true);
        int index = 0;
        if (QString::compare(Config::reg.getSerialPort(), "") != 0)
            foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
            {
                index++;
                if (QString::compare(info.portName(), Config::reg.getSerialPort()) == 0)
                {
                    ui->serialCombo->setCurrentIndex(index);
                    break;
                }
            }
        else
            ui->serialCombo->setCurrentIndex(0);

        if(ui->serialCombo->currentIndex() == 0)
            ui->buttonBox->buttons()[0]->setEnabled(false);
    }
    else if (Config::reg.getUdpOn())
    {
        ui->udpButton->setChecked(true);
        ui->baudRateLineEdit->setEnabled(false);
        ui->machineIDLineEdit->setEnabled(false);
        ui->ipLineEdit->setEnabled(true);
        ui->portLineEdit->setEnabled(true);
    }
    else
    {
        ui->tcpButton->setChecked(true);
        ui->baudRateLineEdit->setEnabled(false);
        ui->machineIDLineEdit->setEnabled(false);
        ui->ipLineEdit->setEnabled(true);
        ui->portLineEdit->setEnabled(true);
    }
}

DialComm::~DialComm()
{
    delete ui;
}

void DialComm::on_buttonBox_accepted()
{
    if(ui->serialButton->isChecked())
    {
        Config::reg.setBaud(ui->baudRateLineEdit->text().toDouble());
        Config::reg.setMachineId(ui->machineIDLineEdit->text().toShort());
        Config::reg.setSerialOn(true);
        Config::reg.setUdpOn(false);
        Config::reg.setTcpOn(false);
        Config::reg.setSerialPort(ui->serialCombo->currentText());
    }
    else if(ui->udpButton->isChecked())
    {
        Config::reg.setIp(ui->ipLineEdit->text());
        Config::reg.setPort(ui->portLineEdit->text().toInt());
        Config::reg.setSerialOn(false);
        Config::reg.setUdpOn(true);
        Config::reg.setTcpOn(false);
    }
    else
    {
        Config::reg.setIp(ui->ipLineEdit->text());
        Config::reg.setPort(ui->portLineEdit->text().toInt());
        Config::reg.setSerialOn(false);
        Config::reg.setUdpOn(false);
        Config::reg.setTcpOn(true);
    }
}

void DialComm::on_buttonBox_rejected()
{
    this->close();
}

void DialComm::on_serialButton_clicked(bool checked)
{
    ui->baudRateLineEdit->setEnabled(checked);
    ui->machineIDLineEdit->setEnabled(checked);
    ui->ipLineEdit->setEnabled(!checked);
    ui->portLineEdit->setEnabled(!checked);
    ui->serialCombo->setEnabled(checked);
}

void DialComm::on_udpButton_clicked(bool checked)
{
    ui->baudRateLineEdit->setEnabled(!checked);
    ui->machineIDLineEdit->setEnabled(!checked);
    ui->ipLineEdit->setEnabled(checked);
    ui->portLineEdit->setEnabled(checked);
    ui->serialCombo->setEnabled(!checked);
}

void DialComm::on_tcpButton_clicked(bool checked)
{
    ui->baudRateLineEdit->setEnabled(!checked);
    ui->machineIDLineEdit->setEnabled(!checked);
    ui->ipLineEdit->setEnabled(checked);
    ui->portLineEdit->setEnabled(checked);
    ui->serialCombo->setEnabled(!checked);
}

void DialComm::updateSerial()
{
    ui->serialCombo->addItem("");
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        ui->serialCombo->addItem(info.portName());
}

void DialComm::on_udpButton_toggled(bool checked)
{
    if(checked)
        ui->buttonBox->buttons()[0]->setEnabled(true);
}

void DialComm::on_tcpButton_toggled(bool checked)
{
    if(checked)
        ui->buttonBox->buttons()[0]->setEnabled(true);
}

void DialComm::on_serialButton_toggled(bool checked)
{
    bool isSelected;
    if(ui->serialCombo->currentIndex() == 0)
        isSelected = false;
    else
        isSelected = true;
    if(checked)
        ui->buttonBox->buttons()[0]->setEnabled(isSelected);
}

void DialComm::on_serialCombo_currentIndexChanged(int index)
{
    if(index == 0)
        ui->buttonBox->buttons()[0]->setEnabled(false);
    else
        ui->buttonBox->buttons()[0]->setEnabled(true);
}
