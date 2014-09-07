#ifndef SAMPLINGTHREAD_H
#define SAMPLINGTHREAD_H
#include "qwt_sampling_thread.h"
#include "sequenceplot.h"
#include "udpcomm.h"
#include <qwt_series_data.h>
#include <QtNetwork/QtNetwork>
#include <QTime>
#include <QString>

class SamplingThread : public QwtSamplingThread
{
    Q_OBJECT

public:
    SamplingThread(QObject *parent = NULL);
    void initiate();
    void halt();

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
    void errorMsg(QString str);
    void updateGUI(QStringList strl);

private slots:
    void on_connection();
    void pause(bool paused);
    void tcpReady();
    void tcpError(QAbstractSocket::SocketError se);
    void requestNewMsg();

protected:
    virtual void sample (double elapsed);

private:
    virtual double value (double timeStamp) const;
//    QUdpSocket *udpSocket;
    UdpComm *udpmgr;
    QTcpSocket *tcpSocket;
    int restartTime;
    double delay;
    bool active;
    QTime time;
    QRegExp *rx;
    quint16 blockSize;
    QString currentMessage;
    QStringList connectionConfig;
};

#endif // SAMPLINGTHREAD_H
