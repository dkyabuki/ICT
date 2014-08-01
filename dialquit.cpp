#include "dialquit.h"
#include "ui_dialquit.h"
#include <QMessageBox>

DialQuit::DialQuit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialQuit)
{
    ui->setupUi(this);
    Qt::WindowFlags flags(Qt::WindowTitleHint);
    this->setWindowFlags(flags);
}

DialQuit::~DialQuit()
{
    delete ui;
}

void DialQuit::on_buttonBox_accepted()
{
    quitProgram = true;
}

void DialQuit::on_buttonBox_rejected()
{
    quitProgram = false;
}

bool DialQuit::getAnswer(){
    return (quitProgram);
}
