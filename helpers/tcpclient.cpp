#include "tcpclient.h"

#include "logger.h"
#include "networkhelper.h"

void TcpClient::Init(const ClientSettings& s)
{
    _isInited = false;
    _settings = s;
    _isInited = true;
}

TcpClient::TcpClient(QObject *parent) :QObject(parent)
{
    tcpSocket = new QTcpSocket(this);

    //in.setDevice(tcpSocket);
    //in.setVersion(QDataStream::Qt_6_5);

    //connect(tcpSocket, &QIODevice::readyRead, this, &TcpClient::readFortune);
    connect(tcpSocket, &QAbstractSocket::errorOccurred, this, &TcpClient::displayError);

}

void TcpClient::SendLog(const QString& msg)
{
    if(!_isInited) return;

    if(!_hostAvailable){
        _hostAvailable = NetworkHelper::Ping(_settings.host());
    }
    if(!_hostAvailable) return;

    _last.clear();

    tcpSocket->connectToHost(_settings.host(), _settings.port(), QIODeviceBase::ReadWrite);
    bool isConnected = tcpSocket->waitForConnected(1000);
    if(isConnected){
        QByteArray b = ("addlog:"+msg).toUtf8();
        tcpSocket->write(b);
        tcpSocket->flush();
        bool isWritten = tcpSocket->waitForBytesWritten(1000);
        if(isWritten){
            bool canRead = tcpSocket->waitForReadyRead(1000);
            if(canRead){
                QByteArray a = tcpSocket->readAll();
                _last = QString(a);
                //ok = true;
            }
        }
    }

    tcpSocket->close();
    tcpSocket->disconnect();

}

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
