#include "networkhelper.h"

#include "processhelper.h"

auto NetworkHelper::Ping(const QString& ip) -> bool
{
    ProcessHelper ph;
    auto out = ph.ShellExecute("ping -c1 -W1 " + ip, -1);
    return !out.exitCode;
}
