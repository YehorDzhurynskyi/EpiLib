#pragma once

#include "MetaObject.h"
#include <nlohmann/json.hpp>

#define epiEmitObject(_ClassName, _Super)                                               \
                                                                                        \
using super = _Super;                                                                   \
                                                                                        \
static MetaClassData EmitMetaClassData();                                               \
static MetaClassData _ClassName##_MetaClassData;                                        \
                                                                                        \
const MetaClass& GetMetaClass() const override                                          \
{                                                                                       \
    assert(g_ClassRegistry.find(MetaTypeID::##_ClassName) != g_ClassRegistry.end());    \
    return *ClassRegistry_Type_Lookup(MetaTypeID::##_ClassName);                        \
}                                                                                       \
                                                                                        \
static inline MetaTypeID TypeID = MetaTypeID::##_ClassName;                             \
                                                                                        \
epiBool Is(MetaTypeID rhs) const override                                               \
{                                                                                       \
    return rhs == MetaTypeID::##_ClassName || super::Is(rhs);                           \
}                                                                                       \
                                                                                        \
void Serialization(json_t& json) override;                                              \
void Deserialization(const json_t& json) override;                                      \
                                                                                        \

namespace epi
{

using json_t = nlohmann::json;

class Object
{
public:
    static MetaClassData EmitMetaClassData();
    static MetaClassData Object_MetaClassData;
    static inline MetaTypeID TypeID = MetaTypeID::Object;

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

    virtual epiString ToString() const;

protected:
    virtual void Serialization(json_t& json) {}
    virtual void Deserialization(const json_t& json) {}

    virtual void OnPreSerialization() {}
    virtual void OnPreDeserialization() {}
    virtual void OnPostSerialization() {}
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
