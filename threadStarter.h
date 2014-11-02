#ifndef SAMPLINGTHREAD_H
#define SAMPLINGTHREAD_H
#include "qwt_sampling_thread.h"
#include "sequenceplot.h"
#include "udpcomm.h"
#include "serialcomm.h"
#include <QThread>
#include <QTimer>
#include "config.h"

class threadStarter : public QThread
{
    Q_OBJECT

public:
    threadStarter(QObject *parent = NULL);
    ~threadStarter();
    void run();

private slots:
    void finishThread();

    //da thread para a GUI
    void emitError(QString error);
    void emitMessage(QString msg);
    //da GUI para a thread
    void emitUpdate();
    void emitStart();
    void emitStop();
    void emitPause();
    void emitSendRequest();

signals:
    void showError(QString error);
    void showMsg(QString msg);
    void updateComm();
    void startComm();
    void stopComm();
    void pauseComm();
    void sendRequest();

//    void initiate();
//    void halt();

//public Q_SLOTS:

//signals:
//    void pointAppendedPot(const QPointF point);
//    void pointAppendedExt(const QPointF point);
//    void showMsg(QString str);
//    void showError(QString str);
//    void updateGUI(QStringList strl);

//private slots:
//    void pause(bool paused);
//    void plot(QStringList query);

//protected:
//    virtual void sample (double elapsed);

//private:
//    bool active;
//    QTime *time;
//    QThread *thread;

//    UdpComm *udpmgr;
//    SerialComm *serialmgr;
//    int x;
};

#endif // SAMPLINGTHREAD_H
