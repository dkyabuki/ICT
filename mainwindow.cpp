#include "mainwindow.h"
#include "ui_mainwindow.h"


typedef short int (Registers::*sigetter)(void);
sigetter sigetters[14];

typedef bool (Registers::*bgetter)(void);
bgetter bgetters[3];

typedef double (Registers::*dgetter)(void);
dgetter dgetters[12];

typedef void (Registers::*sisetter)(short int);
sisetter sisetters[14];

typedef void (Registers::*bsetter)(bool);
bsetter bsetters[3];

typedef void (Registers::*dsetter)(double);
dsetter dsetters[12];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    bgetters[0] = &Registers::getSensorEnable;
    bgetters[1] = &Registers::getControlEnable;
    bgetters[2] = &Registers::getActuatorEnable;

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

    bsetters[0] = &Registers::setSensorEnable;
    bsetters[1] = &Registers::setControlEnable;
    bsetters[2] = &Registers::setActuatorEnable;

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

    ui->potPlot->setAxisScale(0,-20,20,5);
    ui->potPlot->setAxisScale(2,0,1,0.1);
    ui->torPlot->setAxisScale(0,-2,2,0.5);
    ui->torPlot->setAxisScale(2,0,1,0.1);
    ui->potPlot->setAxisTitle(0,"Tension (V)");
    ui->potPlot->setAxisTitle(2,"Time (s)");
    ui->torPlot->setAxisTitle(0,"Tension (V)");
    ui->torPlot->setAxisTitle(2,"Time (s)");
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(close_program()));
    connect(ui->actionSave_Current_Config, SIGNAL(triggered()), this, SLOT(save_config()));
    connect(ui->actionLoad_Config, SIGNAL(triggered()), this, SLOT(load_config()));
    timepot = 0;
    timetor = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePlotCanvas(){
    Config general_config;
    ui->potPlot->setAxisScale(0,general_config.reg.getPosYMin(),general_config.reg.getPosYMax(),general_config.reg.getPosYStep());
    ui->potPlot->setAxisScale(2,general_config.reg.getPosXMin(),general_config.reg.getPosXMax(),general_config.reg.getPosXStep());
    ui->torPlot->setAxisScale(0,general_config.reg.getTorYMin(),general_config.reg.getTorYMax(),general_config.reg.getTorYStep());
    ui->torPlot->setAxisScale(2,general_config.reg.getTorXMin(),general_config.reg.getTorXMax(),general_config.reg.getTorXStep());
    switch (general_config.reg.getPosPlotUnit()){
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
    switch (general_config.reg.getTorPlotUnit()){
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
    Config general_config;
    QString fileName = QFileDialog::getSaveFileName(this,"","","Impedance Control Config File (*.iccf)");
    QFile file (fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        statusBar()->showMessage("Operation Cancelled or could not open file to save");
        return;
    }
    QTextStream out(&file);

    for (int i = 0; i < NSI; i++){
        out<<"00 "<<i<<" "<<QString::number((general_config.reg.*sigetters[i])())<<"\n";
    }

    for (int i = 0; i < NB; i++){
        out<<"01 "<<i<<" "<<QString::number((general_config.reg.*bgetters[i])())<<"\n";
    }

    for (int i = 0; i < ND; i++){
        out<<"02 "<<i<<" "<<QString::number((general_config.reg.*dgetters[i])())<<"\n";
    }

    file.close();
}

void MainWindow::load_config()
{
    int j;
    Config general_config;
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
            (general_config.reg.*sisetters[j])(list.first().toInt());
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
            (general_config.reg.*bsetters[j])(list.first().toInt());
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
            (general_config.reg.*dsetters[j])(list.first().toDouble());
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

void MainWindow::on_potPlot_itemAttached(QwtPlotItem *plotItem, bool on)
{
    //ui->potPlot->replot();
}

void MainWindow::on_torPlot_itemAttached(QwtPlotItem *plotItem, bool on)
{
    ui->torPlot->replot();
}

void MainWindow::on_pushButton_clicked()
{
    Config genconf;
    double ypos, ytor;
    QwtPlotMarker *pos = new QwtPlotMarker();
    QwtPlotMarker *tor = new QwtPlotMarker();
    pos->setSymbol( new QwtSymbol( QwtSymbol::Diamond, Qt::red, Qt::NoPen, QSize(5,5) ) );
    tor->setSymbol( new QwtSymbol( QwtSymbol::Diamond, Qt::black, Qt::NoPen, QSize(5,5) ) );
    ypos = (qrand()%((int)((genconf.reg.getPosYMax()*100 + 100) - genconf.reg.getPosYMin()*100)) + 100*genconf.reg.getPosYMin())/100.0;
    ytor = (qrand()%((int)((genconf.reg.getTorYMax()*100 + 100) - genconf.reg.getTorYMin()*100)) + 100*genconf.reg.getTorYMin())/100.0;
    pos->setValue(QPointF(timepot, ypos));
    tor->setValue(QPointF(timetor, ytor));
    timepot += 0.002;
    timetor += 0.002;
    pos->attach(ui->potPlot);
    tor->attach(ui->torPlot);
    if (timepot > genconf.reg.getPosXMax())
    {
        timepot -= 0.002;
        timepot -= genconf.reg.getPosXMax();
        ui->potPlot->detachItems(QwtPlotItem::Rtti_PlotItem, true);
    }
    if (timetor > genconf.reg.getTorXMax())
    {
        timetor -= 0.002;
        timetor -= genconf.reg.getTorXMax();
        ui->torPlot->detachItems(QwtPlotItem::Rtti_PlotItem, true);
    }
}
