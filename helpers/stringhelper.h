#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <QString>


class StringHelper
{
public:
    StringHelper();

    static QString Normalize(const QString s);
    static QStringList Normalize(const QStringList s);
};

#endif // STRINGHELPER_H
