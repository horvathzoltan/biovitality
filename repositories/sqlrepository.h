#ifndef SQLREPOSITORY_H
#define SQLREPOSITORY_H

#include "sqlexcelrepository.h"

#include <QSqlField>
#include <QString>

//#include <meta/meta.h>


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
    static const QString CONTAINS_BY_COLUMN_CMD;
    static const QString GET_ID_BY_COLUMN_CMD;
    static const QString GET_CMD;
    static const QString GETALL_CMD;
    static const QString UPDATE_CMD;
    static const QString INSERT_CMD;
    static const QString TABLE_EXISTS_CMD;

public:
    const QString& tableName(){return _tableName;}
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
//class SqlRepository : public SqlExcelRepository, public RepositoryBase
class SqlRepository : public RepositoryBase
{
private:
    SqlRepository();
public:
    //SqlRepository(const QString& tname);
    SqlRepository(const QString& tname) : RepositoryBase(tname) {}

    bool isTableExists();
    T Get(int id);
    QList<T> GetAll();
    bool Update(const T& m);
    bool Add(const T& m);

public:
    bool Contains_ByColumn(const QString& fieldName, const QVariant& fieldValue);
    QList<int> GetIds_ByColumn(const QString& fieldName, const QVariant& fieldValue);
};

// template<typename T>
// class SqlERepository : public SqlRepository<T>
// {
// private:
//     QString _tableName;
// private:
//     SqlERepository() :  SqlRepository<T>("") { _tableName=""; };
// public:
//     SqlERepository(const QString& tname) :  SqlRepository<T>(tname)
//     {
//         _tableName = tname;
//     };

// private:
//     static const QString CONTAINS_EXCEL_ID_CMD;
//     static const QString GET_ID_BY_EXCEL_ID_CMD;

// public:
//     bool ContainsBy_ExcelId(int id);
//     int GetIdBy_ExcelId(int id);
//     QString tableName2()const{return _tableName;}
// };

#endif // SQLREPOSITORY_H
