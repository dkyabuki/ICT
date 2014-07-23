#ifndef REGISTERS_H
#define REGISTERS_H

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

    short int getMode();

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

    void setMode(short int v);

private:

    short int MONITORING;
    short int SENSORING;
    short int TRAJECTORY;

    short int SENSOR_PRIORITY;
    short int SENSOR_PERIOD;
    short int SENSOR_ENABLE;

    short int CONTROL_PRIORITY;
    short int CONTROL_PERIOD;
    short int CONTROL_ENABLE;

    short int ACTUATOR_PRIORITY;
    short int ACTUATOR_PERIOD;
    short int ACTUATOR_ENABLE;

    short int SERIAL_PRIORITY;
    short int SERIAL_PERIOD;

    short int MODE;
};

#endif // REGISTERS_H
