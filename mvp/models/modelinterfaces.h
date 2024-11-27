#ifndef MODELINTERFACES_H
#define MODELINTERFACES_H

#include "meta/meta.h"

template<class T>
class I_Meta
{
public:
    I_Meta(){}
public:
    void __attribute__((used)) Check_I_Meta()
    {
        //Meta<T> *_meta_Check = &T::_meta;

        [[maybe_unused]] void (*MetaInit_Check)() = &T::MetaInit;
        [[maybe_unused]] bool (T::*isValid_Check)() = &T::isValid;
    }
};

template<class T>
class I_SQLRepo
{
public:
    I_SQLRepo(){}
public:
    void __attribute__((used)) Check_I_SQLRepo()
    {
        [[maybe_unused]] T (*FromMetaValues_Check)(const QList<MetaValue> &v) = &T::FromMetaValues;
    }
};

template<class T>
class I_CSVImport{
public:
    I_CSVImport(){}
private:
    void __attribute__((used)) Check_I_CSVImport()
    {
        [[maybe_unused]] QVariant (T::*GetValue_Check)(const QString& name) const = &T::GetValue;
        [[maybe_unused]] MetaField* (*GetField_Check)(const QString& name) = &T::GetField;
        [[maybe_unused]] QString (*GetMetaFieldList_Check)() = &T::GetMetaFieldList;
        [[maybe_unused]] QList<SQLHelper::SQLParam> (T::*GetQueryParams_Check)()const = &T::GetQueryParams;
        [[maybe_unused]] QList<T> (*CSV_Import_Check)(const QList<QVarLengthArray<QString>>& records) = &T::CSV_Import;
    }
};

#endif // MODELINTERFACES_H
