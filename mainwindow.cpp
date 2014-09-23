#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmath.h>
#include <QtSerialPort/QSerialPort>

typedef short int (Registers::*sigetter)(void);
sigetter sigetters[15];

typedef bool (Registers::*bgetter)(void);
bgetter bgetters[6];

typedef double (Registers::*dgetter)(void);
dgetter dgetters[13];

typedef void (Registers::*sisetter)(short int);
sisetter sisetters[15];

typedef void (Registers::*bsetter)(bool);
bsetter bsetters[6];

typedef void (Registers::*dsetter)(double);
dsetter dsetters[13];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //INICIALIZACAO DE MEMBROS
    sigetters[0] = &Registers::getMonitoring;
    sigetters[1] = &Registers::getSensoring;
    sigetters[2] = &Registers::getTrajectory;
    sigetters[3] = &Registers::getSensorPriority;
    sigetters[4] = &Registers::getSensorPeriod;
    sigetters[5] = &Registers::getControlPriority;
    sigetters[6] = &Registers::getControlPeriod;
    sigetters[7] = &Registers::getActuatorPriority;
    sigetters[8] = &Registers::getActuatorPeriod;
    sigetters[9] = &Registers::getSerialPriority;
    sigetters[10] = &Registers::getSerialPeriod;
    sigetters[11] = &Registers::getMode;
    sigetters[12] = &Registers::getPosPlotUnit;
    sigetters[13] = &Registers::getTorPlotUnit;
    sigetters[14] = &Registers::getMachineId;

    bgetters[0] = &Registers::getSensorEnable;
    bgetters[1] = &Registers::getControlEnable;
    bgetters[2] = &Registers::getActuatorEnable;
    bgetters[3] = &Registers::getSerial;
    bgetters[4] = &Registers::getTCP;
    bgetters[5] = &Registers::getUDP;

    dgetters[0] = &Registers::getPosXMax;
    dgetters[1] = &Registers::getPosYMax;
    dgetters[2] = &Registers::getTorXMax;
    dgetters[3] = &Registers::getTorYMax;
    dgetters[4] = &Registers::getPosXMin;
    dgetters[5] = &Registers::getPosYMin;
    dgetters[6] = &Registers::getTorXMin;
    dgetters[7] = &Registers::getTorXMin;
    dgetters[8] = &Registers::getPosXStep;
    dgetters[9] = &Registers::getTorXStep;
    dgetters[10] = &Registers::getPosYStep;
    dgetters[11] = &Registers::getPosYStep;
    dgetters[12] = &Registers::getBaud;

    sisetters[0] = &Registers::setMonitoring;
    sisetters[1] = &Registers::setSensoring;
    sisetters[2] = &Registers::setTrajectory;
    sisetters[3] = &Registers::setSensorPriority;
    sisetters[4] = &Registers::setSensorPeriod;
    sisetters[5] = &Registers::setControlPriority;
    sisetters[6] = &Registers::setControlPeriod;
    sisetters[7] = &Registers::setActuatorPriority;
    sisetters[8] = &Registers::setActuatorPeriod;
    sisetters[9] = &Registers::setSerialPriority;
    sisetters[10] = &Registers::setSerialPeriod;
    sisetters[11] = &Registers::setMode;
    sisetters[12] = &Registers::setPosPlotUnit;
    sisetters[13] = &Registers::setTorPlotUnit;
    sisetters[14] = &Registers::setMachineId;

    bsetters[0] = &Registers::setSensorEnable;
    bsetters[1] = &Registers::setControlEnable;
    bsetters[2] = &Registers::setActuatorEnable;
    bsetters[3] = &Registers::setSerial;
    bsetters[4] = &Registers::setTCP;
    bsetters[5] = &Registers::setUDP;

    dsetters[0] = &Registers::setPosXMax;
    dsetters[1] = &Registers::setPosYMax;
    dsetters[2] = &Registers::setTorXMax;
    dsetters[3] = &Registers::setTorYMax;
    dsetters[4] = &Registers::setPosXMin;
    dsetters[5] = &Registers::setPosYMin;
    dsetters[6] = &Registers::setTorXMin;
    dsetters[7] = &Registers::setTorXMin;
    dsetters[8] = &Registers::setPosXStep;
    dsetters[9] = &Registers::setTorXStep;
    dsetters[10] = &Registers::setPosYStep;
    dsetters[11] = &Registers::setPosYStep;
    dsetters[12] = &Registers::setBaud;

    running = false;
    timepot = 0;
    timetor = 0;
    red.setColor(QPalette::WindowText,Qt::red);
    black.setColor(QPalette::WindowText,Qt::black);
    samplingThread = new SamplingThread(this);

    ui->potPlot->setAxisScale(0,-20,20,5);
    ui->potPlot->setAxisScale(2,0,1,0.1);
    ui->torPlot->setAxisScale(0,-2,2,0.5);
    ui->torPlot->setAxisScale(2,0,1,0.1);
    ui->potPlot->setAxisTitle(0,"Tension (V)");
    ui->potPlot->setAxisTitle(2,"Time (s)");
    ui->torPlot->setAxisTitle(0,"Tension (V)");
    ui->torPlot->setAxisTitle(2,"Time (s)");

    ui->connectionLabel->setPalette(red);
    ui->ipLabel->setPalette(red);
    ui->portLabel->setPalette(red);

    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(close_program()));
    connect(ui->actionSave_Current_Config, SIGNAL(triggered()), this, SLOT(save_config()));
    connect(ui->actionLoad_Config, SIGNAL(triggered()), this, SLOT(load_config()));
    connect(this, SIGNAL(on_controlStartup(bool)), this, SLOT(control_signal_emitted(bool)),Qt::DirectConnection);
    connect(this, SIGNAL(on_controlPause(bool)), this, SLOT(control_pause_signal_emitted(bool)),Qt::DirectConnection);
    connect(samplingThread, SIGNAL(showMsg(QString)), this, SLOT(show_error(QString)),Qt::QueuedConnection);
    connect(samplingThread, SIGNAL(updateGUI(QStringList)), this, SLOT(update_connection(QStringList)));
    connect(samplingThread, SIGNAL(pointAppendedPot(QPointF)), this, SLOT(append_pos(const QPointF)),Qt::QueuedConnection);
    connect(samplingThread, SIGNAL(pointAppendedExt(QPointF)), this, SLOT(append_ext(const QPointF)),Qt::QueuedConnection);
    connect(this, SIGNAL(on_controlPause(bool)),samplingThread,SLOT(pause(bool)),Qt::QueuedConnection);
    connect(this, SIGNAL(comm_config(QHostAddress,quint16)), samplingThread, SLOT(commConfig(QHostAddress,quint16)));
    emit on_controlStartup(false);
}

