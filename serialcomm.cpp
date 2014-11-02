#include "serialcomm.h"

SerialComm::SerialComm(QObject *parent) :
    QObject(parent)
{
}

int SerialComm::setPort(QString portName)
{
    if (portNo != NULL)
        free(portNo);
    foreach(const QSerialPortInfo info, QSerialPortInfo::availablePorts())
    {
        if(QString::compare(info.portName(), portName) == 0)
            portNo = new QSerialPort(portName);
    }
    if(portNo != NULL)
    {
        connect(portNo, SIGNAL(readyRead()), this, SLOT(emitReadSignal()));
        return 0;
    }
    else
        return -1;
}

int SerialComm::config()
{
    if (portNo != NULL)
    {
        if(!portNo->setBaudRate((qint32)Config::reg.getBaud()))
            return -1;
        if(!portNo->setDataBits(QSerialPort::Data8))
            return -1;
        if(!portNo->setParity(QSerialPort::NoParity))
            return -1;
        if(!portNo->setStopBits(QSerialPort::OneStop))
            return -1;
        if(!portNo->setFlowControl(QSerialPort::NoFlowControl))
            return -1;

        QByteArray temp = QString::number(Config::reg.getMachineId()).toLocal8Bit();
        thisId = temp.data();
    }
    return -1;
}

void SerialComm::sendQuery(CommMessage message)
{

}

int SerialComm::open()
{
    if(portNo->isOpen())
    {
        portNo->close();
    }
    if(!portNo->open(QIODevice::ReadWrite))
        return -1;
    return 0;
}

SerialComm::CommMessage* SerialComm::readMsg()
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

bool SerialComm::isOpen()
{
    return (portNo->isOpen()? true : false);
}

void SerialComm::close()
{
    portNo->close();
}

void SerialComm::emitReadSignal()
{
    emit(readReady());
}
