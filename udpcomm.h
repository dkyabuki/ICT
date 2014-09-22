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
    QRegExp *rx;

};

#endif // UDPCOMM_H
