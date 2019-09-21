#include "EpiLib/pch.h"
#include "Object.h"

namespace epi
{

const MetaClass& Object::GetMetaClass() const
{
    assert(g_ClassRegistry.find(MetaTypeID::Object) != g_ClassRegistry.end());
    return *ClassRegistry_Lookup(MetaTypeID::Object);
}

epiBool Object::Is(MetaTypeID rhs) const
{
    return rhs == MetaTypeID::Object;
}

void Object::Serialize(json_t& json)
{
    OnPreSerialization();
    Serialization(json);
}

void Object::Deserialize(const json_t& json)
{
    Deserialization(json);
    OnPostDeserialization();
}

}
