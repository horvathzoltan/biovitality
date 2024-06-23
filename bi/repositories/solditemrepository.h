#ifndef SOLDITEMREPOSITORY_H
#define SOLDITEMREPOSITORY_H

#include <bi/models/solditem.h>

class RepositoryBase{
public:
    static const QString CONTAINS_CMD;
    static const QString TABLE_NAME;

    bool Contains(int id);
};

class SoldItemRepository : public RepositoryBase
{
public:
    SoldItemRepository();


    //bool Contains(int id);
    // void Add(const SoldItem& m);
    // SoldItem Get(int id);
    // QList<SoldItem> GetAll();
    // void Update(const SoldItem& m);
    // void Remove(int id);
};

#endif // SOLDITEMREPOSITORY_H
