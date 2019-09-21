#pragma once

#include "ClassRegistry.h"

namespace epi
{

using MetaPropertyID = epiHash_t;
enum class MetaTypeID : epiU32
{
    None = 0,

    Char,
    Bool,
    Byte,
    Float,
    Double,
    Size_t,
    U8,
    U16,
    U32,
    U64,
    S8,
    S16,
    S32,
    S64,

    Array,
    HashMap,
    Vec2,
    Vec3,
    Vec4,

    Handle,

    Object,

// CUSTOM TYPES
    Vessel,
    Bloodstream,
    Model,

    StaticVentricle,
    StaticRegulator,
    Sensor,
    StaticRegulatedVessel,
    StaticRegulatedBloodstream,
    StaticModel,

    DynamicVentricle,
    DynamicBloodstream,
    DynamicModel
};

class Object;
class MetaProperty final
{
public:
    //MetaProperty() = default;
    MetaProperty(MetaTypeID propertyTypeID,
                 epiSize_t offset,
                 MetaProperty* nestedMetaProperty);
    MetaProperty(const MetaProperty&) = delete;
    MetaProperty& operator=(const MetaProperty&) = delete;
    MetaProperty(MetaProperty&&);
    MetaProperty& operator=(MetaProperty&&);
    ~MetaProperty();

    epiBool IsValid() const;
    epiBool HasNested() const;

    MetaTypeID GetTypeID() const;

    epiByte* GetValue(const Object& object) const;

    MetaProperty* GetNestedMetaProperty();
    const MetaProperty* GetNestedMetaProperty() const;

protected:
    MetaTypeID m_PropertyTypeID;
    epiSize_t m_Offset;
    MetaProperty* m_NestedMetaProperty;
};

class MetaType
{
public:
    static epiBool IsFundamental(MetaTypeID typeID);
    static epiBool IsHandle(MetaTypeID typeID);
    static epiBool IsMultiDimensional(MetaTypeID typeID);
    static epiBool IsMultiDimensionalInplace(MetaTypeID typeID);
    static epiBool IsCompound(MetaTypeID typeID);

    static epiByte* GetElementByIndex(const epiByte* container, const MetaProperty& meta, epiS32 index);
    static epiByte* GetElementByHash(const epiByte* container, const MetaProperty& meta, epiHash_t hash);

    template<typename T>
    static MetaTypeID TypeOf();
};

struct MetaClassData
{
    void AddProperty(MetaPropertyID propertyID, MetaProperty&& metaProperty);

    std::map<MetaPropertyID, MetaProperty> Properties;
};

class MetaClass final
{
public:
    MetaClass(MetaClassData* classData, MetaTypeID typeID, MetaTypeID superTypeID, epiSize_t sizeOf);

    epiBool IsValid() const;

    const MetaProperty* GetProperty_FromBase(MetaPropertyID pid) const;
    const MetaProperty* GetProperty_FromDerived(MetaPropertyID pid) const;
    const MetaProperty* GetProperty_FromCurrent(MetaPropertyID pid) const;
    const MetaProperty* GetProperty(MetaPropertyID pid) const;

    MetaTypeID GetTypeID() const;
    const char* GetClassName() const;
    epiSize_t GetSizeOf() const;

protected:
    MetaClassData* m_ClassData;
    MetaTypeID m_TypeID;
    MetaTypeID m_SuperTypeID;
    epiSize_t m_SizeOf;
};

template<typename T>
MetaTypeID MetaType::TypeOf()
{
    if constexpr (std::is_fundamental<T>::value)
    {
        if constexpr (std::is_same<epiChar, T>::value) return MetaTypeID::Char;
        else if constexpr (std::is_same<epiBool, T>::value) return MetaTypeID::Bool;
        else if constexpr (std::is_same<epiByte, T>::value) return MetaTypeID::Byte;
        else if constexpr (std::is_same<epiFloat, T>::value) return MetaTypeID::Float;
        else if constexpr (std::is_same<epiDouble, T>::value) return MetaTypeID::Double;
        else if constexpr (std::is_same<epiSize_t, T>::value) return MetaTypeID::Size_t;
        else if constexpr (std::is_same<epiU8, T>::value) return MetaTypeID::U8;
        else if constexpr (std::is_same<epiU16, T>::value) return MetaTypeID::U16;
        else if constexpr (std::is_same<epiU32, T>::value) return MetaTypeID::U32;
        else if constexpr (std::is_same<epiU64, T>::value) return MetaTypeID::U64;
        else if constexpr (std::is_same<epiS8, T>::value) return MetaTypeID::S8;
        else if constexpr (std::is_same<epiS16, T>::value) return MetaTypeID::S16;
        else if constexpr (std::is_same<epiS32, T>::value) return MetaTypeID::S32;
        else if constexpr (std::is_same<epiS64, T>::value) return MetaTypeID::S64;
    }
    else
    {
        static_assert(std::is_base_of<Object, T>::value);
        return T::TypeID;
    }

    return MetaTypeID::None;
}

}
