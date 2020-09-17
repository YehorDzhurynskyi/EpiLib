#pragma once

#include "MetaObject.h"
#include <nlohmann/json.hpp>

EPI_NAMESPACE_BEGIN()

using json_t = nlohmann::json;

class Object
{
public:
    static MetaClass EmitMetaClass();
    constexpr static epiMetaTypeID TypeID{epiHashCompileTime(Object)};

public:
    Object() = default;
    Object(const Object&) = default;
    Object(Object&&) = default;
    Object& operator=(const Object&) = default;
    Object& operator=(Object&&) = default;
    virtual ~Object() = default;

    virtual const MetaClass& GetMetaClass() const;
    virtual epiBool Is(epiMetaTypeID rhs) const;

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

// TODO: move to a different place
template<typename T, typename U>
T* epiAs(U* rhs)
{
    static_assert(!std::is_pointer_v<T> && !std::is_pointer_v<U>);
    static_assert(!std::is_reference_v<T> && !std::is_reference_v<U>);

    static_assert(std::is_base_of_v<Object, std::decay_t<U>>);
    static_assert(std::is_base_of_v<Object, std::decay_t<T>>);
    static_assert(std::is_base_of_v<std::decay_t<U>, std::decay_t<T>>);

    if (!rhs->Is(T::TypeID))
    {
        return nullptr;
    }

    return static_cast<T*>(rhs);
}

EPI_NAMESPACE_END()
