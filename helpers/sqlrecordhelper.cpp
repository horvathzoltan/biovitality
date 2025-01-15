#include "sqlrecordhelper.h"
#include "typehelper.h"
#include "helpers/logger.h"
//#include "sqlhelper.h"
//#include "optionalconverters.h"

#include <QRegularExpression>
#include <QSqlField>

// int SqlRecordHelper::IndexOf(const QList<QSqlRecord> &records, const QString &fn)
// {
//     for (const QSqlRecord &r : records) {
//         if (r.){}
//     }
//     return -1;
// }

QList<SqlRecordHelper::SqlColumn> SqlRecordHelper::SqlColumn::Parse(const QList<QSqlRecord> &records)
{
    QList<SqlRecordHelper::SqlColumn> e;
    for(auto&r:records){
        auto m = Parse(r);
        e.append(m);
    }
    return e;
}

SqlRecordHelper::SqlColumn SqlRecordHelper::SqlColumn::Parse(const QSqlRecord &r)
{
    SqlRecordHelper::SqlColumn m;

    m.field = GetValueToString(r, "Field");
    m.type = GetValueToString(r, "Type").toLower();
    m.null = GetValueToString(r, "Null").toLower();
    m.key = GetValueToString(r, "Key").toLower();
    m._default = GetValueToString(r, "Default").toLower();
    m.extra = GetValueToString(r, "Extra").toLower();

    int metaTypeId = MariaDBType_ToMetaTypeId(m.type);

    if(m.null=="yes"){
        // todo 001c4 a varchar nullable nem jelent ám automatikusan optional<int> -et
        //int t2 = OptionalConverters::ToNullable_MetaTypeId(t);
        //int metaTypeId_Nullable = ToNullable(metaTypeId);
        m._metaTypeId = TypeHelper::ToNullable(metaTypeId);//(metaTypeId_Nullable == -1)?metaTypeId:metaTypeId_Nullable;
    } else{
         m._metaTypeId = metaTypeId;
    }

    return m;
}

QString SqlRecordHelper::GetValueToString(
    const QSqlRecord &r, const QString& fieldName ){

     int i = r.indexOf(fieldName);
     if(i>=0){
         QSqlField f = r.field(i);
         return f.value().toString();//SQLHelper::GetFieldValue(f.value());
     }
     return {};
}

int SqlRecordHelper::SqlColumn::IndexOf(const QList<SqlColumn> &columns, const QString &fieldName)
{
    int L = columns.count();
    for(int i=0;i<L;i++)
    {
        auto&column = columns[i];
        if(column.field == fieldName) return i;
    }
    return -1;
}

int SqlRecordHelper::SqlColumn::MariaDBType_ToMetaTypeId(const QString &typeNameLength)
{   
    QRegularExpression r(R"(^(?:([\w]+)(?:\(([\d,.]+)\))?)(?:\s*([\w\ ]*))$)");

    auto m = r.match(typeNameLength);

    if(m.hasMatch()){
        ColumnModel column(m.captured(1),
                           m.captured(2),
                           m.captured(3));

        return column.MariaDBType_ToMetaTypeId();
    }

    return -1;
}


QString SqlRecordHelper::SqlColumn::ToString()
{
    QString msg = field+' '+type;

    if(null=="yes") msg+= " nullable";

    return msg;
}


SqlRecordHelper::ColumnModel::ColumnModel(const QString &n, const QString &l, const QString &m)
{
    _name = n; _length = l; _modifier = m;
}

int SqlRecordHelper::ColumnModel::MariaDBType_ToMetaTypeId()
{
    if(_name == "bool") return QMetaType::Type::Bool;
    if(_name == "int"){
        if(_modifier.contains("unsigned")) return QMetaType::Type::UInt;
        return QMetaType::Type::Int;
    }

    if(_name == "bigint"){
        if(_modifier.contains("unsigned")) return QMetaType::Type::ULongLong;
        return QMetaType::Type::LongLong;
    }

    if(_name == "varchar") return QMetaType::Type::QString;
    if(_name == "date") return QMetaType::Type::QDateTime;

    if(_name == "decimal") return QMetaType::Type::QReal;
    if(_name == "double") return QMetaType::Type::Double;
    if(_name == "float") return QMetaType::Type::Float;

    zWarning("MariaDBType_ToMetaTypeId not implements conversion to type: "+_name);
    return -1;
}





// int SqlRecordHelper::ColumnModel::ToNullableTypeId(int t){
//     //if(QMetaType::Type::Bool) return OptionalConverters::
// }
