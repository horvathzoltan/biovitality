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


class IdMegnev{
public:
    int id = -1;
    QString name;
    QString code;
};

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

struct MetaField{
public:
    QString name;
    QString wcode;
    QMetaType type;
    int _offset;

    char* GetPtr(char* s){ return s+ _offset; }

    MetaValue GetMetaValue(char* s){
        MetaValue mv(name, wcode, type);

        //char* ptr = GetPtr(s);
        mv.value = GetValue(s);
            //QVariant(type, ptr);
        //QMetaType::convert(type, ptr, type, &mv.value);

        return mv;
    }

    QVariant GetValue(char* s){
        char* ptr = GetPtr(s);
        QVariant v(type, ptr);

        return v;
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

    void AddField(const QString& name, const QMetaType& t, char* field_ptr)
    {
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

    QString GetFieldList(){
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


    MetaField* GetField(const QString& name){
        for(auto&a:_fields){
            if(a.name==name) return &a;
        }
        return nullptr;
    }

    T FromMetaValues(const QList<MetaValue>& metaValues){
        T s;
        for(auto&m:metaValues){
            MetaField* f = GetField(m.name);
            if(f){
                char* ptr = f->GetPtr((char*)&s);
                // fromtype, from, totype, to
                QMetaType::convert(m.value.metaType(), m.value.constData(), f->type, ptr);
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

    MetaValue GetMetaValue(const T* s, const QString& fieldName){
        if(!s) return {};
        MetaField* field = s->GetField(fieldName);
        if(!field) return {};
        MetaValue value = field->GetMetaValue((char*)s);
        return value;
    }
};


#endif // META_H
