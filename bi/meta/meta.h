#ifndef META_H
#define META_H

#include "helpers/logger.h"
#include <QList>
#include <QMetaType>
#include <QString>
#include <QVariant>


#define AddMetaField(b) _meta.AddField(#b, QMetaType::fromType<decltype(_meta._instance.b)>(), (char*)(&_meta._instance.b));


struct MetaField{
public:
    QString name;
    QMetaType type;
    int _offset;
};

struct MetaValue{
public:
    QString name;
    QVariant value;
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
        for(auto&a:_fields){
            //if(a.name.toLower()=="id") continue;
            if(!e.isEmpty()) e+=",";
            e+=a.name+":="+a.name;
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
                QVariant v = m.value;

                char* ptr = ((char*)&s) + f->_offset;
                QMetaType::convert(v.metaType(), v.constData(), f->type, ptr);
            }
        }
        return s;
    }
};


#endif // META_H
