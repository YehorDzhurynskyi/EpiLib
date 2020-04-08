#pragma once

#include "EpiCore/Hash.h"

namespace epi
{

using MetaPropertyID = epiHash_t;
using MetaTypeID = epiHash_t;

class Object;
class MetaProperty final
{
    friend MetaProperty epiMetaProperty_Impl(const epiChar* name, epiSize_t offset, MetaTypeID typeID, MetaTypeID nestedTypeID);

private:
    MetaProperty() = default;

public:
    MetaProperty(const MetaProperty&) = default;
    MetaProperty& operator=(const MetaProperty&) = default;
    MetaProperty(MetaProperty&&) = default;
    MetaProperty& operator=(MetaProperty&&) = default;
    ~MetaProperty() = default;

    epiBool IsValid() const;
    epiBool HasNested() const;

    MetaTypeID GetTypeID() const;
    MetaTypeID GetNestedTypeID() const;

    epiByte* GetValue(const Object& object) const;

protected:
    MetaTypeID m_TypeID;
    MetaTypeID m_NestedTypeID;
    epiSize_t m_Offset;

#ifdef epiUSE_METAPROPERTY_NAME
public:
    const epiChar* GetName() const { return m_Name.c_str(); }

protected:
    void SetName(const epiChar* name) { m_Name = name; }

protected:
    epiString m_Name;
#else // epiUSE_METAPROPERTY_NAME
public:
    const epiChar* GetName() const { return ""; }

protected:
    void SetName(const epiChar* name) {}
#endif // epiUSE_METAPROPERTY_NAME
};

#define epiMetaProperty(_Name, _Owner, _Type, _NestedType) \
    { \
        auto m = epiMetaProperty_Impl(#_Name, \
                                      offsetof(_Owner, m_##_Name), \
                                      _Type, \
                                      _NestedType); \
        data.AddProperty(epiHashCompileTime(#_Name), std::move(m)); \
    } \

inline MetaProperty epiMetaProperty_Impl(const epiChar* name, epiSize_t offset, MetaTypeID typeID, MetaTypeID nestedTypeID)
{
    MetaProperty prty;

    prty.SetName(name);
    prty.m_Offset = offset;
    prty.m_TypeID = typeID;
    prty.m_NestedTypeID = nestedTypeID;

    assert(prty.IsValid());

    return prty;
}

enum : MetaTypeID
{
    MetaTypeID_epiNone = 0,

    MetaTypeID_epiChar = epiHashCompileTime(epiChar),
    MetaTypeID_epiBool = epiHashCompileTime(epiBool),
    MetaTypeID_epiByte = epiHashCompileTime(epiByte),
    MetaTypeID_epiFloat = epiHashCompileTime(epiFloat),
    MetaTypeID_epiDouble = epiHashCompileTime(epiDouble),
    MetaTypeID_epiSize_t = epiHashCompileTime(epiSize_t),
    MetaTypeID_epiString = epiHashCompileTime(epiString),
    MetaTypeID_epiU8 = epiHashCompileTime(epiU8),
    MetaTypeID_epiU16 = epiHashCompileTime(epiU16),
    MetaTypeID_epiU32 = epiHashCompileTime(epiU32),
    MetaTypeID_epiU64 = epiHashCompileTime(epiU64),
    MetaTypeID_epiS8 = epiHashCompileTime(epiS8),
    MetaTypeID_epiS16 = epiHashCompileTime(epiS16),
    MetaTypeID_epiS32 = epiHashCompileTime(epiS32),
    MetaTypeID_epiS64 = epiHashCompileTime(epiS64),

    MetaTypeID_epiArray = epiHashCompileTime(epiArray),
    MetaTypeID_epiPtrArray = epiHashCompileTime(epiPtrArray),

    MetaTypeID_epiHandle = epiHashCompileTime(epiHandle)
};

class MetaType
{
public:
    static epiBool IsFundamental(MetaTypeID typeID);
    static epiBool IsHandle(MetaTypeID typeID);
    static epiBool IsMultiDimensional(MetaTypeID typeID);
    static epiBool IsMultiDimensionalInplace(MetaTypeID typeID);
    static epiBool IsCompound(MetaTypeID typeID);

#if 0
    static epiByte* GetElementByIndex(const epiByte* container, const MetaProperty& meta, epiS32 index);
    static epiByte* GetElementByHash(const epiByte* container, const MetaProperty& meta, epiHash_t hash);
#endif
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
