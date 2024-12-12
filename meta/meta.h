#ifndef META_H
#define META_H

#include "helpers/logger.h"
#include <QList>
#include <QMetaType>
#include <QString>
#include <QVariant>
#include <helpers/sqlhelper.h>


#define AddMetaField(b) _meta.AddField(#b, QMetaType::fromType<decltype(_meta._instance.b)>(), (char*)(&_meta._instance.b));
#define AddMetaBase(b) _meta.AddBaseName(#b, sizeof(b));

//#define AddRowToField(b,c) Add_RowToField(#b, c); {(void)_meta._instance.b;}
#define FieldName(t, b) QString(#b); { (void)t::metaInstance().b;}
#define AddRowToField(a,b,c) if(_meta.Contains(#b)){a.Add_RowToField(#b, c); {(void)_meta._instance.b;}} else {zWarning(QStringLiteral("MetaField is not exists:")+#b);}

// class optConv{
//     quint64 ToUint64(bool *ok = nullptr) const
//     {
//          const bool canConvertSafely = l < std::numeric_limits<int>::max();
//     }
// }


template<typename T>
struct CSV_ImportModel
{
    struct Data{
    private:
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

class IdMegnev{
public:
    int id = -1;
    QString name;
    QString code;
};



// ez megy ki az UI felé
struct MetaValue{
private:
    MetaValue(){};    
public:
    MetaValue(const QString& _name, const QString& _wcode,const QMetaType& type ){
        name = _name;
        wcode = _wcode;
        value = QVariant(type);
    }

    MetaValue(const QString& _name, const QString& _wcode,const QVariant& _value ){
        name = _name;
        wcode = _wcode;
        value = _value;
    }

    QString name;
    QString translatedName;
    QString wcode;
    QVariant value;

    bool isValid(){ return !name.isEmpty();}
};

struct MetaValidationMessage{
    QString name;
    QString wcode;
    QString value;
};

// a meta ezekből a mezőkből áll
struct MetaField{
public:
    QString name;
    QString wcode;
    QMetaType type;
    int _offset;

    char* GetPtr(char* s){ return s+ _offset; }

    // ez megy ki az UI felé
    MetaValue GetMetaValue(char* s){
        // if(name == "alimedCode")
        // {
        //     zInfo("alimedCode");
        // }
        MetaValue mv(name, wcode, type);
        mv.value = GetValue(s);
        return mv;
    }

    QVariant GetValue(char* s){
        char* ptr = GetPtr(s);
        if(type.id()==QMetaType::QVariant){
            //QMetaType qvm = type;
            //QVariant v(qvm, ptr);
            qWarning("Do not use QVariant in model!");
            // QVariant* p = (QVariant*)s;

            // QVariant v(*p);
            // return v;
            return {};
        } else if(type.id()<QMetaType::User){
            QVariant v(type, ptr);
            return v;
        } else {
            QMetaType qvm = QMetaType(QMetaType::QVariant);
            bool cc = QMetaType::canConvert(type, qvm);
            QVariant v;
            if(cc){
                QMetaType::convert(type, ptr, qvm, &v);
            }
            return v;
        }
    }

};

struct IdMegnevIxs{
public:
    int id = -1;
    QList<int> megnev;
    int code = -1;
};

struct DataRowDefaultModel{
public:
    QString name;
    QList<IdMegnev> values;
};

struct FieldType{
    QMetaType declType;
    QMetaType keyType;
    QMetaType valueType;
};

template<typename T>
class Meta{
    QList<MetaField> _fields;
    IdMegnevIxs _idMegnevIxs;
    bool _verbose = true;
public:
    T _instance;

    QString _baseName;
    QString _baseWcode;

    void SetVerbose(bool v){_verbose = v;};

    // QString GetFieldName(const QString& name, char* field_ptr){
    //      return name;
    //  }    

    void AddField(const QString& name, const QMetaType& t, char* field_ptr)
    {
        // if(name == "alimedCode"){
        //       zInfo("alimedCode megvan");
        // }
        if(t.id() == QMetaType::QVariant){
            zWarning("AddField: Do not use QVariant "+name+" in model!");
        }
        MetaField f;
        f.name=name;
        f.wcode = _baseWcode+"::"+f.name;
        f.type = t;
        int offset = field_ptr - (char*)(&_instance);
        f._offset = offset;

        if(_verbose){
            QString msg = QStringLiteral("AddField:")
                          +QString::number(offset)
                          +" "+t.name() + '('+QString::number(t.sizeOf())+")"
                          +" "+name
                          +" to "+ _baseName;
            zInfo(msg);
        }

        _fields.append(f);        
    }

    bool Contains(const QString& name)
    {
        for(auto&a:_fields) if(a.name == name) return true;
        return false;
    }

    // Gets field names separated with comma
    // SqlRepo: Get, GetAll
    QString GetMetaFieldNames(){
        if(_fields.isEmpty()) return {};
        QString e;
        for(auto&a:_fields){
            //if(a.name.toLower()=="id") continue;
            if(!e.isEmpty()) e+=",";
            e+=a.name;
        }
        return e;
    }

    void AddBaseName(char const *y, unsigned long){
        _baseName = QString(y);
        _baseWcode = "WCodes::"+_baseName;
    }

    QString GetBaseTypeName() {
        return _baseName;
    }

