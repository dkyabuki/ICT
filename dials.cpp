#include "dials.h"
#include "ui_dials.h"

DialS::DialS(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialS)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

DialS::~DialS()
{
    delete ui;
}
