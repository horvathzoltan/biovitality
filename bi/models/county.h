#ifndef COUNTY_H
#define COUNTY_H

#include "bi/meta/meta.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

class County
{
public:
    County();

    int id=-1;
    QString name;
    QString KSH_code;

    static void MetaInit();

    bool isValid();

private:
    static Meta<County> _meta;

};

#endif // COUNTY_H
