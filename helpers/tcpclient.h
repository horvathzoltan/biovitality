#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include "networkhelper.h"


class TcpClient : public QObject
{
    Q_OBJECT        

private:
    QTcpSocket *tcpSocket = nullptr;
    QString _last;
    bool _hostAvailable = false;
    bool _isInited=false;

    ClientSettings _settings;
public:
    explicit TcpClient(QObject *parent = nullptr);

    void Init(const ClientSettings& s);
    void SendLog(const QString& msg);
private slots:
    void displayError(QAbstractSocket::SocketError socketError);
};

#endif // TCPCLIENT_H
