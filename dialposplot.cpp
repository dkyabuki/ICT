#include "dialposplot.h"
#include "ui_dialposplot.h"

DialPosPlot::DialPosPlot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialPosPlot)
{
    ui->setupUi(this);
}

DialPosPlot::~DialPosPlot()
{
    delete ui;
}
