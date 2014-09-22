#ifndef SAMPLINGTHREAD_H
#define SAMPLINGTHREAD_H
#include "qwt_sampling_thread.h"
#include "sequenceplot.h"
#include "udpcomm.h"
#include <qwt_series_data.h>
#include <QTime>
#include <QString>

class SamplingThread : public QwtSamplingThread
{
    Q_OBJECT

public:
    SamplingThread(QObject *parent = NULL);
    ~SamplingThread();

    void initiate();
    void halt();

public Q_SLOTS:

signals:
    void pointAppendedPot(const QPointF point);
    void pointAppendedExt(const QPointF point);
    void showMsg(QString str);
    void updateGUI(QStringList strl);

private slots:
//    void on_connection();
    void pause(bool paused);
//    void tcpReady();
//    void tcpError(QAbstractSocket::SocketError se);
//    void requestNewMsg();

protected:
    virtual void sample (double elapsed);

private:
    UdpComm *udpmgr;
//    QTcpSocket *tcpSocket;
    int restartTime;
    double delay;
    bool active;
    QTime time;
//    quint16 blockSize;
//    QString currentMessage;
//    QStringList connectionConfig;
};

#endif // SAMPLINGTHREAD_H
