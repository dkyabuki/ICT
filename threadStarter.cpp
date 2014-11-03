#include "threadStarter.h"
#include <qmath.h>

threadStarter::threadStarter(QObject *parent):QThread(parent)
{
}

threadStarter::~threadStarter()
{
    this->deleteLater();
}

void threadStarter::run()
{
    QTimer *timer = new QTimer();
    if (Config::reg.getSerialOn())
    {
        SerialComm *serialmgr = new SerialComm();
        connect(timer, SIGNAL(timeout()), serialmgr, SLOT(process()));

        //sinais da comm. para a GUI
        connect(serialmgr, SIGNAL(finished()), this, SLOT(quit()));
//        connect(serialmgr, SIGNAL(finished()), serialmgr, SLOT(quit()));
        connect(serialmgr, SIGNAL(finished()), this, SLOT(deleteLater()));
        connect(serialmgr, SIGNAL(show_error(QString)), this, SLOT(emitError(QString)));
        connect(serialmgr, SIGNAL(show_message(QString)), this, SLOT(emitMessage(QString)));

        //sinais da GUI para a comm.
        connect(this, SIGNAL(updateComm()), serialmgr, SLOT(config()));
        connect(this, SIGNAL(startComm()), serialmgr, SLOT(start()));
        connect(this, SIGNAL(pauseComm(bool)), serialmgr, SLOT(pause(bool)));
        connect(this, SIGNAL(stopComm()), serialmgr, SLOT(stop()));
        connect(this, SIGNAL(sendRequest(CommMessage)), serialmgr, SLOT(sendQuery(CommMessage)));
        connect(this, SIGNAL(finishComm()), serialmgr, SLOT(finishComm()));
    }
    else if (Config::reg.getUdpOn())
    {
        UdpComm udpmgr;
        connect(timer, SIGNAL(timeout()), &udpmgr, SLOT(process()));
        connect(&udpmgr, SIGNAL(finished()), this, SLOT(quit()));
        connect(&udpmgr, SIGNAL(finished()), &udpmgr, SLOT(quit()));
        connect(&udpmgr, SIGNAL(finished()), this, SLOT(deleteLater()));
    }
    timer->start(100);
    exec();
}

void threadStarter::emitPlotPoint(double time, double tor, double pos)
{
    emit(plotPoint(time, tor, pos));
}

void threadStarter::emitError(QString error)
{
    emit(showError(error));
}

void threadStarter::emitMessage(QString msg)
{
    emit(showMsg(msg));
}

void threadStarter::emitUpdate()
{
    emit(updateComm());
}

void threadStarter::emitStart()
{
    emit(startComm());
}

void threadStarter::emitStop()
{
    emit(stopComm());
}

void threadStarter::emitPause(bool paused)
{
    emit(pauseComm(paused));
}

void threadStarter::emitSendRequest(CommMessage message)
{
    emit(sendRequest(message));
}

void threadStarter::emitFinish()
{
    emit(finishComm());
}

//void threadStarter::sample( double elapsed )
//{
//    Q_UNUSED(elapsed);
//    if(active)
//    {
//        /*************************/
//        /*   Conexao por SERIAL  */
//        /*************************/
//        else if(Config::reg.getSerialOn())
//        {

//            emit(showMsg(serialmgr->test()));
//        }
//    }

//}

//void threadStarter::pause(bool running)
//{
//    active = !running;
//    else if (Config::reg.getSerialOn())
//    {

//    }
//}

//void threadStarter::plot(QStringList query)
//{
//    x = time->elapsed();
//    const QPointF p(x/1000.00, query[1].toDouble()/1000.00);
//    const QPointF t(x/1000.00, query[2].toDouble()/1000.00);
//    emit pointAppendedPot(p);
//    emit pointAppendedExt(t);
//}
