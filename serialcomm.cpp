#include "serialcomm.h"

SerialComm::SerialComm(QObject *parent) :
    QObject(parent)
{
    active = false;
}

int SerialComm::setPort(QString portName)
{

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

void SerialComm::process()
{

}

void SerialComm::sendQuery(CommMessage message)
{

}

void SerialComm::start()
{

}

void SerialComm::stop()
{
    if(portNo->isOpen())
        portNo->close();
    portNo->deleteLater();
    free(IdList);
    free(thisId);
    emit(finished());
}

void SerialComm::pause()
{

}

void SerialComm::config()
{
    if (portNo != NULL)
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

        if (portNo != NULL)
        {
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
    }
    else
        emit(show_error("Náo foi possível encontrar a porta serial"));
    return;
}
