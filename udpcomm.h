#ifndef UDPCOMM_H
#define UDPCOMM_H
#include <QtNetwork>

class UdpComm : public QUdpSocket
{

public:
    UdpComm(QObject *parent = NULL);
    QStringList udpRead();
    static bool datagramIsWrong(QStringList query);

private:
    #pragma pack(push,before)
    #pragma pack(1)
    struct commdata
    {
        unsigned short int type;
        double position;
        double torque;
        double time;
        char msg[20];
        int size;
    } *message;
    #pragma pack(pop,before)

    QRegExp *rx;

};

#endif // UDPCOMM_H
