#include "dialtorplot.h"
#include "ui_dialtorplot.h"
#include "config.h"
#include "qstring.h"

DialTorPlot::DialTorPlot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialTorPlot)
{
    Qt::WindowFlags flags(Qt::WindowTitleHint);
    this->setWindowFlags(flags);
    ui->setupUi(this);
    ui->xmaxLineEdit->setText(QString::number(Config::reg.getTorXMax()));
    ui->xminLineEdit->setText(QString::number(Config::reg.getTorXMin()));
    ui->ymaxLineEdit->setText(QString::number(Config::reg.getTorYMax()));
    ui->yminLineEdit->setText(QString::number(Config::reg.getTorYMin()));
    ui->stepSizeXLineEdit->setText(QString::number(Config::reg.getTorXStep()));
    ui->stepSizeYLineEdit->setText(QString::number(Config::reg.getTorYStep()));
    int unit = Config::reg.getTorPlotUnit();
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
            ui->nmCheck->setChecked(true);
        } else {
            ui->nmmCheck->setChecked(true);
        }
    }
}

DialTorPlot::~DialTorPlot()
{
    delete ui;
}

void DialTorPlot::on_vButton_clicked()
{
    ui->nmCheck->setEnabled(false);
    ui->nmmCheck->setEnabled(false);
    ui->vCheck->setEnabled(true);
    ui->mvCheck->setEnabled(true);
}

void DialTorPlot::on_physButton_clicked()
{
    ui->nmCheck->setEnabled(true);
    ui->nmmCheck->setEnabled(true);
    ui->vCheck->setEnabled(false);
    ui->mvCheck->setEnabled(false);
}

void DialTorPlot::on_vButton_toggled(bool checked)
{
    if(checked == true){
        ui->nmCheck->setEnabled(false);
        ui->nmmCheck->setEnabled(false);
        ui->vCheck->setEnabled(true);
        ui->mvCheck->setEnabled(true);
    }
}

void DialTorPlot::on_physButton_toggled(bool checked)
{
    if(checked == true){
        ui->nmCheck->setEnabled(true);
        ui->nmmCheck->setEnabled(true);
        ui->vCheck->setEnabled(false);
        ui->mvCheck->setEnabled(false);
    }
}

void DialTorPlot::on_buttonBox_rejected()
{
    this->close();
}

void DialTorPlot::on_buttonBox_accepted()
{
    if(ui->vButton->isChecked()){
        if(ui->vCheck->isChecked()){
            Config::reg.setTorPlotUnit(0);
        } else {
            Config::reg.setTorPlotUnit(1);
        }
    } else {
        if(ui->nmCheck->isChecked()){
            Config::reg.setTorPlotUnit(2);
        } else {
            Config::reg.setTorPlotUnit(3);
        }
    }
    Config::reg.setTorXMax(ui->xmaxLineEdit->text().toDouble());
    Config::reg.setTorYMax(ui->ymaxLineEdit->text().toDouble());
    Config::reg.setTorXMin(ui->xminLineEdit->text().toDouble());
    Config::reg.setTorYMin(ui->yminLineEdit->text().toDouble());
    Config::reg.setTorXStep(ui->stepSizeXLineEdit->text().toDouble());
    Config::reg.setTorYStep(ui->stepSizeYLineEdit->text().toDouble());
    this->close();
}
