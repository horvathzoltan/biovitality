#ifndef CSVHELPER_H
#define CSVHELPER_H

#include <QString>
#include <QMap>
#include <QVarLengthArray>
#include <QVariant>
#include "meta/meta.h"
#include "helpers/stringhelper.h"


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
                QString _metaFieldName;
                QString _csvRowName;

            public:
                QString metaFieldName(){return _metaFieldName;}
                QString csvRowName(){return _csvRowName;}

                Data(const QString& metaFieldName, const QString& csvRowName){
                    _metaFieldName = metaFieldName;
                    _csvRowName = StringHelper::Normalize(csvRowName);
                }
            };

            QList<Data> _data;

        public:
            void Add_RowToField(const QString& metaFieldName, const QString& csvRowName)
            {
                Data data(metaFieldName, csvRowName);
                _data.append(data);
            }

            int Get_RowIx(const QString& header);
        QMap<QString,int> Get_RowIndexes(const QVarLengthArray<QString>& header);
    };

};

#endif // CSVHELPER_H
