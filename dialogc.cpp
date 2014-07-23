#include "dialogc.h"
#include "ui_dialogc.h"

Dialogc::Dialogc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogc)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

Dialogc::~Dialogc()
{
    delete ui;
}
