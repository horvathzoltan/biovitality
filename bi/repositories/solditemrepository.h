#ifndef SOLDITEMREPOSITORY_H
#define SOLDITEMREPOSITORY_H

#include <bi/models/solditem.h>

class RepositoryBase{
public:
    static const QString CONTAINS_CMD;
    static const QString CONTAINS_EXCEL_ID_CMD;
    static const QString GET_CMD;
    static const QString GETALL_CMD;
    static const QString UPDATE_CMD;

    static const QString TABLE_NAME;

    bool Contains(int id);
};

class SoldItemRepository : public RepositoryBase
{
public:
    SoldItemRepository();

    bool ContainsBy_ExcelId(int id);
    //void Add(const SoldItem& m);

    SoldItem Get(int id);
    QList<SoldItem> GetAll();
    bool Update(const SoldItem& m);
    // void Remove(int id);
};

#endif // SOLDITEMREPOSITORY_H
