#ifndef SAMPLINGTHREAD_H
#define SAMPLINGTHREAD_H
#include "qwt_sampling_thread.h"
#include "sequenceplot.h"
#include "udpcomm.h"
#include "serialcomm.h"
#include <qwt_series_data.h>
#include <QTime>
#include <QString>
#include <sstream>
#include "config.h"

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
    void showError(QString str);
    void updateGUI(QStringList strl);

private slots:
//    void on_connection();
    void pause(bool paused);
//    void tcpReady();
//    void tcpError(QAbstractSocket::SocketError se);
//    void requestNewMsg();
    void plot(QStringList query);

protected:
    virtual void sample (double elapsed);

private:
    bool active;
    QTime *time;

//    quint16 port;
//    QHostAddress ip;
    UdpComm *udpmgr;
    SerialComm *serialmgr;
    int x;
};

#endif // SAMPLINGTHREAD_H
