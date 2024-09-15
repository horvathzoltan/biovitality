#include "csvhelper.h"

#include <helpers/stringhelper.h>




int CSVHelper::IndexOfRow(const QVarLengthArray<QString>& row, const QString &column_name)
{
    int L = row.length();
    for (int i = 0;i<L;i++) {
        QString a =row[i];
        QString a2 = StringHelper::Normalize(a);
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
