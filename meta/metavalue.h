#ifndef METAVALUE_H
#define METAVALUE_H

#include <QString>
#include <QVariant>

enum RefType{
    None, R_1N, R_NM
};

struct MetaValue{
private:
    MetaValue(){};    
public:
    MetaValue(const QString& _name, const QString& _wcode,const QMetaType& _type, RefType _refType)
    {
        metaField_name = _name;
        wcode = _wcode;
        value = QVariant(_type);
        type = _type;
        refType = _refType;
    }
    
    MetaValue(const QString& _name, const QString& _wcode,const QVariant& _value, RefType _refType)
    {
        metaField_name = _name;
        wcode = _wcode;
        value = _value;
        type = _value.metaType();
        refType = _refType;
    }
    
    // ez köti a MetaField-hez, talán jobb lenne egy index
    // név vélkül viszont nem tudjuk megnevezni hibaüzenetben
    QString metaField_name;
    //int metaField_ix;
    
    QString wcode;
    QString translatedName;
    
    QVariant value;
    QMetaType type;

    RefType refType;
    
    bool isValid(){ return !metaField_name.isEmpty();}
};

struct MetaValidationMessage{
    QString name;
    QString wcode;
    QString value;

public:
    QString ToString(){
        return wcode+": "+name+"="+value;
    }
};

#endif // METAVALUE_H