MainWindow::~MainWindow()
{
    samplingThread->stop();
    delete ui;
}

void MainWindow::updatePlotCanvas(){
    ui->potPlot->setAxisScale(0,Config::reg.getPosYMin(),Config::reg.getPosYMax(),Config::reg.getPosYStep());
    ui->potPlot->setAxisScale(2,Config::reg.getPosXMin(),Config::reg.getPosXMax(),Config::reg.getPosXStep());
    ui->torPlot->setAxisScale(0,Config::reg.getTorYMin(),Config::reg.getTorYMax(),Config::reg.getTorYStep());
    ui->torPlot->setAxisScale(2,Config::reg.getTorXMin(),Config::reg.getTorXMax(),Config::reg.getTorXStep());
    switch (Config::reg.getPosPlotUnit()){
    case 0:
        ui->potPlot->setAxisTitle(0, "Tension (V)");
        break;
    case 1:
        ui->potPlot->setAxisTitle(0, "Tension (mV)");
        break;
    case 2:
        ui->potPlot->setAxisTitle(0, "Angular Position (Deg)");
        break;
    case 3:
        ui->potPlot->setAxisTitle(0, "Angular Position (Rad)");
        break;
    }
    switch (Config::reg.getTorPlotUnit()){
    case 0:
        ui->torPlot->setAxisTitle(0, "Tension (V)");
        break;
    case 1:
        ui->torPlot->setAxisTitle(0, "Tension (mV)");
        break;
    case 2:
        ui->torPlot->setAxisTitle(0, "Torque (N.m)");
        break;
    case 3:
        ui->torPlot->setAxisTitle(0, "Torque (N.mm)");
        break;
    }
    ui->potPlot->updateAxes();
    ui->torPlot->updateAxes();
    ui->potPlot->replot();
    ui->torPlot->replot();
}

