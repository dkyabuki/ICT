#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QObject>
#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SerialComm : public QObject
{
    Q_OBJECT

public:
    SerialComm(QObject *parent = NULL);

public slots:
    int setPort(QString portName);

private slots:
    void sendQuery(CommMessage message);

private:
#pragma pack(push, before)
#pragma pack(1)
    struct CommMessage;
#pragma pack(pop, before)
    QSerialPort *portNo;
    char* IdList;

};

#endif // SERIALCOMM_H