    // QString GetFieldList_UPDATE(){
    //     if(_fields.isEmpty()) return {};
    //     QString e;
    //     int i = 0;
    //     for(auto&a:_fields){
    //         if(a.name.toLower()=="id") continue;
    //         if(!e.isEmpty()) e+=",";
    //         e+=a.name+"=:"+a.name;
    //     }
    //     return e;
    // }


    MetaField* GetMetaField(const QString& name){
        for(auto&a:_fields){
            if(a.name==name) return &a;
        }
        return nullptr;
    }

    // Parses T from a list of MetaValue
    // SqlRepo: Get, GetAll
    T FromMetaValues(const QList<MetaValue>& metaValues){
        T s;
        for(auto&m:metaValues){
            // if(m.name == "alimedCode"){
            //      zInfo("alimedCode megvan");
            // }
            MetaField* f = GetMetaField(m.name);            
            if(f){
                char* ptr = f->GetPtr((char*)&s);
                auto typeId = f->type.id();

                if(typeId==QMetaType::QVariant){
                    qWarning("Do not use QVariant in model!");
                    // két QVariantot underlying type alapján
                    // QMetaType qvm = m.value.metaType();
                    // QVariant* ptr2 = (QVariant*)ptr;
                    // QMetaType mt = ptr2->metaType();
                    // QVariant a(m.value);
                    // bool cc = a.canConvert(mt);
                    // if(cc){
                    //     bool ok = a.convert(mt);
                    //     if(ok)
                    //     {
                    //         ptr2->setValue(a);
                    //     }
                    // } else{
                    //     QString msg = QStringLiteral("No converter registered from ")
                    //     +qvm.name()+" to "+ f->type.name();
                    //     zWarning(msg);
                    // }
                    //zInfo("alimedCode megvan");
                } else if(typeId<QMetaType::User){
                    // QVariant értékét underlying típusba
                    // fromtype, from, totype, to
                    QMetaType qvm = m.value.metaType();
                    bool cc = QMetaType::canConvert(qvm, f->type);
                    if(cc)
                    {
                        QMetaType::convert(qvm, m.value.constData(), f->type, ptr);
                    } else{
                        QString msg = QStringLiteral("No converter registered from ")
                                      +qvm.name()+" to "+ f->type.name();
                        zWarning(msg);
                    }
                } else{
                    //std::optional *e;
                    //user type
                    // QVariantot user típusba
                    QMetaType qvm = QMetaType(QMetaType::QVariant);
                    bool cc = QMetaType::canConvert(qvm, f->type);
                    if(cc)
                    {
                        QMetaType::convert(qvm, &m.value, f->type, ptr);
                    } else{
                        QString msg = QStringLiteral("No converter registered from ")
                        +qvm.name()+" to "+ f->type.name();
                        zWarning(msg);
                    }
                }
            }
        }
        return s;
    }

    QList<MetaValue> ToMetaValues(const T* s){
        QList<MetaValue> m;
        if(s){
            for (MetaField &f : _fields) {
                MetaValue mv =  f.GetMetaValue((char*)s);
                m.append(mv);
            }
        }
        return m;
    }

    QList<SQLHelper::SQLParam> ToMetaValues2(const T* s){
        QList<SQLHelper::SQLParam> m;
        if(s){
            int i=1;
            for (MetaField &f : _fields) {
                bool isId = f.name.toLower()=="id";
                MetaValue mv =  f.GetMetaValue((char*)s);

                SQLHelper::SQLParam p;
                p.paramName = isId?"id":"p"+QString::number(i++);
                p.fieldName = mv.name;
                p.fieldValue = mv.value;
                m.append(p);
            }
        }
        return m;
    }
    
    void MetaIdMegnevIndex(int i, const QList<int> m, int c){
        _idMegnevIxs.id = i;
        _idMegnevIxs.megnev = m;
        _idMegnevIxs.code = c;
    }
    
    IdMegnev ToIdMegnev(const T* s){
        IdMegnev e;
        if(_idMegnevIxs.id>-1){
            MetaField idf = _fields[_idMegnevIxs.id];
            MetaValue mv =  idf.GetMetaValue((char*)s);
            e.id = mv.value.toInt();
        }

        e.name.clear();
        for(auto &megnev:_idMegnevIxs.megnev){
            if(megnev>-1){
                MetaField idn = _fields[megnev];
                MetaValue mv2 =  idn.GetMetaValue((char*)s);
                if(!e.name.isEmpty()) e.name+=",";
                e.name += mv2.value.toString();
            }
        }

        if(_idMegnevIxs.code>-1){
            MetaField idc = _fields[_idMegnevIxs.code];
            MetaValue mv3 =  idc.GetMetaValue((char*)s);
            e.code = mv3.value.toString();
        }
        return e;
    }


    DataRowDefaultModel ToIdMegnevs(const QList<T>& data){
        DataRowDefaultModel e;
        e.name = _baseName;

        for(auto&a:data){
            IdMegnev i = a.ToIdMegnev();
            e.values.append(i);
        }

        return e;
    }

    // GUI_ADD
    MetaValue GetMetaValue(const T* s, const QString& fieldName){
        if(!s) return MetaValue("","",QMetaType());
        MetaField* field = s->GetMetaField(fieldName);
        if(!field) return MetaValue("","",QMetaType());
        MetaValue value = field->GetMetaValue((char*)s);
        return value;
    }

    QVariant GetValue(const T* s, const QString& fieldName){
        if(!s) return {};
        MetaField* field = s->GetMetaField(fieldName);
        if(!field) return {};
        QVariant value = field->GetValue((char*)s);
        return value;
    }
};


#endif // META_H