void MainWindow::append_pos(const QPointF &point)
{
    ui->potPlot->appendPoint(point);
    if((double)point.x()>ui->potPlot->axisInterval(2).maxValue())
    {
        double min = ui->potPlot->axisInterval(2).maxValue();
        double max = ui->potPlot->axisInterval(2).maxValue()*2 - ui->potPlot->axisInterval(2).minValue();
        ui->potPlot->setAxisScale(2, min, max, Config::reg.getPosXStep());
        ui->potPlot->replot();
    }
}

void MainWindow::append_ext(const QPointF &point)
{
    ui->torPlot->appendPoint(point);
    if((double)point.x()>ui->torPlot->axisInterval(2).maxValue())
    {
        double min = ui->torPlot->axisInterval(2).maxValue();
        double max = ui->torPlot->axisInterval(2).maxValue()*2 - ui->torPlot->axisInterval(2).minValue();
        ui->torPlot->setAxisScale(2, min, max, Config::reg.getTorXStep());
        ui->torPlot->replot();
    }
}

void MainWindow::show_error(QString str)
{
    ui->statusBar->showMessage(str);
}

void MainWindow::update_connection(QStringList str)
{
    if(str.size() != 3){
        ui->statusBar->showMessage("Error in GUI update - Connection: size of the config stringlist is larger than 3");
        return;
    }

    for(int i = 0; i < str.size(); i++)
    {
        switch(i)
        {
        case 0:
            ui->connectionLabel->setText(str[i]);
            if(QString::compare(str[i],"Disconnected",Qt::CaseInsensitive) != 0)
                ui->connectionLabel->setPalette(black);
            else
                ui->connectionLabel->setPalette(red);
            break;
        case 1:
            ui->ipLabel->setText(str[i]);
            if(QString::compare(str[i],"-",Qt::CaseInsensitive) != 0)
                ui->ipLabel->setPalette(black);
            else
                ui->ipLabel->setPalette(red);
            break;
        case 2:
            ui->portLabel->setText(str[i]);
            if(QString::compare(str[i],"-",Qt::CaseInsensitive) != 0)
                ui->portLabel->setPalette(black);
            else
                ui->portLabel->setPalette(red);
        }
    }
}


void MainWindow::control_signal_emitted(bool on)
{
    ui->connButton->setEnabled(!on);
    ui->controlStartButton->setEnabled(!on);
    ui->convButton->setEnabled(!on);
    ui->driverConfigButton->setEnabled(!on);
    ui->driverPlayPauseButton->setEnabled(!on);
    ui->modeButton->setEnabled(!on);
    ui->posConfigButton->setEnabled(!on);
    ui->torConfigButton->setEnabled(!on);
    ui->posSaveButton->setEnabled(!on);
    ui->torSaveButton->setEnabled(!on);
    ui->pushButton->setEnabled(!on);
    ui->regButton->setEnabled(!on);
    ui->taskButton->setEnabled(!on);
    ui->controlPauseButton->setEnabled(on);
    ui->controlStopButton->setEnabled(on);
    ui->menuBar->setEnabled(!on);
    running = on;
}

void MainWindow::control_pause_signal_emitted(bool on)
{
    ui->posConfigButton->setEnabled(on);
    ui->torConfigButton->setEnabled(on);
    ui->posSaveButton->setEnabled(on);
    ui->torSaveButton->setEnabled(on);
    ui->controlStopButton->setEnabled(!on);
    ui->controlPauseButton->setText(on? "Continue":"Pause");
    running = !on;
}

void MainWindow::close_program(){
    DialQuit dialq;
    dialq.setModal(true);
    dialq.exec();
    if(dialq.getAnswer())
        this->close();
}

void MainWindow::save_config()
{
    QString fileName = QFileDialog::getSaveFileName(this,"","","Impedance Control Config File (*.iccf)");
    QFile file (fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        statusBar()->showMessage("Operation Cancelled or could not open file to save");
        return;
    }
    QTextStream out(&file);

    for (int i = 0; i < NSI; i++){
        out<<"00 "<<i<<" "<<QString::number((Config::reg.*sigetters[i])())<<"\n";
    }

    for (int i = 0; i < NB; i++){
        out<<"01 "<<i<<" "<<QString::number((Config::reg.*bgetters[i])())<<"\n";
    }

    for (int i = 0; i < ND; i++){
        out<<"02 "<<i<<" "<<QString::number((Config::reg.*dgetters[i])())<<"\n";
    }

    file.close();
}

