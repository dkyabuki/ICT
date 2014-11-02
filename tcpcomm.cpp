#include "tcpcomm.h"

TcpComm::TcpComm(QObject *parent)
{
    Q_UNUSED(parent);
//    connect(this, SIGNAL(newConnection()), this, SLOT(tcpReady()));
    currentMessage = " ";
}

void TcpComm::tcpReady()
{

}
