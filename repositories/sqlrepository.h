#ifndef SQLREPOSITORY_H
#define SQLREPOSITORY_H

#include <QSqlField>
#include <QString>
#include <typeindex>

#include <helpers/sqlhelper.h>


//#include <meta/meta.h>


//#include <bi/models/solditem.h>

class TypeContainer{
private:
    QMap<std::type_index, void*> _data;

    template<typename T>
    static std::type_index GetKey(){ return std::type_index(typeid(T));}

public:
    template< typename T>
    void Add(T* ptr){
        std::type_index key = GetKey<T>();
        _data.insert(key, ptr);
    }

    template< typename T>
    T* Get(){
        std::type_index key = GetKey<T>();
        bool contains = _data.contains(key);
        if(contains){
            void* b = _data.value(key);
            T* e = reinterpret_cast<T*>(b);
            return e;
        }
        return nullptr;
    }

    template<typename T>
    void Delete(){
        std::type_index key = GetKey<T>();
        if(_data.contains(key)){
            void* b = _data.take(key);
            T* e = reinterpret_cast<T*>(b);
            delete e;
        }
    }
};

class RepositoryBase{
private:
    QString _tableName;
protected:
    RepositoryBase(){};
public:
    RepositoryBase(const QString& tname)
    {
        _tableName = tname;
        //_repos.append(this);
        //_typeContainer.Add<>(this);
    };
protected:
    static const QString CONTAINS_CMD;
    static const QString CONTAINS_BY_COLUMN_CMD;
    static const QString GET_ID_BY_COLUMN_CMD;
    static const QString GET_CMD;
    static const QString GETALL_CMD;
    static const QString UPDATE_CMD;
    static const QString INSERT_CMD;
    static const QString TABLE_EXISTS_CMD;
    static const QString FIELDS_EXISTS_CMD;

public:
    //static QMap<std::type_index, void*> _repos;
    //TypeContainer _typeContainer;

    //static RepositoryBase* GetRepository(const QString& tableName);
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
    SqlRepository(const QString& tname);

    bool isTableExists();
    bool isFieldsExists();

    T Get(int id);
    QList<T> GetAll();
    bool Update(const T& m);
    bool Add(const T& m);

    //bool dbErr(SQLHelper::DbErr& dbErr);
public:
    bool Contains_ByColumn(const QString& fieldName, const QVariant& fieldValue);
    QList<int> GetIds_ByColumn(const QString& fieldName, const QVariant& fieldValue);

    //template<typename T>
    static bool Check();
};

class SqlRepositoryContainer{
private:
    static TypeContainer _data;

public:
    template< typename T>
    static void Add(SqlRepository<T>* ptr){_data.Add(ptr);}

    template< typename T>
    static SqlRepository<T>* Get(){return _data.Get<SqlRepository<T>>();}
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