void MainWindow::load_config()
{
    int j;
    QString fileName = QFileDialog::getOpenFileName(this,"","","Impedance Control Config File (*.iccf)");
    QFile file (fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        statusBar()->showMessage("Operation cancelled or could not open file to load");
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
        case 00:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            j = list.first().toInt();
            list.pop_front();
            (Config::reg.*sisetters[j])(list.first().toInt());
            break;
        case 01:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            j = list.first().toInt();
            list.pop_front();
            (Config::reg.*bsetters[j])(list.first().toInt());
            break;
        case 02:
            list.pop_front();
            if (list.empty())
            {
                ui->statusBar->showMessage("Incomplete line in selected file");
                return;
            }
            j = list.first().toInt();
            list.pop_front();
            (Config::reg.*dsetters[j])(list.first().toDouble());
            break;
        }
        line = in.readLine();
    }
    file.close();
    updatePlotCanvas();
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
    QString fileName = QFileDialog::getSaveFileName(this,"","","Text File (*.txt)");
    QFile file (fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for(int i = 0; i < ui->potPlot->size(); i++)
    {
        out<<i<<"\t"<<ui->potPlot->dataSample(i).x()<<"\t"<<ui->potPlot->dataSample(i).y()<<"\n";
    }
    file.close();
}

void MainWindow::on_torSaveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,"","","Text File (*.txt)");
    QFile file (fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for(int i = 0; i < ui->torPlot->size(); i++)
    {
        out<<i<<"\t"<<ui->torPlot->dataSample(i).x()<<"\t"<<ui->torPlot->dataSample(i).y()<<"\n";
    }
    file.close();
}

void MainWindow::on_torConfigButton_clicked()
{
    DialTorPlot torplotdialog;
    torplotdialog.setModal(true);
    torplotdialog.exec();
    updatePlotCanvas();
}

void MainWindow::on_posConfigButton_clicked()
{
    DialPosPlot posplotdialog;
    posplotdialog.setModal(true);
    posplotdialog.exec();
    updatePlotCanvas();
}

void MainWindow::on_pushButton_clicked()
{
    double ypos, ytor;
//    ypos = (qrand()%((int)((Config::reg.getPosYMax()*100 + 100) - Config::reg.getPosYMin()*100)) + 100*Config::reg.getPosYMin())/100.0;
//    ytor = (qrand()%((int)((Config::reg.getTorYMax()*100 + 100) - Config::reg.getTorYMin()*100)) + 100*Config::reg.getTorYMin())/100.0;
    ypos = ((Config::reg.getPosYMax() - Config::reg.getPosYMin())/2)*qSin(timepot*25)+(Config::reg.getPosYMax() + Config::reg.getPosYMin())/2;
    ytor = ((Config::reg.getTorYMax() - Config::reg.getTorYMin())/2)*qSin(timetor*25)+(Config::reg.getTorYMax() + Config::reg.getTorYMin())/2;
    timepot += 0.002;
    timetor += 0.002;
    ui->potPlot->appendPoint(QPointF(timepot, ypos));
    ui->torPlot->appendPoint(QPointF(timetor, ytor));
    if (timepot > Config::reg.getPosXMax())
    {
        timepot -= 0.002;
        timepot -= Config::reg.getPosXMax();
        ui->potPlot->clearPoints();
    }
    if (timetor > Config::reg.getTorXMax())
    {
        timetor -= 0.002;
        timetor -= Config::reg.getTorXMax();
        ui->torPlot->clearPoints();
    }
}

void MainWindow::on_controlStartButton_clicked()
{
    if((ui->potPlot->size()>0) | (ui->torPlot->size()>0))
    {
        ui->potPlot->clearPoints();
        ui->torPlot->clearPoints();
    }
    updatePlotCanvas();
    emit on_controlStartup(true);
    samplingThread->setInterval(1);
    samplingThread->initiate();
}

void MainWindow::on_controlPauseButton_clicked()
{
    emit on_controlPause(running);
}

void MainWindow::on_controlStopButton_clicked()
{
    emit on_controlStartup(false);
    samplingThread->halt();
}

