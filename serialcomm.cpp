#include "serialcomm.h"

SerialComm::SerialComm(QObject *parent) :
    QObject(parent)
{
    active = false;
    ready = false;
}

CommMessage* SerialComm::readMsg()
{
    CommMessage *msg;
    msg = (CommMessage *)portNo->readAll().data_ptr();
    return (msg);
}

QString SerialComm::test()
{
    std::stringstream ss;
    ss<<QThread::currentThreadId();
    QString str;
    str = QString::fromStdString(ss.str());
    return("thread ID " + str);
}

void SerialComm::process()
{
    if(active)
    {
        if(!portNo->isRequestToSend() && !timer->isActive())
        {
            if(ready)
            {
                CommMessage *incoming = (CommMessage *)portNo->readAll().data_ptr();
                if(validateMessage(incoming) == 0)
                {
                    //TRATA SINAL RECEBIDO
                }
            }
        }
    }
//    std::stringstream ss;
//    ss<<QThread::currentThreadId();
//    QString str;
//    str = QString::fromStdString(ss.str());
//    emit show_message("thread ID " + str);
}

void SerialComm::sendQuery(CommMessage message)
{
//    portNo->write(QByteArray::fromRawData((char *)&message, sizeof(message)));
    emit(show_message("sinal emitido 2"));
}

void SerialComm::start()
{
    CommMessage startOrder;
    startOrder.start = ':';
    startOrder.id = 'A';
    startOrder.command[0] = 'O';
    startOrder.command[1] = '0';
    startOrder.data = (new QString("Hello, device!"))->toLocal8Bit().data();
    startOrder.datasize = (char)(strlen(startOrder.data));
//    for(int i = 0; i < strlen(startOrder.data); i++)
//    {
//        startOrder.data[i];
//    }
//    startOrder.checksum = (char)0xFFFF - startOrder.start - startOrder.id - startOrder.command[0] - startOrder.command[1];
    startOrder.checksum[0] = '0';
    startOrder.checksum[1] = '0';
    sendQuery(startOrder);
    active = true;
}

void SerialComm::stop()
{
    CommMessage stopOrder;
    stopOrder.start = ':';
    stopOrder.id = 'A';
    stopOrder.command[0] = 'O';
    stopOrder.command[1] = '1';
    stopOrder.data = "";
    stopOrder.datasize = 0;
    stopOrder.checksum[0] = '0';
    stopOrder.checksum[1] = '0';
    sendQuery(stopOrder);
    active = false;
}

void SerialComm::finishComm()
{
//    if(portNo->isOpen())
//        portNo->close();
//    portNo->deleteLater();
//    free(IdList);
//    free(thisId);
    emit(show_message("Emitiu sinal 2"));
//    emit(finished());
//    this->deleteLater();
}

void SerialComm::pause(bool paused)
{
    active = false;
    if(paused)
    {
        if(portNo->isOpen())
        {
            portNo->clear();
            portNo->close();
        }
    }
    else
        if(!portNo->isOpen())
            portNo->open(QIODevice::ReadWrite);
}

void SerialComm::config()
{
    if (portNo != NULL)
        if (portNo->isOpen())
            portNo->close();
        free(portNo);
    foreach(const QSerialPortInfo info, QSerialPortInfo::availablePorts())
    {
        if(QString::compare(info.portName(), Config::reg.getSerialPort()) == 0)
            portNo = new QSerialPort(info.portName());
    }
    if (portNo != NULL)
    {
        if(!portNo->open(QIODevice::ReadWrite))
        {
            emit(show_error("Não foi possível abrir a porta serial"));
            return;
        }
        if(!portNo->setBaudRate((qint32)Config::reg.getBaud()))
        {
            emit(show_error("Não foi possível ajustar o Baud"));
            return;
        }
        if(!portNo->setDataBits(QSerialPort::Data8))
        {
            emit(show_error("Não foi possível ajustar o tamanho dos dados"));
            return;
        }
        if(!portNo->setParity(QSerialPort::NoParity))
        {
            emit(show_error("Não foi possível ajustar a paridade dos bits"));
            return;
        }
        if(!portNo->setStopBits(QSerialPort::OneStop))
        {
            emit(show_error("Não foi possível ajustar o stop bit"));
            return;
        }
        if(!portNo->setFlowControl(QSerialPort::NoFlowControl))
        {
            emit(show_error("Não foi possível ajustar o controle de fluxo"));
            return;
        }
        QByteArray temp = QString::number(Config::reg.getMachineId()).toLocal8Bit();
        thisId = temp.data();
    }
    else
        emit(show_error("Náo foi possível encontrar a porta serial"));
    return;
}

void SerialComm::hasPendingMessage()
{
    ready = true;
}

int SerialComm::validateMessage(CommMessage *msg)
{
    if(msg->start == ':')
        if(msg->id == *thisId)
            switch(msg->command[0])
            {
            case ('S'):
            case ('O'):
            case ('H'):
            case ('C'):
                return 0;
            default:
                return -1;
            }
    return -1;
}
