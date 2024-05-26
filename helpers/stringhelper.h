#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <QString>


class StringHelper
{
public:
    StringHelper();

    static QString Normalize(const QString s);
};

#endif // STRINGHELPER_H
