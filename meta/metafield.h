#ifndef METAFIELD_H
#define METAFIELD_H

#include "helpers/logger.h"
#include "metavalue.h"
#include <QMetaType>


struct MetaValidationMessage{
    QString name;
    QString wcode;
    QString value;

public:
    QString ToString(){
        return wcode+": "+name+"="+value;
    }
};

enum RefType{
    None, R_1N, R_NM
};

struct MetaFieldBase{
public:
    QString name;
    QMetaType type;
    //RefType refType;

    QString ToString(){return name+' '+type.name();}
};

// ez megy ki az UI felé
struct MetaField : public MetaFieldBase{
public:
    QString wcode;
    int _offset;
    char* GetPtr(char* s){ return s+ _offset; }
    
    // ez megy ki az UI felé
    MetaValue GetMetaValue(char* s){
        // if(name == "alimedCode")
        // {
        //      zInfo("alimedCode");
        // }
        MetaValue mv(name, wcode, type);//, refType);
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
                bool ok = QMetaType::convert(type, ptr, qvm, &v);
                if(!ok){
                    zInfo("cc err");
                }
            }
            return v;
        }
    }
    
};

#endif // METAFIELD_H
