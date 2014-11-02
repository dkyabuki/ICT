#include "threadStarter.h"
#include <qmath.h>

threadStarter::threadStarter(QObject *parent):QThread(parent)
{
//    active = false;
//    if(Config::reg.getUdpOn())
//        udpmgr = new UdpComm(this);
//    else if(Config::reg.getSerialOn())
//        serialmgr = new SerialComm(this);
//    else
//        emit(showError("Nenhuma forma de comunicação foi selecionada"));
//    time = new QTime();
//    x=0;
}

threadStarter::~threadStarter()
{
    this->deleteLater();
}

void threadStarter::run()
{
    QTimer timer;
    if (Config::reg.getSerialOn())
    {
        SerialComm serialmgr;
        connect(&timer, SIGNAL(timeout()), &serialmgr, SLOT(process()));
        connect(&serialmgr, SIGNAL(finished()), this, SLOT(quit()));
        connect(&serialmgr, SIGNAL(finished()), &serialmgr, SLOT(quit()));
        connect(&serialmgr, SIGNAL(finished()), this, SLOT(deleteLater()));
        connect(&serialmgr, SIGNAL(show_error(QString)), this, SLOT(emitError(QString)));
        connect(&serialmgr, SIGNAL(show_message(QString)), this, SLOT(emitMessage(QString)));
    }
    else if (Config::reg.getUdpOn())
    {
        UdpComm udpmgr;
        connect(&timer, SIGNAL(timeout()), &udpmgr, SLOT(process()));
        connect(&udpmgr, SIGNAL(finished()), this, SLOT(quit()));
        connect(&udpmgr, SIGNAL(finished()), &udpmgr, SLOT(quit()));
        connect(&udpmgr, SIGNAL(finished()), this, SLOT(deleteLater()));
    }
    timer.start(2);
    exec();
}

void threadStarter::finishThread()
{

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

void threadStarter::emitPause()
{
    emit(pauseComm());
}

void threadStarter::emitSendRequest()
{
    emit(sendRequest());
}

//void threadStarter::initiate()
//{
//    if (Config::reg.getUdpOn())
//    {
//        udpmgr->bind(45454, UdpComm::ShareAddress);
//        start();
//        time->start();
//        active = true;
//    }
//}

//void threadStarter::halt()
//{
//    if (Config::reg.getUdpOn())
//        udpmgr->abort();
//    stop();
//}

//void threadStarter::sample( double elapsed )
//{
//    Q_UNUSED(elapsed);
//    if(active)
//    {
//        /*************************/
//        /*    Conexao por UDP    */
//        /*************************/
//        if(Config::reg.getUdpOn())
//        {
//            if(udpmgr->hasPendingDatagrams())
//            {
//                QStringList query = udpmgr->udpRead();
//                if(!UdpComm::datagramIsWrong(query))
//                {
//                    if(query[0].toInt() == 00)
//                        emit showMsg("tipo = " + query[1]);
//                    else
//                        plot(query);
//                }
//                else
//                {
//                    emit showError("Erro ao ler valores");
//                }
//            }
//        }
//        /*************************/
//        /*   Conexao por SERIAL  */
//        /*************************/
//        else if(Config::reg.getSerialOn())
//        {

//            emit(showMsg(serialmgr->test()));
//        }
//    }
////    std::stringstream ss;
////    ss<<QThread::currentThreadId();
////    QString str;
////    str = QString::fromStdString(ss.str());
////    emit showMsg("thread ID " + str);
//}

//void threadStarter::pause(bool running)
//{
//    active = !running;
//    if (Config::reg.getUdpOn())
//    {
//        if (!active)
//            udpmgr->abort();
//        else
//            udpmgr->bind(45454, UdpComm::ShareAddress);
//    }
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
