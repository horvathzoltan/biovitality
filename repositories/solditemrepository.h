#ifndef SOLDITEMREPOSITORY_H
#define SOLDITEMREPOSITORY_H

#include <bi/models/solditem.h>


class SoldItemRepository
{
public:
    SoldItemRepository();
    static void InsertOrUpdate(const QList<SoldItem>& items);
};

#endif // SOLDITEMREPOSITORY_H
