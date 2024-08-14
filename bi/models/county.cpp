#include "county.h"

Meta<County> County::_meta;

void County::MetaInit()
{
    AddMetaField(id);
    AddMetaField(name);
    AddMetaField(KSH_code);
}

bool County::isValid()
{
    if(id<0) return false;
    if(name.isEmpty()) return false;
    return true;
}

County::County() {}

