#include "dialtorplot.h"
#include "ui_dialtorplot.h"

dialTorPlot::dialTorPlot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialTorPlot)
{
    ui->setupUi(this);
}

dialTorPlot::~dialTorPlot()
{
    delete ui;
}
