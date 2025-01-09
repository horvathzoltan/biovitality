#ifndef METAVALUE_H
#define METAVALUE_H

#include <QString>
#include <QVariant>


struct MetaValue{
private:
    MetaValue(){};    
public:
    MetaValue(const QString& _name, const QString& _wcode,const QMetaType& type)// , RefType _refType)
    {
        metaField_name = _name;
        wcode = _wcode;
        value = QVariant(type);
        //  refType = _refType;
    }
    
    MetaValue(const QString& _name, const QString& _wcode,const QVariant& _value)// , RefType _refType)
    {
        metaField_name = _name;
        wcode = _wcode;
        value = _value;
        //  refType = _refType;
    }
    
    // ez köti a MetaField-hez, talán jobb lenne egy index
    // név vélkül viszont nem tudjuk megnevezni hibaüzenetben
    QString metaField_name;
    //int metaField_ix;
    
    QString wcode;
    QString translatedName;
    
    QVariant value;
    //RefType refType;
    
    bool isValid(){ return !metaField_name.isEmpty();}
};

#endif // METAVALUE_H
