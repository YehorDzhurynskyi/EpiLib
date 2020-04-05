#pragma once

#include "ClassRegistry.h"
#include "EmitMeta.h"

namespace epi
{

using MetaPropertyID = epiHash_t;
enum class MetaTypeID : epiU32
{
    None = 0,

    epiChar,
    epiBool,
    epiByte,
    epiFloat,
    epiDouble,
    epiSize_t,
    epiString,
    epiU8,
    epiU16,
    epiU32,
    epiU64,
    epiS8,
    epiS16,
    epiS32,
    epiS64,

    epiArray,
    epiPtrArray,
    HashMap,
    Vec2,
    Vec3,
    Vec4,

    Handle,

    Object,

// CUSTOM TYPES
    Test,
    Vessel,
    Bloodstream,
    Model,
    StaticVentricle,
    StaticRegulator,
    Sensor,
    StaticRegulatedVessel,
    StaticRegulatedBloodstream,
    StaticModel,
    Simulation,
    SimulationWard,
    DynamicVentricle,
    DynamicBloodstream,
    DynamicModel,
    StaticRegulatedModel,
    ModelItem
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

class MetaClassData
{
public:
    void AddProperty(MetaPropertyID propertyID, MetaProperty&& metaProperty);

    const epiSize_t GetPropertiesCount() const;
    const MetaProperty* GetPropertyAt(epiS32 index) const;
    const MetaProperty* GetPropertyBy(MetaPropertyID pid) const;

public:
    auto begin() -> typename std::vector<MetaProperty>::iterator { return m_Properties.begin(); }
    auto end() -> typename std::vector<MetaProperty>::iterator { return m_Properties.end(); }
    auto begin() const -> typename std::vector<MetaProperty>::const_iterator { return m_Properties.cbegin(); }
    auto end() const -> typename std::vector<MetaProperty>::const_iterator { return m_Properties.cend();}
    auto rbegin() -> typename std::vector<MetaProperty>::reverse_iterator { return m_Properties.rbegin(); }
    auto rend() -> typename std::vector<MetaProperty>::reverse_iterator { return m_Properties.rend(); }
    auto crbegin() const -> typename std::vector<MetaProperty>::const_reverse_iterator { return m_Properties.crbegin(); }
    auto crend() const -> typename std::vector<MetaProperty>::const_reverse_iterator { return m_Properties.crend(); }

protected:
    std::vector<MetaProperty> m_Properties;
    std::map<MetaPropertyID, epiS32> m_ToIndexTable;
};

class MetaClass final
{
public:
    MetaClass(MetaClassData&& classData, MetaTypeID typeID, MetaTypeID superTypeID, epiSize_t sizeOf, const epiChar* name);

    epiBool IsValid() const;

    const MetaProperty* GetProperty_FromBase(MetaPropertyID pid) const;
    const MetaProperty* GetProperty_FromDerived(MetaPropertyID pid) const;
    const MetaProperty* GetProperty_FromCurrent(MetaPropertyID pid) const;
    const MetaProperty* GetProperty(MetaPropertyID pid) const;

    const MetaClassData& GetClassData() const;
    MetaTypeID GetTypeID() const;
    MetaTypeID GetSuperTypeID() const;
    const epiChar* GetName() const;
    epiSize_t GetSizeOf() const;

protected:
    MetaClassData m_ClassData;
    MetaTypeID m_TypeID;
    MetaTypeID m_SuperTypeID;
    epiSize_t m_SizeOf;
    epiString m_Name;
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
