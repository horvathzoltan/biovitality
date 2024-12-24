#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT

private:
    QTcpSocket *tcpSocket = nullptr;
    //QDataStream in;
    QString _last;
public:
    explicit TcpClient(QObject *parent = nullptr);
    void requestNewFortune(const QString& msg);

private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    //void readFortune();
};

#endif // TCPCLIENT_H
