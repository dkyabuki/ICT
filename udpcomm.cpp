#include "udpcomm.h"

UdpComm::UdpComm()
{
    socket = new QUdpSocket();
    socket->bind(45454, QUdpSocket::ShareAddress);
    rx = new QRegExp("(\\ |\\,|\\:|\\t)");
}

QStringList UdpComm::udpRead()
{
    if(socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());
        QStringList query = QString(datagram.constData()).split(*rx);
        return(query);
    }
    QStringList query;
    return(query);
}

bool UdpComm::checkError(QStringList query)
{
    if(!query.isEmpty())
    {
        if(query[0].toInt() == 40)
        {
            if(!query[1].isNull() && !query[2].isNull() && !query[3].isNull() && query[4] == "\0")
            {
                return(false);
            }
            else{
                return(true);
            }
        }
    }
    else
    {
        return(true);
    }
}

void UdpComm::emptySocket()
{
    socket->flush();
}
