#ifndef SQLEXCELREPOSITORY_H
#define SQLEXCELREPOSITORY_H

#include <QString>


class SqlExcelRepository{
private:
    QString _tableName;
protected:
    SqlExcelRepository(){};
public:
    SqlExcelRepository(const QString& tname){_tableName = tname;};

protected:
    static const QString CONTAINS_EXCEL_ID_CMD;
public:
    bool ContainsBy_ExcelId(int id);
    QString tableName2(){return _tableName;}
};

#endif // SQLEXCELREPOSITORY_H
