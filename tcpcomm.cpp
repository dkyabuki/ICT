#include "tcpcomm.h"

TcpComm::TcpComm(QObject *parent, QHostAddress ipAddress, quint16 accessPort):QTcpServer(parent)
{
    ip = ipAddress;
    port = accessPort;
    connect(this, SIGNAL(newConnection()), this, SLOT(tcpReady()));
    currentMessage = " ";
}
