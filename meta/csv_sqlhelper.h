#ifndef CSV_SQLHELPER_H
#define CSV_SQLHELPER_H

#include "helpers/logger.h"
#include "sqlmetahelper.h"
#include <QString>

#include <repositories/sqlrepository.h>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>


class CSV_SQLHelper
{
public:
    struct CSVErrModel{
    private:
        QString _fileName;
        int _itemsCount;
        int _recordsCount;

        CSVErrModel(){};
    public:

        CSVErrModel(const QString& fn){
            _fileName = fn;
            _itemsCount= 0;
            _recordsCount = 0;
        }

        void setRecordsCount(int v){ _recordsCount = v;}
        void setItemsCount(int v){ _itemsCount = v;}

        QString ToSting(){
            return QStringLiteral("%1 (%2/%3)")
            .arg(_fileName)
                .arg(_itemsCount)
                .arg(_recordsCount);
        }
    };

    //CSV_SQLHelper();
    // imports from file to SQL repo
    template<typename T>
    void static Import(const QString& fn, SqlRepository<T>& repo, const QString& columnName)
    {
        CSVErrModel csverr(fn);
        FileHelper::CSVModel csvModel = FileHelper::LoadCSV(fn, ',');
        csverr.setRecordsCount(csvModel.records.count());

        if(csvModel.error == FileHelper::Ok)
        {
            zInfo("file ok");
            QList<T> items = T::CSV_Import(csvModel.records);
            csverr.setItemsCount(items.count());

            zInfo("items loaded: "+csverr.ToSting());
            SqlMetaHelper::InsertOrUpdate2(repo, items, columnName);
        }
        else
        {
            zWarning("items load failed: "+csverr.ToSting());
        }
    };

}; // endof class
#endif // CSV_SQLHELPER_H
