#include "serialcomm.h"

struct SerialComm::CommMessage
{
    char        start;
    char        id;
    char        command[2];
    char        data[26];
    char        checksum[2];
};

SerialComm::SerialComm(QObject *parent) :
    QObject(parent)
{
}


int SerialComm::setPort(QString portName)
{
    if (portNo != NULL)
        free(portNo);
    QString portNames;
    foreach(const QSerialPortInfo info, QSerialPortInfo::availablePorts())
    {
        if(QString::compare(info.portName(), portName) == 0)
            portNo = new QSerialPort(portName);
    }
    if(portNo != NULL)
        return 0;
    else
        return -1;
}

void SerialComm::sendQuery(CommMessage message)
{
}
