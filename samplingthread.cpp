#include "samplingthread.h"
#include <qmath.h>

SamplingThread::SamplingThread(QObject *parent):QwtSamplingThread(parent)
{
    active = false;
    delay = 0;
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
        const QPointF point((double)(time.elapsed()/1000.00 + delay/1000.00),value((double)(time.elapsed()/1000.00 + delay/1000.00)));
        //const QPointF point(elapsed,value(elapsed));
        emit pointAppendedPot(point);
        emit pointAppendedExt(point);
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
