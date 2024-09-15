#include "address.h"

Meta<Address> Address::_meta;

Address::Address() {}

void Address::MetaInit()
{
    AddMetaBase(Address);
    AddMetaField(id);
    AddMetaField(postalCode);
    AddMetaField(settlementName);
    AddMetaField(publicAreaName);
    AddMetaField(excelId);
}

bool Address::isValid()
{
    if(id<0) return false;
    if(settlementName.isEmpty()) return false;
    if(publicAreaName.isEmpty()) return false;
    //if(units<=0) return false; // ha minusz a darabszám, stornós
    //if(netPrice<=0) return false; // ha minusz az ár, stornós
    return true;
}
