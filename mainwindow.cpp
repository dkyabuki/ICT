#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "dialt.h"
#include "dialr.h"
#include "dialm.h"
#include "dialogc.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QAction>
#include <QString>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionSave_Current_Config, SIGNAL(triggered()), this, SLOT(save_config()));
    connect(ui->actionLoad_Config, SIGNAL(triggered()), this, SLOT(load_config()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::save_config()
{
    Config general_config;
    QString fileName = QFileDialog::getSaveFileName(this,"","","Impedance Control Config File (*.iccf)");
    QFile file (fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        statusBar()->showMessage("Could not open file to save");
        return;
    }
    QTextStream out(&file);
    out<<"01 "<<QString::number(general_config.reg.getMonitoring())<<"\n";
    out<<"02 "<<QString::number(general_config.reg.getSensoring())<<"\n";
    out<<"03 "<<QString::number(general_config.reg.getTrajectory())<<"\n";
    out<<"04 "<<QString::number(general_config.reg.getSensorEnable())<<"\n";
    out<<"05 "<<QString::number(general_config.reg.getSensorPeriod())<<"\n";
    out<<"06 "<<QString::number(general_config.reg.getSensorPriority())<<"\n";
    out<<"07 "<<QString::number(general_config.reg.getControlEnable())<<"\n";
    out<<"08 "<<QString::number(general_config.reg.getControlPeriod())<<"\n";
    out<<"09 "<<QString::number(general_config.reg.getControlPriority())<<"\n";
    out<<"10 "<<QString::number(general_config.reg.getActuatorEnable())<<"\n";
    out<<"11 "<<QString::number(general_config.reg.getActuatorPeriod())<<"\n";
    out<<"12 "<<QString::number(general_config.reg.getActuatorPriority())<<"\n";
    out<<"13 "<<QString::number(general_config.reg.getSerialPeriod())<<"\n";
    out<<"14 "<<QString::number(general_config.reg.getSerialPriority())<<"\n";
    out<<"15 "<<QString::number(general_config.reg.getMode())<<"\n";
    file.close();
}

void MainWindow::load_config()
{
    Config general_config;
    QString fileName = QFileDialog::getOpenFileName(this,"","","Impedance Control Config File (*.iccf)");
    QFile file (fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        statusBar()->showMessage("Could not open config file");
        return;
    }
    QTextStream in(&file);
    QString line = in.readLine();
    while(!line.isNull())
    {
        QStringList list = line.split(" ");
        if (list.empty())
        {
            ui->statusBar->showMessage("Empty line in selected file");
            return;
        }
        switch(list.first().toInt())
        {
        case 1:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setMonitoring(list.first().toInt());
            break;
        case 2:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setSensoring(list.first().toInt());
            break;
        case 3:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setTrajectory(list.first().toInt());
            break;
        case 4:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setSensorEnable(list.first().toInt());
            break;
        case 5:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setSensorPeriod(list.first().toInt());
            break;
        case 6:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setSensorPriority(list.first().toInt());
            break;
        case 7:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setControlEnable(list.first().toInt());
            break;
        case 8:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setControlPeriod(list.first().toInt());
            break;
        case 9:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setControlPriority(list.first().toInt());
            break;
        case 10:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setActuatorEnable(list.first().toInt());
            break;
        case 11:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setActuatorPeriod(list.first().toInt());
            break;
        case 12:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setActuatorPriority(list.first().toInt());
            break;
        case 13:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setSerialPeriod(list.first().toInt());
            break;
        case 14:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setSerialPriority(list.first().toInt());
            break;
        case 15:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            general_config.reg.setMode(list.first().toInt());
            break;
        }
        line = in.readLine();

    }
    file.close();
}

void MainWindow::on_taskButton_clicked()
{
    Dialt taskdialog;
    taskdialog.setModal(true);
    taskdialog.exec();
}

void MainWindow::on_convButton_clicked()
{
    Dialogc conversordialog;
    conversordialog.setModal(true);
    conversordialog.exec();
}

void MainWindow::on_regButton_clicked()
{
    Dialr registerdialog;
    registerdialog.setModal(true);
    registerdialog.exec();
}



void MainWindow::on_modeButton_clicked()
{
    Dialm modedialog;
    modedialog.setModal(true);
    modedialog.exec();
}

void MainWindow::on_posSaveButton_clicked()
{
    int n = 3;
    QString fileName = QFileDialog::getSaveFileName(this);
    QFile file (fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for(int i = 0; i < n; i++)
    {

    }
    file.close();
}

void MainWindow::on_torSaveButton_clicked()
{
    int n = 3;
    QString fileName = QFileDialog::getSaveFileName(this);
    QFile file (fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for(int i = 0; i < n; i++)
    {

    }
    file.close();
}
