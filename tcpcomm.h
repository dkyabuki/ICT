#ifndef TCPCOMM_H
#define TCPCOMM_H
#include <QtNetwork>
#include <QString>

class TcpComm : public QTcpServer
{

public:
    TcpComm(QObject *parent = NULL, QHostAddress ipAddress, quint16 accessPort);

private:
    quint16 blockSize;
    quint16 port;
    QHostAddress ip;
    QString currentMessage;
};

#endif // TCPCOMM_H
