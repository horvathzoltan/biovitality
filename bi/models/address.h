#ifndef ADDRESS_H
#define ADDRESS_H

#include "bi/meta/meta.h"
#include "bi/meta/meta.h"
#include <QVariant>

class Address
{
public:
    Address();

    int id=-1;
    int postalCode;         // irsz
    QString settlementName; // településnév
    QString publicAreaName; // közterület(utca) név + házszám - a cím utolsó tagja
    //QString houseNumber;    // házszám - a cím utolsó tagja
    int excelId=-1;

    static void MetaInit();
};

#endif // ADDRESS_H
