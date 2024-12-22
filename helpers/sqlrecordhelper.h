 #ifndef SQLRECORDHELPER_H
 #define SQLRECORDHELPER_H

 #include <QList>
 #include <QSqlRecord>


 class SqlRecordHelper
 {
 public:
     struct SqlColumn{
    private:
         QString field;
         QString type;
         QString null;
         QString key;
         QString _default;
         QString extra;
         int _typeId;
     public:
         int typeId(){return _typeId;}

         static SqlColumn Parse(const QSqlRecord& r);
         static QList<SqlColumn> Parse(const QList<QSqlRecord>& r);

         static int IndexOf(const QList<SqlRecordHelper::SqlColumn>& columns, const QString& fieldName);

         static int MariaDBType_ToTypeId(const QString& typeName);
     };


     //static int IndexOf(const QList<QSqlRecord>& records, const QString& fn);
     static QString GetValueToString(
         const QSqlRecord &r, const QString& fieldName );
 };

 #endif // SQLRECORDHELPER_H
