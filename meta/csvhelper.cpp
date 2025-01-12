#include "csvhelper.h"

#include "helpers/stringhelper.h"




int CSVHelper::IndexOfRow(const QVarLengthArray<QString>& rows, const QString &column_name)
{
    int L = rows.length();
    for (int i = 0;i<L;i++) {
        QString row = rows[i];
        QString a2 = StringHelper::Normalize(row);
        QString column_name2 = StringHelper::Normalize(column_name);
        if (a2 == column_name2) return i;
    }
    return -1;
}

QVariant CSVHelper::GetData(const QVarLengthArray<QString>& row, const QString& columnName, const QMap<QString,int>& ixs){
    if(ixs.contains(columnName)){
        int ix = ixs.value(columnName);
        return GetData(row, ix);
    }
    return {};
}

QVariant CSVHelper::GetData(const QVarLengthArray<QString> &row, int ix){
    if(ix<0) return {};
    if(ix>=row.length()) return {};

    return QVariant(row[ix]);
}

int CSVHelper::GetId(const QVariant& v){
    QString txt = v.toString();
    if(txt.endsWith('.')) txt = txt.left(txt.length()-1);
    bool ok;
    int i = txt.toInt(&ok);
    if(ok) return i;
    return -1;
}

MetaValue CSVHelper::CSV_RowToMetaValue(const QVarLengthArray<QString> &row, const QString& fieldName , int fieldIx)
{
    QVariant v2 = GetData(row, fieldIx);
    RefType refType = RefType::None;
    MetaValue v1(fieldName, "", v2, refType);
    return v1;
}

QList<MetaValue> CSVHelper::CSV_RowToMetaValues(const QVarLengthArray<QString> &row, const QMap<QString,int>& ixs)
{
    QList<MetaValue> metaValues;

    QMapIterator i(ixs);
    while(i.hasNext())
    {
        i.next();
        MetaValue v1 = CSV_RowToMetaValue(row,i.key(),i.value());
        metaValues.append(v1);
    }
    return metaValues;
}

QMap<QString, int> CSVHelper::RowToField::Get_RowIndexes(const QVarLengthArray<QString> &headers)
{
    QMap<QString,int> ixs;

    for(int i=0;i<headers.length();i++){
        QString header0 = headers[i];
        QString header = StringHelper::Normalize(header0);

        int rowIx = Get_RowIx(header);

        if(rowIx>-1){

            ixs.insert(_data[rowIx].metaFieldName(), i);
        }
    }

    return ixs;
}

int CSVHelper::RowToField::Get_RowIx(const QString& header)
{
    int L = _data.length();
    for(int i=0;i<L;i++){
        auto& a = _data[i];
        if(a.csvRowName()==header) return i;
    }
    return -1;
}
