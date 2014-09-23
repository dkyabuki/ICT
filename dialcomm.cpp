#include "dialcomm.h"
#include "ui_dialcomm.h"

DialComm::DialComm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialComm)
{
    ui->setupUi(this);
}

DialComm::~DialComm()
{
    delete ui;
}
