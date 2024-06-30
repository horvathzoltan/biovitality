#ifndef META_H
#define META_H

#include "helpers/logger.h"
#include <QList>
#include <QMetaType>
#include <QString>
#include <QVariant>


#define AddMetaField(b) _meta.AddField(#b, QMetaType::fromType<decltype(_meta._instance.b)>(), (char*)(&_meta._instance.b));


struct MetaValue{
private:
    MetaValue(){};
public:
    MetaValue(const QString& _name, const QMetaType& type){
        name = _name;
        value = QVariant(type);
    }

    QString name;
    QVariant value;
};

struct MetaField{
public:
    QString name;
    QMetaType type;
    int _offset;

    char* GetPtr(char* s){ return s+ _offset; }

    MetaValue GetMetaValue(char* s){
        MetaValue mv(name, type);

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

    void AddField(const QString& name, const QMetaType& t, char* field_ptr)
    {
        MetaField f;
        f.name=name;
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

    QString GetFieldList_UPDATE(){
        if(_fields.isEmpty()) return {};
        QString e;
        int i = 0;
        for(auto&a:_fields){            
            if(a.name.toLower()=="id") continue;
            if(!e.isEmpty()) e+=",";
            e+=a.name+"=:"+a.name;
        }
        return e;
    }


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

    QMap<QString,QVariant> ToMetaValues2(const T* s){
        QMap<QString,QVariant> m;
        if(s){
            for (MetaField &f : _fields) {
                //if(f.name.toLower()=="id") continue;
                MetaValue mv =  f.GetMetaValue((char*)s);
                m.insert(mv.name, mv.value);
            }
        }
        return m;
    }

};


#endif // META_H
