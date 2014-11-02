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
    void show_message(QString msg);
    void show_error(QString error);
    void finished();

public slots:
    void process();
    int setPort(QString portName);
    void close();
    bool isOpen();
    CommMessage* readMsg();
    QString test();

private slots:
    void sendQuery(CommMessage message);
    void config();
    void start();
    void stop();
    void pause();

private:
    bool active;
    QSerialPort *portNo;
    char* IdList;
    char* thisId;
};

#endif // SERIALCOMM_H
