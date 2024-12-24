#include "tcpclient.h"

#include "logger.h"

TcpClient::TcpClient(QObject *parent) :QObject(parent)
{
    tcpSocket = new QTcpSocket(this);

    //in.setDevice(tcpSocket);
    //in.setVersion(QDataStream::Qt_6_5);

    //connect(tcpSocket, &QIODevice::readyRead, this, &TcpClient::readFortune);
    connect(tcpSocket, &QAbstractSocket::errorOccurred, this, &TcpClient::displayError);

}

void TcpClient::requestNewFortune(const QString& msg)
{
    //tcpSocket->abort();

    tcpSocket->connectToHost("192.168.1.156", 8081, QIODeviceBase::ReadWrite);
    //tcpSocket->open(QIODeviceBase::ReadWrite);
    tcpSocket->waitForConnected();
    //tcpSocket->write("getlist");
    QByteArray b = ("addlog:"+msg).toUtf8();
    tcpSocket->write(b);
    tcpSocket->flush();
    //tcpSocket->waitForBytesWritten(1000);
    tcpSocket->waitForReadyRead(1000);
    QByteArray a = tcpSocket->readAll();
    tcpSocket->close();

    _last = QString(a);

}

// void TcpClient::readFortune()
// {
//     in.startTransaction();

//     QString nextFortune;
//     in >> nextFortune;

//     if (!in.commitTransaction())
//         return;

//     qDebug()<<nextFortune;
// }

void TcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug()<<"RemoteHostClosedError";
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug()<<"HostNotFoundError";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug()<<"ConnectionRefusedError";
        break;
    default:
         qDebug()<<QStringLiteral("The following error occurred: %1.")
                .arg(tcpSocket->errorString());
        break;
    }
}
