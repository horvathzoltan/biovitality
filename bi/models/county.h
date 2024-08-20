#ifndef COUNTY_H
#define COUNTY_H

#include "bi/meta/meta.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

#include <dataform.h>

/*
5;Budapest;01
2;Baranya vármegye;02
1;Bács-Kiskun vármegye;03
3;Békés vármegye;04
4;Borsod-Abaúj-Zemplén vármegye;05
6;Csongrád-Csanád vármegye;06
7;Fejér vármegye;07
8;Győr-Moson-Sopron vármegye;08
9;Hadjú-Bihar vármegye;09
10;Heves vármegye;10
12;Komárom-Esztergom vármegye;11
13;Nógrád vármegye;12
14;Pest vármegye;13
20;Somogy vármegye;14
15;Szabolcs-Szatmár-Bereg vármegye;15
11;Jász-Nagykun Szolnok vármegye;16
16;Tolna vármegye;17
17;Vas vármegye;18
18;Veszprém vármegye;19
19;Zala vármegye;20
*/

class County
{
public:
    County();
    County(int i, const QString& n, const QString& k);

    int id=-1;
    QString name;
    QString KSH_code;

    static void MetaInit();

    bool isValid();

    static DataRowDefaultModel To_DataRowDefaultModel();

    IdMegnev ToIdMegnev(){return _meta.ToIdMegnev(this); }
private:
    static QList<County> _data;
    static Meta<County> _meta;    
};

#endif // COUNTY_H
