#ifndef TCPCOMM_H
#define TCPCOMM_H
#include <QtNetwork>
#include <QString>

class TcpComm : public QTcpServer
{

public:
    TcpComm(QObject *parent = NULL, QHostAddress ipAddress = QHostAddress::LocalHost, quint16 accessPort = 45454);

private:
    quint16 blockSize;
    quint16 port;
    QHostAddress ip;
    QString currentMessage;
};

#endif // TCPCOMM_H
