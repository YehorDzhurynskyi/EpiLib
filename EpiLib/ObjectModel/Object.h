#pragma once

#include "MetaObject.h"
#include <rapidjson/document.h>

#define epiEmitObject(_ClassName, _Super)                                               \
                                                                                        \
using super = _Super;                                                                   \
                                                                                        \
using _ClassName##_MetaClassData = MetaClassData;                                       \
friend _ClassName##_MetaClassData CreateMetaClassData_##_ClassName();                   \
                                                                                        \
const MetaClass& GetMetaClass() const override                                          \
{                                                                                       \
    assert(g_ClassRegistry.find(MetaTypeID::##_ClassName) != g_ClassRegistry.end());    \
    return *ClassRegistry_Lookup(MetaTypeID::##_ClassName);                             \
}                                                                                       \
                                                                                        \
static inline MetaTypeID TypeID = MetaTypeID::##_ClassName;                             \
                                                                                        \
epiBool Is(MetaTypeID rhs) const override                                               \
{                                                                                       \
    return rhs == MetaTypeID::##_ClassName || super::Is(rhs);                           \
}                                                                                       \
                                                                                        \
void Serialization(json_t& json) const override;                                        \
void Deserialization(const json_t& json) override;                                      \
                                                                                        \

namespace epi
{

using json_t = rapidjson::Value;

class Object
{
public:
    using Object_MetaClassData = MetaClassData;
    friend Object_MetaClassData CreateMetaClassData_Object();

public:
    Object() = default;
    Object(const Object&) = default;
    Object(Object&&) = default;
    Object& operator=(const Object&) = default;
    Object& operator=(Object&&) = default;
    virtual ~Object() = default;

    virtual const MetaClass& GetMetaClass() const;
    virtual epiBool Is(MetaTypeID rhs) const;

public:
    void Serialize(json_t& json);
    void Deserialize(const json_t& json);

protected:
    virtual void Serialization(json_t& json) const = 0;
    virtual void Deserialization(const json_t& json) = 0;

    virtual void OnPreSerialization() {}
    virtual void OnPostDeserialization() {}
};

template<typename T, typename U>
T* As(U* rhs)
{
    static_assert(std::is_base_of<Object, U>::value);
    static_assert(std::is_base_of<Object, T>::value);
    static_assert(std::is_base_of<U, T>::value);

    if (!rhs->Is(T::TypeID))
    {
        return nullptr;
    }

    return static_cast<T*>(rhs);
}

}
