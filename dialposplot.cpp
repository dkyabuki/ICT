#include "dialposplot.h"
#include "ui_dialposplot.h"
#include "config.h"
#include <qstring.h>

DialPosPlot::DialPosPlot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialPosPlot)
{
    Qt::WindowFlags flags(Qt::WindowTitleHint);
    this->setWindowFlags(flags);
    ui->setupUi(this);
    ui->xmaxLineEdit->setText(QString::number(Config::reg.getPosXMax()));
    ui->xminLineEdit->setText(QString::number(Config::reg.getPosXMin()));
    ui->ymaxLineEdit->setText(QString::number(Config::reg.getPosYMax()));
    ui->yminLineEdit->setText(QString::number(Config::reg.getPosYMin()));
    ui->stepSizeXLineEdit->setText(QString::number(Config::reg.getPosXStep()));
    ui->stepSizeYLineEdit->setText(QString::number(Config::reg.getPosYStep()));
    int unit = Config::reg.getPosPlotUnit();
    if(unit <= 1){
        ui->vButton->setChecked(true);
        if(unit == 0){
            ui->vCheck->setChecked(true);
        } else {
            ui->mvCheck->setChecked(true);
        }
    } else {
        ui->physButton->setChecked(true);
        if(unit == 2){
            ui->degCheck->setChecked(true);
        } else {
            ui->radCheck->setChecked(true);
        }
    }
}

DialPosPlot::~DialPosPlot()
{
    delete ui;
}

void DialPosPlot::on_physButton_clicked()
{
    ui->degCheck->setEnabled(true);
    ui->radCheck->setEnabled(true);
    ui->vCheck->setEnabled(false);
    ui->mvCheck->setEnabled(false);
}

void DialPosPlot::on_vButton_clicked()
{
    ui->degCheck->setEnabled(false);
    ui->radCheck->setEnabled(false);
    ui->vCheck->setEnabled(true);
    ui->mvCheck->setEnabled(true);
}

void DialPosPlot::on_vButton_toggled(bool checked)
{
    if(checked == true){
        ui->degCheck->setEnabled(false);
        ui->radCheck->setEnabled(false);
        ui->vCheck->setEnabled(true);
        ui->mvCheck->setEnabled(true);
    }
}

void DialPosPlot::on_physButton_toggled(bool checked)
{
    if(checked == true){
        ui->degCheck->setEnabled(true);
        ui->radCheck->setEnabled(true);
        ui->vCheck->setEnabled(false);
        ui->mvCheck->setEnabled(false);
    }
}

void DialPosPlot::on_buttonBox_rejected()
{
    this->close();
}

void DialPosPlot::on_buttonBox_accepted()
{
    if(ui->vButton->isChecked()){
        if(ui->vCheck->isChecked()){
            Config::reg.setPosPlotUnit(0);
        } else {
            Config::reg.setPosPlotUnit(1);
        }
    } else {
        if(ui->degCheck->isChecked()){
            Config::reg.setPosPlotUnit(2);
        } else {
            Config::reg.setPosPlotUnit(3);
        }
    }
    Config::reg.setPosXMax(ui->xmaxLineEdit->text().toDouble());
    Config::reg.setPosYMax(ui->ymaxLineEdit->text().toDouble());
    Config::reg.setPosXMin(ui->xminLineEdit->text().toDouble());
    Config::reg.setPosYMin(ui->yminLineEdit->text().toDouble());
    Config::reg.setPosXStep(ui->stepSizeXLineEdit->text().toDouble());
    Config::reg.setPosYStep(ui->stepSizeYLineEdit->text().toDouble());
}
