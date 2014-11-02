#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QObject>
#include <sstream>
#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "config.h"

class SerialComm : public QObject
{
    Q_OBJECT

public:
    SerialComm(QObject *parent = NULL);

#pragma pack(push, before)
#pragma pack(1)
    struct CommMessage
    {
        char                        start;          //1 byte
        char                        id;             //1 byte
        char                        command[2];     //2 bytes
        unsigned short int          datasize;       //4 bits
        char                        *data;          //até 255 bytes
        char                        checksum[2];    //2 bytes
    };
#pragma pack(pop, before)

signals:
    void readReady();

public slots:
    void process();
    int setPort(QString portName);
    int config();
    int open();
    void close();
    bool isOpen();
    void emitReadSignal();
    CommMessage* readMsg();
    QString test();

private slots:
    void sendQuery(CommMessage message);

private:
    QSerialPort *portNo;
    char* IdList;
    char* thisId;
};

#endif // SERIALCOMM_H
