#ifndef NETWORKHELPER_H
#define NETWORKHELPER_H

#include <QString>

struct ClientSettings{
protected:
    QString _host;
    int _port;

public:
    ClientSettings(){};
    ClientSettings(const QString& h,int port);

    QString host(){return _host;}
    int port(){return _port;}
    QString ToString_HostPort();
};

class NetworkHelper
{
public:
    static bool Ping(const QString &ip, int timeout);
};

#endif // NETWORKHELPER_H
