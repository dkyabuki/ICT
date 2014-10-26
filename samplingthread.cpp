#include "samplingthread.h"
#include <qmath.h>

//Inicializa membros e conecta sinais
SamplingThread::SamplingThread(QObject *parent):QwtSamplingThread(parent)
{
    active = false;
    udpmgr = new UdpComm(this);
    tcpmgr = new TcpComm(this, ip, port);
    x=0;
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
    udpmgr->bind(45454, UdpComm::ShareAddress);
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
    udpmgr->abort();
    stop();
}

//Nao funcional - Executada a cada x ms
void SamplingThread::sample( double elapsed )
{
    Q_UNUSED(elapsed);
    if(active)
    {
        /*************************/
        /*    Conexao por UDP    */
        /*************************/
        if(udpmgr->hasPendingDatagrams())
        {
            QStringList query = udpmgr->udpRead();
            if(!UdpComm::datagramIsWrong(query))
            {
                if(query[0].toInt() == 00)
                    emit showMsg("tipo = " + query[1]);
                else
                    plot(query);
            }
            else
            {
                emit showMsg("Erro ao ler valores");
            }
        }
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

    if(!active)
        udpmgr->abort();
    else
        udpmgr->bind(45454, UdpComm::ShareAddress);
}

void SamplingThread::commConfig(QHostAddress ipconf, quint16 portconf)
{
    ip = ipconf;
    port = portconf;
}

void SamplingThread::plot(QStringList query)
{
    x += 0.002;
    const QPointF p(x, query[1].toDouble()/1000.00);
    const QPointF t(x, query[2].toDouble()/1000.00);
    emit pointAppendedPot(p);
    emit pointAppendedExt(t);
}
