#ifndef CSV_IMPORTMODEL_H
#define CSV_IMPORTMODEL_H

#include <QString>
#include <QVarLengthArray>


template<typename T>
struct CSV_ImportModel
{
    struct Data{
    private:
        T _item;
        QVarLengthArray<QString> _csvFields;
        int _rowNumber;
        QChar _separator;        
    public:
        Data(T i, QVarLengthArray<QString> r, int n, QChar s){
            _csvFields = r;
            _item = i;
            _rowNumber = n;
            _separator = s;
        }
        
        T item(){return _item;}
        bool isValid(){return _item.isValid();};
        
        QString csvRow(){
            QString e = "";
            for(auto&a:_csvFields)
            {
                if(!e.isEmpty()) e+=_separator;
                e+=a;
            }
            return e;
        }
        
        int rowNumber(){return _rowNumber;}
    };
    
private:
    QList<Data> _data;
public:
    void Add(const Data& d){ _data.append(d);}
    bool isEmpty(){return _data.isEmpty();}
    int validItemsCount(){
        int i=0;
        for(auto&a:_data) if(a.isValid()) i++;
        return i;
    };
    QList<Data> data(){return _data;}
};

#endif // CSV_IMPORTMODEL_H
