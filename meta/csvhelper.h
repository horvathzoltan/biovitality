#ifndef CSVHELPER_H
#define CSVHELPER_H

#include <QString>
#include <QMap>
#include <QVarLengthArray>
#include <QVariant>

class CSVHelper
{
public:
    static int IndexOfRow(const QVarLengthArray<QString>& row, const QString & column_name);

    static QVariant GetData(const QVarLengthArray<QString>& row, const QString &columnName, const QMap<QString, int>& ixs);
    static QVariant GetData(const QVarLengthArray<QString>& row, int ix);

    // stringből csinál id-t, ha van mögötte pont, leszedi
    static int GetId(const QVariant& v);
};

#endif // CSVHELPER_H
