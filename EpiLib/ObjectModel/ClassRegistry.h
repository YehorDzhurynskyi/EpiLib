#pragma once

namespace epi
{

enum class MetaTypeID : epiU32;
class MetaClass;

extern std::map<MetaTypeID, MetaClass> g_ClassRegistry;
extern std::map<MetaTypeID, const epiChar*> g_ClassNameRegistry;

const MetaClass* ClassRegistry_Lookup(MetaTypeID typeID);

const epiChar* ClassNameRegistry_Lookup(MetaTypeID typeID);
const MetaClass* ClassNameRegistry_Lookup(const epiChar* typeName, epiSize_t len);

}
