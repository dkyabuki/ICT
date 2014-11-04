#include "serialcomm.h"

SerialComm::SerialComm(QObject *parent) :
    QObject(parent)
{
    active = false;
    ready = false;
    portNo = NULL;
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
    char buf[5];
    char *msg;
    msg = (char *)malloc(262);
    char *datasize;
    char *aux = msg;
    *aux = ':';
    aux++;
    *aux = 'A';
    aux++;
    switch(msgCode)
    {
    case(0):
        *aux = 'S';
        aux++;
        *aux = 'T';
        aux++;
        datasize = aux;
        aux += sizeof(CommMessage::datasize);
        *aux = '|';
        aux++;
        strcpy(aux, itoa(Config::reg.getSensorEnable(), buf, 10));
        aux += strlen(buf);
        *aux = '|';
        aux++;
        strcpy(aux, itoa(Config::reg.getSensorPeriod(), buf, 10));
        aux += strlen(buf);
        *aux = '|';
        aux++;
        strcpy(aux, itoa(Config::reg.getSensorPriority(), buf, 10));
        aux += strlen(buf);
        *aux = '|';
        aux++;
        strcpy(aux, itoa(Config::reg.getControlEnable(), buf, 10));
        aux += strlen(buf);
        *aux = '|';
        aux++;
        strcpy(aux, itoa(Config::reg.getControlPeriod(), buf, 10));
        aux += strlen(buf);
        *aux = '|';
        aux++;
        strcpy(aux, itoa(Config::reg.getControlPriority(), buf, 10));
        aux += strlen(buf);
        *aux = '|';
        aux++;
        strcpy(aux, itoa(Config::reg.getActuatorEnable(), buf, 10));
        aux += strlen(buf);
        *aux = '|';
        aux++;
        strcpy(aux, itoa(Config::reg.getActuatorPeriod(), buf, 10));
        aux += strlen(buf);
        *aux = '|';
        aux++;
        strcpy(aux, itoa(Config::reg.getActuatorPriority(), buf, 10));
        aux += strlen(buf);
        *aux = '|';
        aux++;
        strcpy(aux, itoa(Config::reg.getSerialPeriod(), buf, 10));
        aux += strlen(buf);
        *aux = '|';
        aux++;
        strcpy(aux, itoa(Config::reg.getSerialPriority(), buf, 10));
        aux += strlen(buf);
        *aux = '|';
        aux++;
        *datasize = (char)(aux - (datasize + sizeof(CommMessage::datasize)));
        break;
    case(1):
        break;
    case(2):
        break;
    case(3):
        break;
    case(4):
        break;
    case(5):
        break;
    case(6):
        break;
    case(7):
        break;
    case(8):
        break;
    case(9):
        break;
    case(10):
        break;
    }
    *aux = '0';
    aux++;
    *aux = '0';
    aux++;
    *aux = '\0';
//    emit(show_error((QString)(msg)));
    portNo->write((char *)&msg, strlen(msg) + 1);
    if(!portNo->waitForBytesWritten(10))
        emit(show_error("Falhou em escrever a mensagem!"));
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
    emit(show_message("Iniciando configuração da porta serial..."));
    if (portNo != NULL)
    {
        if (portNo->isOpen())
            portNo->close();
        free(portNo);
    }
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
    emit(show_message("Porta serial configurada com sucesso!"));
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
