#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QObject>
#include <sstream>
#include <QtSerialPort>
#include <QTimer>
#include <QtSerialPort/QSerialPortInfo>
#include "config.h"

#pragma pack(push, before)
#pragma pack(1)
struct CommMessage
{
    char                        start;          //1 byte
    char                        id;             //1 byte
    char                        command[2];     //2 bytes
    unsigned char               datasize;       //1 byte
    char                        *data;          //até 255 bytes
    char                        checksum[2];    //2 bytes
};
#pragma pack(pop, before)

class SerialComm : public QObject
{
    Q_OBJECT

public:
    SerialComm(QObject *parent = NULL);

signals:
    void show_message(QString msg);
    void show_error(QString error);
    void finished();

public slots:
    void process();
    CommMessage* readMsg();
    QString test();

private slots:
    void sendQuery(CommMessage message);
    void config();
    void start();
    void stop();
    void pause(bool paused);
    void finishComm();

    void hasPendingMessage();
    int validateMessage(CommMessage *msg);
private:
    bool active;
    bool ready;
    QSerialPort *portNo;
    char* IdList;
    char* thisId;
    QTimer* timer;
};

#endif // SERIALCOMM_H
