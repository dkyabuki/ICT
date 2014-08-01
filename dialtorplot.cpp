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
    Config gen_config;
    ui->setupUi(this);
    ui->xmaxLineEdit->setText(QString::number(gen_config.reg.getTorXMax()));
    ui->xminLineEdit->setText(QString::number(gen_config.reg.getTorXMin()));
    ui->ymaxLineEdit->setText(QString::number(gen_config.reg.getTorYMax()));
    ui->yminLineEdit->setText(QString::number(gen_config.reg.getTorYMin()));
    ui->stepSizeXLineEdit->setText(QString::number(gen_config.reg.getTorXStep()));
    ui->stepSizeYLineEdit->setText(QString::number(gen_config.reg.getTorYStep()));
    int unit = gen_config.reg.getTorPlotUnit();
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
    Config gen_conf;
    if(ui->vButton->isChecked()){
        if(ui->vCheck->isChecked()){
            gen_conf.reg.setTorPlotUnit(0);
        } else {
            gen_conf.reg.setTorPlotUnit(1);
        }
    } else {
        if(ui->nmCheck->isChecked()){
            gen_conf.reg.setTorPlotUnit(2);
        } else {
            gen_conf.reg.setTorPlotUnit(3);
        }
    }
    gen_conf.reg.setTorXMax(ui->xmaxLineEdit->text().toDouble());
    gen_conf.reg.setTorYMax(ui->ymaxLineEdit->text().toDouble());
    gen_conf.reg.setTorXMin(ui->xminLineEdit->text().toDouble());
    gen_conf.reg.setTorYMin(ui->yminLineEdit->text().toDouble());
    gen_conf.reg.setTorXStep(ui->stepSizeXLineEdit->text().toDouble());
    gen_conf.reg.setTorYStep(ui->stepSizeYLineEdit->text().toDouble());
    this->close();
}
