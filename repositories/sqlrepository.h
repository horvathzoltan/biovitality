#ifndef SQLREPOSITORY_H
#define SQLREPOSITORY_H

#include "sqlexcelrepository.h"

#include <QString>


//#include <bi/models/solditem.h>

class RepositoryBase{
private:
    QString _tableName;
protected:
    RepositoryBase(){};
public:
    RepositoryBase(const QString& tname){_tableName = tname;};

protected:
    static const QString CONTAINS_CMD;    
    static const QString GET_CMD;
    static const QString GETALL_CMD;
    static const QString UPDATE_CMD;
    static const QString INSERT_CMD;
    static const QString TABLE_EXISTS_CMD;

public:
    QString tableName(){return _tableName;}
    bool Contains(int id);
};

/*
class SqlRepository : public RepositoryBase
{
public:
    SqlRepository();

    SoldItem Get(int id);
    QList<SoldItem> GetAll();
    bool Update(const SoldItem& m);
    bool Add(const SoldItem& m);

    bool ContainsBy_ExcelId(int id);
};
*/


template<typename T>
class SqlRepository : public SqlExcelRepository, public RepositoryBase
{
private:
    SqlRepository(){};
public:
    SqlRepository(const QString& tname);

    bool isTableExists();
    T Get(int id);
    QList<T> GetAll();
    bool Update(const T& m);
    bool Add(const T& m);    
};

#endif // SQLREPOSITORY_H
