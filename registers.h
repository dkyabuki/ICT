#ifndef REGISTERS_H
#define REGISTERS_H

#define NSI     14
#define NB      5
#define ND      13
#define NI      1
#define NST     2

#include <QString>
#include <QtNetwork>

class Registers
{
public:

    Registers();
    ~Registers();

    short int getMonitoring ();
    short int getSensoring ();
    short int getTrajectory ();

    short int getSensorPriority();
    short int getSensorPeriod();
    bool getSensorEnable();

    short int getControlPriority();
    short int getControlPeriod();
    bool getControlEnable();

    short int getActuatorPriority();
    short int getActuatorPeriod();
    bool getActuatorEnable();

    short int getSerialPriority();
    short int getSerialPeriod();

    short int getPosPlotUnit();
    short int getTorPlotUnit();
    double getPosXMax();
    double getPosYMax();
    double getTorXMax();
    double getTorYMax();
    double getPosXMin();
    double getPosYMin();
    double getTorXMin();
    double getTorYMin();
    double getPosXStep();
    double getTorXStep();
    double getPosYStep();
    double getTorYStep();

    short int getMachineId();
    double getBaud();

    bool getSerialOn();
    bool getUdpOn();

    int getPort();

    QString getIp();
    QString getSerialPort();

    void setMonitoring (short int v);
    void setSensoring (short int v);
    void setTrajectory (short int v);

    void setSensorPriority(short int v);
    void setSensorPeriod(short int v);
    void setSensorEnable(bool v);

    void setControlPriority(short int v);
    void setControlPeriod(short int v);
    void setControlEnable(bool v);

    void setActuatorPriority(short int v);
    void setActuatorPeriod(short int v);
    void setActuatorEnable(bool v);

    void setSerialPriority(short int v);
    void setSerialPeriod(short int v);

    void setPosPlotUnit(short int v);
    void setTorPlotUnit(short int v);
    void setPosXMax(double v);
    void setPosYMax(double v);
    void setTorXMax(double v);
    void setTorYMax(double v);
    void setPosXMin(double v);
    void setPosYMin(double v);
    void setTorXMin(double v);
    void setTorYMin(double v);
    void setPosXStep(double v);
    void setTorXStep(double v);
    void setPosYStep(double v);
    void setTorYStep(double v);

    void setMachineId(short int v);
    void setBaud(double v);

    void setSerialOn(bool v);
    void setUdpOn(bool v);

    void setPort(int v);

    void setIp(QString v);
    void setSerialPort(QString v);

private:

    //Short Int = 15
    short int MONITORING;        //0
    short int SENSORING;         //1
    short int TRAJECTORY;        //2
    short int SENSOR_PRIORITY;   //3
    short int SENSOR_PERIOD;     //4
    short int CONTROL_PRIORITY;  //5
    short int CONTROL_PERIOD;    //6
    short int ACTUATOR_PRIORITY; //7
    short int ACTUATOR_PERIOD;   //8
    short int SERIAL_PRIORITY;   //9
    short int SERIAL_PERIOD;     //10
    short int POS_PLOT_UNIT;     //11 (0 = v, 1 = mv, 2 = deg, 3 = rad)
    short int TOR_PLOT_UNIT;     //12 (0 = v, 1 = mv, 2 = N.m, 3 = N.mm)
    short int MACHINE_ID;        //13

    //Bool = 3
    bool ACTUATOR_ENABLE;    //0
    bool CONTROL_ENABLE;     //1
    bool SENSOR_ENABLE;      //2
    bool SERIAL_ON;          //3
    bool UDP_ON;             //4

    //Double = 13
    double POS_X_MAX;    //0
    double POS_Y_MAX;    //1
    double TOR_X_MAX;    //2
    double TOR_Y_MAX;    //3
    double POS_X_MIN;    //4
    double POS_Y_MIN;    //5
    double TOR_X_MIN;    //6
    double TOR_Y_MIN;    //7
    double POS_X_STEP;   //8
    double TOR_X_STEP;   //9
    double POS_Y_STEP;   //10
    double TOR_Y_STEP;   //11
    double BAUD;         //12

    //Int = 1
    int PORT;           //0

    //String = 1
    QString IP;             //0
    QString SERIAL_PORT;    //1
};

#endif // REGISTERS_H
