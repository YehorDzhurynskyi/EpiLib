#include "EpiLib/pch.h"
#include "ClassRegistry.h"

#include "MetaObject.h"

namespace epi
{

const MetaClass* ClassRegistry_Type_Lookup(MetaTypeID typeID)
{
    const auto it = g_ClassRegistry.find(typeID);
    if (it == g_ClassRegistry.end())
    {
        assert(!"No such class has been registred");
        return nullptr;
    }

    return &it->second;
}

const MetaClass* ClassRegistry_Name_Lookup(const epiChar* typeName, epiSize_t len)
{
    for (const auto& [k, v] : g_ClassRegistry)
    {
        const epiChar* name = v.GetName();
        if (strlen(name) == len && strncmp(name, typeName, len) == 0)
        {
            return &v;
        }
    }

    return nullptr;
}

}
