#include "udpcomm.h"

UdpComm::UdpComm(QObject *parent):QUdpSocket(parent)
{
    rx = new QRegExp("(\\ |\\,|\\:|\\t)");
}

QStringList UdpComm::udpRead()
{
    QByteArray datagram;
    datagram.resize(pendingDatagramSize());
    readDatagram(datagram.data(), datagram.size());
    return(QString(datagram.constData()).split(*rx));
}

bool UdpComm::datagramIsWrong(QStringList query)
{
    if(!query.isEmpty())
    {
        if(query[0].toInt() == 40)
        {
            if(!query[1].isNull() && !query[2].isNull() && !query[3].isNull())
            {
                return(false);
            }
        }
    }
    return(true);
}
