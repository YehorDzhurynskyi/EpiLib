#include "Object.h"

namespace epi
{

MetaClass Object::EmitMetaClass()
{
    MetaClassData data;

    return MetaClass(std::move(data), epiHashCompileTime(Object), MetaTypeID_None, sizeof(Object), "Object");
}

const MetaClass& Object::GetMetaClass() const
{
    return ClassRegistry_GetMetaClass<Object>();
}

epiBool Object::Is(MetaTypeID rhs) const
{
    return rhs == Object::TypeID;
}

void Object::Serialize(json_t& json)
{
    OnPreSerialization();
    Serialization(json);
    OnPostSerialization();
}

void Object::Deserialize(const json_t& json)
{
    OnPreDeserialization();
    Deserialization(json);
    OnPostDeserialization();
}

epiString Object::ToString() const
{
    return GetMetaClass().GetName();
}

}
