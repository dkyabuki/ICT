#ifndef UDPCOMM_H
#define UDPCOMM_H
#include <QtNetwork>

class UdpComm
{
public:
    UdpComm();
    QStringList udpRead();
    static bool checkError(QStringList query);
    void emptySocket();

private:
    QUdpSocket *socket;
    QRegExp *rx;

};

#endif // UDPCOMM_H
