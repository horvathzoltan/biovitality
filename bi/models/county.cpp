#include "county.h"

Meta<County> County::_meta;
QList<County> County::_data = {
    {5,"Budapest","01"},
    {2,"Baranya vármegye","02"},
    {1,"Bács-Kiskun vármegye","03"},
    {3,"Békés vármegye","04"},
    {4,"Borsod-Abaúj-Zemplén vármegye","05"},
    {6,"Csongrád-Csanád vármegye","06"},
    {7,"Fejér vármegye","07"},
    {8,"Győr-Moson-Sopron vármegye","08"},
    {9,"Hajdú-Bihar vármegye","09"},
    {10,";Heves vármegye","10"},
    {12,";Komárom-Esztergom vármegye","11"},
    {13,";Nógrád vármegye","12"},
    {14,";Pest vármegye","13"},
    {20,";Somogy vármegye","14"},
    {15,";Szabolcs-Szatmár-Bereg vármegye","15"},
    {11,";Jász-Nagykun Szolnok vármegye","16"},
    {16,";Tolna vármegye","17"},
    {17,";Vas vármegye","18"},
    {18,";Veszprém vármegye","19"},
    {19,";Zala vármegye","20"}
};


void County::MetaInit()
{
    AddMetaBase(County);
    AddMetaField(id); // id
    AddMetaField(name); //megnev
    AddMetaField(KSH_code); //code

    _meta.MetaIdMegnevIndex(0,1,2);
    //AddMetaIdMegnevIndex(id, name, KSH_code);

}

bool County::isValid()
{
    if(id<0) return false;
    if(name.isEmpty()) return false;
    return true;
}

DataRowDefaultModel County::To_DataRowDefaultModel()
{
    DataRowDefaultModel e;
    e.name = _meta._baseName;

    for(auto&a:_data){
        IdMegnev i = a.ToIdMegnev();
        e.values.append(i);
    }

    return e;
}

County::County() {}

County::County(int i, const QString &n, const QString &k)
{
    id = i; name = n; KSH_code = k;
}

