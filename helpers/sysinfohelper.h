#ifndef SYSINFOHELPER_H
#define SYSINFOHELPER_H

#include <QString>


class SysInfoHelper
{
private:
    static QString _target;
    static QString _buildNumber;
    static QString _user;
    static QString _hostName;

    static bool hasBuildNumber();
public:
    static void Init(const QString& t, const QString& b);
    static QString Get_SysInfo();

};

#endif // SYSINFOHELPER_H
