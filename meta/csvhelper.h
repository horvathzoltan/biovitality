#ifndef CSVHELPER_H
#define CSVHELPER_H

#include <QString>
#include <QMap>
#include <QVarLengthArray>
#include <QVariant>
#include <meta/meta.h>


class CSVHelper
{
public:
    static int IndexOfRow(const QVarLengthArray<QString>& row, const QString & column_name);

    static QVariant GetData(const QVarLengthArray<QString>& row, const QString &columnName, const QMap<QString, int>& ixs);
    static QVariant GetData(const QVarLengthArray<QString>& row, int ix);

    // stringből csinál id-t, ha van mögötte pont, leszedi
    static int GetId(const QVariant& v);
    static MetaValue CSV_RowToMetaValue(const QVarLengthArray<QString> &row, const QString& fn , int ix);
    static QList<MetaValue> CSV_RowToMetaValues(const QVarLengthArray<QString>& row, const QMap<QString,int>& ixs);
};

#endif // CSVHELPER_H
