#ifndef CSVHELPER_H
#define CSVHELPER_H

#include <QString>
#include <QMap>
#include <QVarLengthArray>
#include <QVariant>
#include <meta/meta.h>
#include <helpers/stringhelper.h>


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

    class RowToField{
        private:
            struct Data{
            private:
                QString _fieldName;
                QString _rowName;

            public:
                QString fieldName(){return _fieldName;}

                Data(const QString& fn, const QString& rn){
                    _fieldName = fn;
                    _rowName = StringHelper::Normalize(rn);
                }
            };

            QList<Data> _data;

        public:
            void Add(const QString& fn, const QString& rn){
                Data data(fn, rn);
                _data.append(data);
            }

            bool ContainsRow(const QString& header);
        QMap<QString,int> Get_RowIndexes(const QVarLengthArray<QString>& header);
    };

};

#endif // CSVHELPER_H
