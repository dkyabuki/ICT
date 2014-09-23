#include "samplingthread.h"
#include <qmath.h>

//Inicializa membros e conecta sinais
SamplingThread::SamplingThread(QObject *parent):QwtSamplingThread(parent)
{
    active = false;
#ifdef __UDP_COMM
    udpmgr = new UdpComm(this);
#endif
#ifdef __TCP_COMM
    tcpmgr = new TcpComm(this, ip, port);
#endif
}

SamplingThread::~SamplingThread()
{
    this->deleteLater();
}

//Inicia o thread
void SamplingThread::initiate()
{
//    if (ip.isEmpty())
//        ip = QHostAddress(QHostAddress::LocalHost).toString();

//    tcpSocket->connectToHost(ip, 45454);
//    connectionConfig = QStringList()<<"TCP"<<ip<<"45454";
//    blockSize = 0;
//    connect(tcpSocket, SIGNAL(connected()), this, SLOT(on_connection()));
    active = true;
#ifdef __UDP_COMM
    udpmgr->bind(45454, UdpComm::ShareAddress);
#endif
    start();
}

//Executa quando uma conexao TCP eh feita
//void SamplingThread::on_connection()
//{
//    emit updateGUI(connectionConfig);
//    time.start();
//    start();
//}

//Interrompe a conexao do socket TCP
void SamplingThread::halt()
{
//    tcpSocket->disconnectFromHost();
#ifdef __UDP_COMM
    udpmgr->abort();
#endif
    stop();
}

//Nao funcional - Executada a cada x ms
void SamplingThread::sample( double elapsed )
{
    if(active)
    {
        /*************************/
        /*    Conexao por UDP    */
        /*************************/
#ifdef __UDP_COMM
        if(udpmgr->hasPendingDatagrams())
        {
            QStringList query = udpmgr->udpRead();
            if(!UdpComm::datagramIsWrong(query))
            {
                plot(query);
            }
            else
            {
                emit showMsg("Erro ao ler valores");
            }
        }
#endif

    }
}

/*************************/
/*    Conexao por TCP    */
/*************************/
//void SamplingThread::tcpReady()
//{
//    QDataStream in(tcpSocket);
//    in.setVersion(QDataStream::Qt_4_0);
//    if(blockSize == 0)
//    {
//        if(tcpSocket->bytesAvailable() < (int)sizeof(quint16))
//            return;

//        in >> blockSize;
//    }
//    if(tcpSocket->bytesAvailable() < blockSize)
//        return;

//    QString nextMessage;
//    in >> nextMessage;

//    if (nextMessage == currentMessage) {
//        QTimer::singleShot(0, this, SLOT(requestNewMsg()));
//        return;
//    }

//    QStringList query = nextMessage.split(*rx);
//    emit errorMsg(nextMessage);
////    if((query[0].toInt() == 40) && !query[1].isNull() && !query[2].isNull() && !query[3].isNull() && (query[4] == "\0"))
////    {
////        double x;
////        x = query[1].toDouble()/1000.00;
////        const QPointF p(x, query[2].toDouble()/1000.00);
////        const QPointF t(x, query[4].toDouble()/1000.00);
////        emit pointAppendedPot(p);
////        emit poin tAppendedExt(t);
////    }
//    currentMessage = nextMessage;
//}

//void SamplingThread::requestNewMsg()
//{
//    blockSize = 0;
//    tcpSocket->abort();

//    QString ip;
//    QList<QHostAddress> iplist = QNetworkInterface::allAddresses();
//    for (int i = 0; i < iplist.size(); ++i) {
//        if (iplist.at(i) != QHostAddress::LocalHost &&
//            iplist.at(i).toIPv4Address()) {
//            ip = iplist.at(i).toString();
//            break;
//        }
//    }
//    if (ip.isEmpty())
//        ip = QHostAddress(QHostAddress::LocalHost).toString();

//    tcpSocket->connectToHost(ip, 45454);
//}

void SamplingThread::pause(bool running)
{
    active = !running;
#ifdef __TCP_COMM
    if(!active)

    else

#endif

#ifdef __UDP_COMM
    if(!active)
        udpmgr->abort();
    else
        udpmgr->bind(45454, UdpComm::ShareAddress);
#endif

}

void SamplingThread::commConfig(QHostAddress ipconf, quint16 portconf)
{
    ip = ipconf;
    port = portconf;
}

void SamplingThread::plot(QStringList query)
{
    double x;
    x = query[1].toDouble()/1000.00;
    const QPointF p(x, query[2].toDouble()/1000.00);
    const QPointF t(x, query[3].toDouble()/1000.00);
    emit pointAppendedPot(p);
    emit pointAppendedExt(t);
}
