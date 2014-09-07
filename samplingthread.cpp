#include "samplingthread.h"
#include <qmath.h>

//Inicializa membros e conecta sinais
SamplingThread::SamplingThread(QObject *parent):QwtSamplingThread(parent)
{
    active = false;
    tcpSocket = new QTcpSocket(this);
    tcpSocket->bind(45454, QTcpSocket::ShareAddress);
    udpmgr = new UdpComm();
    delay = 0;
    rx = new QRegExp("(\\ |\\,|\\:|\\t)");
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(tcpReady()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT());
    currentMessage = " ";
}

//Inicia o thread
void SamplingThread::initiate()
{
    QString ip;
    QList<QHostAddress> iplist = QNetworkInterface::allAddresses();
    for (int i = 0; i < iplist.size(); ++i) {
        if (iplist.at(i) != QHostAddress::LocalHost &&
            iplist.at(i).toIPv4Address()) {
            ip = iplist.at(i).toString();
            break;
        }
    }
    if (ip.isEmpty())
        ip = QHostAddress(QHostAddress::LocalHost).toString();

    tcpSocket->connectToHost(ip, 45454);
    connectionConfig = QStringList()<<"TCP"<<ip<<"45454";
    blockSize = 0;
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(on_connection()));
//    active = true;
}

//Executa quando uma conexao TCP eh feita
void SamplingThread::on_connection()
{
    emit updateGUI(connectionConfig);
    time.start();
    start();
}

//Interrompe a conexao do socket TCP
void SamplingThread::halt()
{
    tcpSocket->disconnectFromHost();
    delay = 0;
    stop();
}

//Nao funcional - Executada a cada x ms
void SamplingThread::sample( double elapsed )
{
    if(active)
    {
        /****************************/
        /*    Excitacao senoidal    */
        /****************************/
        /*const QPointF point((double)(time.elapsed()/1000.00 + delay/1000.00),value((double)(time.elapsed()/1000.00 + delay/1000.00)));
        //const QPointF point(elapsed,value(elapsed));
        emit pointAppendedPot(point);
        emit pointAppendedExt(point);*/


        /*************************/
        /*    Conexao por UDP    */
        /*************************/
        QStringList query = udpmgr->udpRead();
        if(!UdpComm::checkError(query))
        {
              emit errorMsg("query[1]: " + query[1]);

//            double x;
//            x = query[1].toDouble()/1000.00;
//            const QPointF p(x, query[2].toDouble()/1000.00);
//            const QPointF t(x, query[3].toDouble()/1000.00);
//            emit pointAppendedPot(p);
//            emit pointAppendedExt(t);

        }
        else
        {
            emit errorMsg("Erro ao ler valores");
            return;
        }
    }
}

/*************************/
/*    Conexao por TCP    */
/*************************/
void SamplingThread::tcpReady()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    if(blockSize == 0)
    {
        if(tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> blockSize;
    }
    if(tcpSocket->bytesAvailable() < blockSize)
        return;

    QString nextMessage;
    in >> nextMessage;

    if (nextMessage == currentMessage) {
        QTimer::singleShot(0, this, SLOT(requestNewMsg()));
        return;
    }

    QStringList query = nextMessage.split(*rx);
    emit errorMsg(nextMessage);
//    if((query[0].toInt() == 40) && !query[1].isNull() && !query[2].isNull() && !query[3].isNull() && (query[4] == "\0"))
//    {
//        double x;
//        x = query[1].toDouble()/1000.00;
//        const QPointF p(x, query[2].toDouble()/1000.00);
//        const QPointF t(x, query[4].toDouble()/1000.00);
//        emit pointAppendedPot(p);
//        emit poin tAppendedExt(t);
//    }
    currentMessage = nextMessage;
}

void SamplingThread::requestNewMsg()
{
    blockSize = 0;
    tcpSocket->abort();

    QString ip;
    QList<QHostAddress> iplist = QNetworkInterface::allAddresses();
    for (int i = 0; i < iplist.size(); ++i) {
        if (iplist.at(i) != QHostAddress::LocalHost &&
            iplist.at(i).toIPv4Address()) {
            ip = iplist.at(i).toString();
            break;
        }
    }
    if (ip.isEmpty())
        ip = QHostAddress(QHostAddress::LocalHost).toString();

    tcpSocket->connectToHost(ip, 45454);
}

void SamplingThread::tcpError(QAbstractSocket::SocketError se)
{
    switch(se)
    {
    case(QAbstractSocket::RemoteHostClosedError):
        break;
    case(QAbstractSocket::HostNotFoundError):
        emit errorMsg("Host was not found");
        break;
    case(QAbstractSocket::ConnectionRefusedError):
        emit errorMsg("Connection refused by peer");
        break;
    default:
        emit errorMsg("the error " + tcpSocket->errorString());
    }
}

double SamplingThread::value( double timeStamp ) const
{
    return (5*qFastSin(timeStamp*25));
}

void SamplingThread::pause(bool paused)
{
    if(paused)
    {
        delay += time.elapsed();
        active = false;
    } else {
        time.start();
        active = true;
    }
}
