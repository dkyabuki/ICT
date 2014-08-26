#include "samplingthread.h"
#include <qmath.h>

SamplingThread::SamplingThread(QObject *parent):QwtSamplingThread(parent)
{
    active = false;
    tcpSocket = new QTcpSocket(this);
    tcpSocket->bind(45454, QTcpSocket::ShareAddress);
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);
    delay = 0;
    rx = new QRegExp("(\\ |\\,|\\:|\\t)");
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(tcpReady()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT());
    currentMessage = " ";
}

void SamplingThread::initiate()
{
    tcpSocket->connectToHost("192.168.0.145", 45454);
    blockSize = 0;
    active = true;
    time.start();
    start();
}

void SamplingThread::halt()
{
    tcpSocket->disconnectFromHost();
    delay = 0;
    stop();
}

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
        /*while (udpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            udpSocket->readDatagram(datagram.data(), datagram.size());
            QStringList query = QString(datagram.constData()).split(*rx);
            if((query[0].toInt() == 40) && !query[1].isNull() && !query[2].isNull() && !query[3].isNull() && (query[4] == "\0"))
            {
//                emit errorMsg("query[2]: " + query[2]);
                double x;
                x = query[1].toDouble()/1000.00;
                const QPointF p(x, query[2].toDouble()/1000.00);
                const QPointF t(x, query[4].toDouble()/1000.00);
                emit pointAppendedPot(p);
                emit pointAppendedExt(t);
            }
            else
            {
                emit errorMsg("Erro ao ler valores");
                udpSocket->flush();
                return;
            }
        }*/
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
    if((query[0].toInt() == 40) && !query[1].isNull() && !query[2].isNull() && !query[3].isNull() && (query[4] == "\0"))
    {
//                emit errorMsg("query[2]: " + query[2]);
        double x;
        x = query[1].toDouble()/1000.00;
        const QPointF p(x, query[2].toDouble()/1000.00);
        const QPointF t(x, query[4].toDouble()/1000.00);
        emit pointAppendedPot(p);
        emit pointAppendedExt(t);
    }
    currentMessage = nextMessage;
}

void SamplingThread::requestNewMsg()
{
    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost("192.168.0.145", 45454);
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
