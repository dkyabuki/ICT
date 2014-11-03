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
    //da comm para a GUI
    void emitError(QString error);
    void emitMessage(QString msg);

    //da GUI para a comm
    void emitUpdate();
    void emitStart();
    void emitStop();
    void emitPause(bool paused);
    void emitSendRequest(int msgCode);
    void emitPlotPoint(double time, double tor, double pos);
    void emitFinish();

signals:
    void showError(QString error);
    void showMsg(QString msg);
    void updateComm();
    void startComm();
    void stopComm();
    void pauseComm(bool paused);
    void finishComm();
    void sendRequest(int msgCode);
    void plotPoint(double time, double tor, double pos);
};

#endif // SAMPLINGTHREAD_H
