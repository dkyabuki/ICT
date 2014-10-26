#ifndef SAMPLINGTHREAD_H
#define SAMPLINGTHREAD_H
#include "qwt_sampling_thread.h"
#include "sequenceplot.h"
#include "udpcomm.h"
#include "tcpcomm.h"
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
    void commConfig(QHostAddress ipconf, quint16 portconf);
//    void tcpReady();
//    void tcpError(QAbstractSocket::SocketError se);
//    void requestNewMsg();

protected:
    virtual void sample (double elapsed);

private:
    void plot(QStringList query);

    int restartTime;
    bool active;
    QTime time;
//    QStringList connectionConfig;

    quint16 port;
    QHostAddress ip;
    UdpComm *udpmgr;
    TcpComm *tcpmgr;
    double x;
};

#endif // SAMPLINGTHREAD_H
