#include "registers.h"

Registers::Registers() //inicializa registros na configuração padrão
{
    MONITORING = 0;
    SENSORING = 0;
    TRAJECTORY = 0;
    SENSOR_PRIORITY = 100;
    SENSOR_PERIOD = 2;
    CONTROL_PRIORITY = 100;
    CONTROL_PERIOD = 2;
    ACTUATOR_PRIORITY = 100;
    ACTUATOR_PERIOD = 2;
    SERIAL_PRIORITY = 100;
    SERIAL_PERIOD = 2;
    MODE = 0;
    POS_PLOT_UNIT = 0;
    TOR_PLOT_UNIT = 0;

    SENSOR_ENABLE = 1;
    CONTROL_ENABLE = 1;
    ACTUATOR_ENABLE = 1;

    POS_X_MAX = 1;
    POS_Y_MAX = 20;
    TOR_X_MAX = 1;
    TOR_Y_MAX = 2;
    POS_X_MIN = 0;
    POS_Y_MIN = -20;
    TOR_X_MIN = 0;
    TOR_Y_MIN = -2;
    POS_X_STEP = 0.1;
    TOR_X_STEP = 0.1;
    POS_Y_STEP = 5;
    TOR_Y_STEP = 0.5;

    MACHINE_ID = 1;
    BAUD = 115200;

    SERIAL_ON = true;
    UDP_ON = false;
    TCP_ON = false;

    PORT = 45454;
    IP = "127.0.0.1";
    SERIAL_PORT = "";
}

Registers::~Registers()
{
}

/*************************************/
/*              GETTERS              */
/*************************************/

short int Registers::getMonitoring ()
{
    return (MONITORING);
}

short int Registers::getSensoring ()
{
    return (SENSORING);
}

short int Registers::getTrajectory ()
{
    return (TRAJECTORY);
}

short int Registers::getSensorPriority()
{
    return (SENSOR_PRIORITY);
}

short int Registers::getSensorPeriod()
{
    return (SENSOR_PERIOD);
}

bool Registers::getSensorEnable()
{
    return (SENSOR_ENABLE);
}

short int Registers::getControlPriority()
{
    return (CONTROL_PRIORITY);
}

short int Registers::getControlPeriod()
{
    return (CONTROL_PERIOD);
}

bool Registers::getControlEnable()
{
    return (CONTROL_ENABLE);
}

short int Registers::getActuatorPriority()
{
    return (ACTUATOR_PRIORITY);
}

short int Registers::getActuatorPeriod()
{
    return (ACTUATOR_PERIOD);
}

bool Registers::getActuatorEnable()
{
    return (ACTUATOR_ENABLE);
}

short int Registers::getSerialPriority()
{
    return (SERIAL_PRIORITY);
}

short int Registers::getSerialPeriod()
{
    return (SERIAL_PERIOD);
}

short int Registers::getMode()
{
    return(MODE);
}

short int Registers::getPosPlotUnit(){
    return(POS_PLOT_UNIT);
}

short int Registers::getTorPlotUnit(){
    return(TOR_PLOT_UNIT);
}

double Registers::getPosXMax(){
    return(POS_X_MAX);
}

double Registers::getPosYMax(){
    return(POS_Y_MAX);
}

double Registers::getTorXMax(){
    return(TOR_X_MAX);
}

double Registers::getTorYMax(){
    return(TOR_Y_MAX);
}

double Registers::getPosXMin(){
    return(POS_X_MIN);
}

double Registers::getPosYMin(){
    return(POS_Y_MIN);
}

double Registers::getTorXMin(){
    return(TOR_X_MIN);
}

double Registers::getTorYMin(){
    return(TOR_Y_MIN);
}

double Registers::getPosXStep(){
    return(POS_X_STEP);
}

double Registers::getTorXStep(){
    return(TOR_X_STEP);
}

double Registers::getPosYStep(){
    return(POS_Y_STEP);
}

double Registers::getTorYStep(){
    return(TOR_Y_STEP);
}

short int Registers::getMachineId(){
    return(MACHINE_ID);
}

double Registers::getBaud(){
    return(BAUD);
}

bool Registers::getSerialOn(){
    return(SERIAL_ON);
}

bool Registers::getUdpOn(){
    return(UDP_ON);
}

bool Registers::getTcpOn(){
    return(TCP_ON);
}

int Registers::getPort(){
    return(PORT);
}

QString Registers::getIp(){
    return(IP);
}

QString Registers::getSerialPort(){
    return(SERIAL_PORT);
}

/*************************************/
/*              SETTERS              */
/*************************************/

void Registers::setMonitoring (short int v){
    MONITORING = v;
}

void Registers::setSensoring (short int v)
{
    SENSORING = v;
}

void Registers::setTrajectory (short int v)
{
    TRAJECTORY = v;
}

void Registers::setSensorPriority(short int v)
{
    SENSOR_PRIORITY = v;
}

void Registers::setSensorPeriod(short int v)
{
    SENSOR_PERIOD = v;
}

void Registers::setSensorEnable(bool v)
{
    SENSOR_ENABLE = v;
}

void Registers::setControlPriority(short int v)
{
    CONTROL_PRIORITY = v;
}

void Registers::setControlPeriod(short int v)
{
    CONTROL_PERIOD = v;
}

void Registers::setControlEnable(bool v)
{
    CONTROL_ENABLE = v;
}

void Registers::setActuatorPriority(short int v)
{
    ACTUATOR_PRIORITY = v;
}

void Registers::setActuatorPeriod(short int v)
{
    ACTUATOR_PERIOD = v;
}

void Registers::setActuatorEnable(bool v)
{
    ACTUATOR_ENABLE = v;
}

void Registers::setSerialPriority(short int v)
{
    SERIAL_PRIORITY = v;
}

void Registers::setSerialPeriod(short int v)
{
    SERIAL_PERIOD = v;
}

void Registers::setMode(short int v)
{
    MODE = v;
}

void Registers::setPosPlotUnit(short int v){
    POS_PLOT_UNIT = v;
}

void Registers::setTorPlotUnit(short int v){
    TOR_PLOT_UNIT = v;
}

void Registers::setPosXMax(double v){
    POS_X_MAX = v;
}

void Registers::setPosYMax(double v){
    POS_Y_MAX = v;
}

void Registers::setTorXMax(double v){
    TOR_X_MAX = v;
}

void Registers::setTorYMax(double v){
    TOR_Y_MAX = v;
}

void Registers::setPosXMin(double v){
    POS_X_MIN = v;
}

void Registers::setPosYMin(double v){
    POS_Y_MIN = v;
}

void Registers::setTorXMin(double v){
    TOR_X_MIN = v;
}

void Registers::setTorYMin(double v){
    TOR_Y_MIN = v;
}

void Registers::setPosXStep(double v){
    POS_X_STEP = v;
}

void Registers::setTorXStep(double v){
    TOR_X_STEP = v;
}

void Registers::setPosYStep(double v){
    POS_Y_STEP = v;
}

void Registers::setTorYStep(double v){
    TOR_Y_STEP = v;
}

void Registers::setMachineId(short int v){
    MACHINE_ID = v;
}

void Registers::setBaud(double v){
    BAUD = v;
}

void Registers::setSerialOn(bool v){
    SERIAL_ON = v;
}

void Registers::setUdpOn(bool v){
    UDP_ON = v;
}

void Registers::setTcpOn(bool v){
    TCP_ON = v;
}

void Registers::setPort(int v){
    PORT = v;
}

void Registers::setIp(QString v){
    IP = v;
}

void Registers::setSerialPort(QString v){
    SERIAL_PORT = v;
}
