#include "samplingthread.h"
#include <qmath.h>

SamplingThread::SamplingThread(QObject *parent):QwtSamplingThread(parent)
{
    active = false;
    if(Config::reg.getUdpOn())
        udpmgr = new UdpComm(this);
    else if(Config::reg.getSerialOn())
        serialmgr = new SerialComm(this);
    else
        emit(showError("Nenhuma forma de comunicação foi selecionada"));
    time = new QTime();
    x=0;
}

SamplingThread::~SamplingThread()
{
    this->deleteLater();
}

void SamplingThread::initiate()
{
    if (Config::reg.getUdpOn())
    {
        udpmgr->bind(45454, UdpComm::ShareAddress);
        start();
        time->start();
        active = true;
    }
    if (Config::reg.getSerialOn())
    {
        if (serialmgr->setPort(Config::reg.getSerialPort()) == 0)
        {
            if(serialmgr->open() != 0)
            {
                emit(showError("Could not open serial port"));
                return;
            }
            serialmgr->config();
            start();
            time->start();
            active = true;
        }
    }
}

void SamplingThread::halt()
{
    if (Config::reg.getUdpOn())
        udpmgr->abort();
    if (Config::reg.getSerialOn())
        if(serialmgr->isOpen())
            serialmgr->close();
    stop();
}

void SamplingThread::sample( double elapsed )
{
    Q_UNUSED(elapsed);
    if(active)
    {
        /*************************/
        /*    Conexao por UDP    */
        /*************************/
        if(Config::reg.getUdpOn())
        {
            if(udpmgr->hasPendingDatagrams())
            {
                QStringList query = udpmgr->udpRead();
                if(!UdpComm::datagramIsWrong(query))
                {
                    if(query[0].toInt() == 00)
                        emit showMsg("tipo = " + query[1]);
                    else
                        plot(query);
                }
                else
                {
                    emit showError("Erro ao ler valores");
                }
            }
        }
        /*************************/
        /*   Conexao por SERIAL  */
        /*************************/
        else if(Config::reg.getSerialOn())
        {

            emit(showMsg(serialmgr->test()));
        }
    }
//    std::stringstream ss;
//    ss<<QThread::currentThreadId();
//    QString str;
//    str = QString::fromStdString(ss.str());
//    emit showMsg("thread ID " + str);
}

void SamplingThread::pause(bool running)
{
    active = !running;
    if (Config::reg.getUdpOn())
    {
        if (!active)
            udpmgr->abort();
        else
            udpmgr->bind(45454, UdpComm::ShareAddress);
    }
    else if (Config::reg.getSerialOn())
    {

    }
}

void SamplingThread::plot(QStringList query)
{
    x = time->elapsed();
    const QPointF p(x/1000.00, query[1].toDouble()/1000.00);
    const QPointF t(x/1000.00, query[2].toDouble()/1000.00);
    emit pointAppendedPot(p);
    emit pointAppendedExt(t);
}
