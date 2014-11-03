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

void SerialComm::sendQuery(int msgCode)
{
    CommMessage msg;
    char buf[5];
    msg.start = ':';
    msg.id = 'A';
    switch(msgCode)
    {
    case (0):
        msg.command[0] = 'S';
        msg.command[1] = 'T';
        char *aux = msg.data;
        *aux = '|';
        aux++;
        if(Config::reg.getSensorEnable() == true)
            *aux = '1';
        else
            *aux = '0';
        aux += 1;
        *aux = '|';
        aux++;

        memcpy(aux, itoa(Config::reg.getSerialPeriod(), buf, 10), sizeof(short int));
//        aux += sizeof(short int);
//        *aux = '\0';
//        emit(show_message((QString)msg.data));
//        break;
//    case (1):
//        msg.command[0] = 'S';
//        msg.command[1] = 'P';
//        break;
//    case (2):
//        msg.command[0] = 'S';
//        msg.command[1] = 'R';
//        break;
//    case (3):
//        msg.command[0] = 'O';
//        msg.command[1] = '0';
//        break;
//    case (4):
//        msg.command[0] = 'O';
//        msg.command[1] = '1';
//        break;
//    case (5):
//        msg.command[0] = 'H';
//        msg.command[1] = '0';
//        break;
//    case (6):
//        msg.command[0] = 'C';
//        msg.command[1] = '0';
//        break;
//    case (7):
//        msg.command[0] = 'C';
//        msg.command[1] = '1';
//        break;
//    case (8):
//        msg.command[0] = 'S';
//        msg.command[1] = 'N';
//        break;
//    case (9):
//        msg.command[0] = 'O';
//        msg.command[1] = '2';
//        break;
//    case (10):
//        msg.command[0] = 'O';
//        msg.command[1] = '3';
    }
    msg.checksum[0] = '0';
    msg.checksum[1] = '0';
//    portNo->write(QByteArray::fromRawData((char *)&message, sizeof(message)));
    emit(show_message(QString::number(sizeof(char))));
}

void SerialComm::start()
{
    sendQuery(3);
    active = true;
}

void SerialComm::stop()
{
    sendQuery(4);
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
