#include "dialm.h"
#include "ui_dialm.h"

Dialm::Dialm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialm)
{
    ui->setupUi(this);
    Config general_config;
    if (general_config.reg.getMode() == 0)
    {
        ui->posModeButton->setChecked(true);
    }
    else
    {
        ui->torModeButton->setChecked(true);
    }
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

Dialm::~Dialm()
{
    delete ui;
}

void Dialm::on_buttonBox_accepted()
{
    Config general_config;
    if(ui->posModeButton->isChecked())
    {
        general_config.reg.setMode(0);
    }
    else
    {
        general_config.reg.setMode(1);
    }
}
