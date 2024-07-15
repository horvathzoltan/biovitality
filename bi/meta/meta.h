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

struct MetaValue{
private:
    MetaValue(){};
public:
    MetaValue(const QString& _name, const QString& _wcode,const QMetaType& type ){
        name = _name;
        wcode = _wcode;
        value = QVariant(type);
    }

    QString name;
    QString translatedName;
    QString wcode;
    QVariant value;
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

        char* ptr = GetPtr(s);
        mv.value = QVariant(type, ptr);
        //QMetaType::convert(type, ptr, type, &mv.value);

        return mv;
    }
};

template<typename T>
class Meta{
    QList<MetaField> _fields;
public:
    T _instance;

    QString _baseName;
    QString _baseWcode;

    void AddField(const QString& name, const QMetaType& t, char* field_ptr)
    {
        MetaField f;
        f.name=name;
        f.wcode = _baseWcode+"::"+f.name;
        f.type = t;
        int offset = field_ptr - (char*)(&_instance);
        f._offset = offset;

        QString msg = QStringLiteral("AddField:")
                      +QString::number(offset)
                      +" "+t.name() + '('+QString::number(t.sizeOf())+")"
                      +" "+name;
        zInfo(msg);
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

};


#endif // META_H
