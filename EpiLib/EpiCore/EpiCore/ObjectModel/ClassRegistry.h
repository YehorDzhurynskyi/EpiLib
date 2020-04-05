#pragma once

namespace epi
{

enum class MetaTypeID : epiU32;
class MetaClass;

extern std::map<MetaTypeID, MetaClass> g_ClassRegistry;

const MetaClass* ClassRegistry_Type_Lookup(MetaTypeID typeID);
const MetaClass* ClassRegistry_Name_Lookup(const epiChar* typeName, epiSize_t len);

template<typename T>
MetaClass& Register()
{
    auto& [it, exists] = g_ClassRegistry.try_emplace(T::TypeID, std::move(T::EmitMetaClass()));
    assert(!exists);
    return it->second;
}

template<typename T>
const MetaClass& ClassRegistry_GetMetaClass()
{
    static MetaClass t = Register<T>();
    return t;
}

}
