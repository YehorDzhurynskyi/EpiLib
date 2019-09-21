#include "EpiLib/pch.h"
#include "ClassRegistry.h"

#include "MetaObject.h"

namespace epi
{

const MetaClass* ClassRegistry_Lookup(MetaTypeID typeID)
{
    const auto it = g_ClassRegistry.find(typeID);
    if (it == g_ClassRegistry.end())
    {
        assert(!"No such class has been registred");
        return nullptr;
    }

    return &it->second;
}

const epiChar* ClassNameRegistry_Lookup(MetaTypeID typeID)
{
    const auto it = g_ClassNameRegistry.find(typeID);
    if (it == g_ClassNameRegistry.end())
    {
        assert(!"No such class has been registred");
        return nullptr;
    }

    return it->second;
}

const MetaClass* ClassNameRegistry_Lookup(const epiChar* typeName, epiSize_t len)
{
    for (const auto& [k, v] : g_ClassNameRegistry)
    {
        if (strlen(v) == len && strncmp(v, typeName, len) == 0)
        {
            return ClassRegistry_Lookup(k);
        }
    }

    return nullptr;
}

}
