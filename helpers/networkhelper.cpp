#include "networkhelper.h"

#include "processhelper.h"

ClientSettings::ClientSettings(const QString &h, int p)
{
    _host = h;
    _port = p;
}

QString ClientSettings::ToString_HostPort()
{
    return _host+":"+QString::number(_port);
}

auto NetworkHelper::Ping(const QString& ip) -> bool
{
    ProcessHelper ph;
    auto out = ph.ShellExecute("ping -c1 -W1 " + ip, -1);
    return !out.exitCode;
}

