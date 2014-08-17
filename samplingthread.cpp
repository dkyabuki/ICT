#include "samplingthread.h"
#include <qmath.h>

SamplingThread::SamplingThread(QObject *parent):QwtSamplingThread(parent)
{
    active = false;
    delay = 0;
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);
    rx = new QRegExp("(\\ |\\,|\\.|\\:|\\t)");
}

void SamplingThread::initiate()
{
    active = true;
    time.start();
    start();
}

void SamplingThread::halt()
{
    delay = 0;
    stop();
}

void SamplingThread::sample( double elapsed )
{
    if(active)
    {
//        const QPointF point((double)(time.elapsed()/1000.00 + delay/1000.00),value((double)(time.elapsed()/1000.00 + delay/1000.00)));
//        //const QPointF point(elapsed,value(elapsed));
//        emit pointAppendedPot(point);
//        emit pointAppendedExt(point);
        if (udpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            udpSocket->readDatagram(datagram.data(), datagram.size());
            QStringList query = QString(datagram.constData()).split(*rx);
            if (query[0].toInt() != 40)
            {
                emit errorMsg("Erro ao ler primeiro termo");
                return;
            }
            if(!query[1].isNull() && !query[2].isNull() && !query[3].isNull())
            {
                double x;
                x = query[1].toDouble()/1000.00;
                const QPointF p(x, query[2].toDouble()/1000.00);
                const QPointF t(x, query[3].toDouble()/1000.00);
                emit pointAppendedPot(p);
                emit pointAppendedExt(t);
            }
            else
            {
                emit errorMsg("Erro ao ler valores");
                return;
            }
        }
    }
}

double SamplingThread::value( double timeStamp ) const
{
    return (5*qFastSin(timeStamp*25));
}

void SamplingThread::pause(bool paused)
{
    if(paused)
    {
        delay += time.elapsed();
        active = false;
    } else {
        time.start();
        active = true;
    }
}
