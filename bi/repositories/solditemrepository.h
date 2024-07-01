#ifndef SOLDITEMREPOSITORY_H
#define SOLDITEMREPOSITORY_H

#include <bi/models/solditem.h>

class RepositoryBase{
protected:
    static const QString CONTAINS_CMD;
    static const QString CONTAINS_EXCEL_ID_CMD;
    static const QString GET_CMD;
    static const QString GETALL_CMD;
    static const QString UPDATE_CMD;
    static const QString INSERT_CMD;

    static const QString TABLE_NAME;

    bool Contains(int id);
};

class SoldItemRepository : public RepositoryBase
{
public:
    SoldItemRepository();

    SoldItem Get(int id);
    QList<SoldItem> GetAll();
    bool Update(const SoldItem& m);
    bool Add(const SoldItem& m);

    bool ContainsBy_ExcelId(int id);
};

#endif // SOLDITEMREPOSITORY_H
