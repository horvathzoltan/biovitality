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
         int _metaTypeId;
     public:
         int metaTypeId(){return _metaTypeId;}

         static SqlColumn Parse(const QSqlRecord& r);
         static QList<SqlColumn> Parse(const QList<QSqlRecord>& r);

         static int IndexOf(const QList<SqlRecordHelper::SqlColumn>& columns, const QString& fieldName);

         static int MariaDBType_ToMetaTypeId(const QString& typeName);                  

         QString ToString();
     };


     //static int IndexOf(const QList<QSqlRecord>& records, const QString& fn);
     static QString GetValueToString(
         const QSqlRecord &r, const QString& fieldName );

     struct ColumnModel {
     private:
         ColumnModel(){};

         QString _name;
         QString _length;
         QString _modifier;

     public:
         ColumnModel(const QString& n,
                     const QString&l,
                     const QString& m);

         int MariaDBType_ToMetaTypeId();


     };

    static int ToNullable(int);
 };

 #endif // SQLRECORDHELPER_H
