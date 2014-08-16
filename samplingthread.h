#ifndef SAMPLINGTHREAD_H
#define SAMPLINGTHREAD_H
#include "qwt_sampling_thread.h"
#include "sequenceplot.h"
#include <qwt_series_data.h>
#include <QtNetwork/QtNetwork>

class SamplingThread : public QwtSamplingThread
{
    Q_OBJECT

public:
    SamplingThread(QObject *parent = NULL);
    void initiate();
    /*Inherits:
     * double interval()
     * double elapsed()
     */

public Q_SLOTS:
    /*Inherits:
     * setInterval()
     * stop()
     */

signals:
    void pointAppendedPot(const QPointF point);
    void pointAppendedExt(const QPointF point);

private slots:
    void pause(bool paused);

protected:
    virtual void sample (double elapsed);

private:
    virtual double value (double timeStamp) const;
    QTcpSocket *tcpSocket;
    double pauseTime;
    double delay;
    bool active;
};

#endif // SAMPLINGTHREAD_H
