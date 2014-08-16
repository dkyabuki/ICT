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
    start();
}

void SamplingThread::sample( double elapsed )
{
    if(active)
    {
        const QPointF point(elapsed - delay,value(elapsed));
        emit pointAppendedPot(point);
        emit pointAppendedExt(point);
    }
}

double SamplingThread::value( double timeStamp ) const
{
    return (20*qFastSin(timeStamp*25));
}

void SamplingThread::pause(bool paused)
{
    if(paused)
    {
        pauseTime = elapsed();
        active = false;
    } else {
        delay += (elapsed() - pauseTime);
        active = true;
    }
}
