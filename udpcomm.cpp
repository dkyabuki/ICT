#include "udpcomm.h"

UdpComm::UdpComm(QObject *parent):QUdpSocket(parent)
{
    rx = new QRegExp("(\\||\\,|\\:|\\t)");
}

QStringList UdpComm::udpRead()
{
    QByteArray datagram;
    datagram.resize(pendingDatagramSize());
    readDatagram(datagram.data(), datagram.size());
    message = (commdata *)datagram.data_ptr();
    QStringList *strl = new QStringList();
    switch(message->type)
    {
    case(00):
        strl->append(QString::number(message->type));
        strl->append(message->msg);
        strl->append(QString::number(message->size));
        break;
    case(01):
        strl->append(QString::number(message->type));
        strl->append(QString::number(message->position));
        strl->append(QString::number(message->torque));
        break;
    }
    return *strl;
//    return(QString(datagram.constData()).split(*rx));
}

bool UdpComm::datagramIsWrong(QStringList query)
{
    if(!query.isEmpty())
    {
        switch(query[0].toInt())
        {

        case(00):
            if(!query[1].isNull() && !query[2].isNull() && !query[3].isNull())
                return(false);
            break;
        case(01):
            if(!query[1].isNull() && !query[2].isNull() && !query[3].isNull())
                return(false);
            break;
        case(40):
            if(!query[1].isNull() && !query[2].isNull() && !query[3].isNull())
                return(false);
            break;
        }
    }
    return(true);
}
