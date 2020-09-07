#pragma once

#include "EpiCore/Hash.h"

namespace epi
{

using epiMetaPropertyID = epiHash_t;
using epiMetaTypeID = epiHash_t;

class Object;
class MetaProperty final
{
private:
    MetaProperty() = default;

public:
    MetaProperty(const MetaProperty&) = default;
    MetaProperty& operator=(const MetaProperty&) = default;
    MetaProperty(MetaProperty&&) = default;
    MetaProperty& operator=(MetaProperty&&) = default;
    ~MetaProperty() = default;

    union Flags
    {
        static constexpr epiU64 MaskReadCallback  = (1ull << 0);
        static constexpr epiU64 MaskWriteCallback = (1ull << 1);
        static constexpr epiU64 MaskReadOnly      = (1ull << 2);
        static constexpr epiU64 MaskWriteOnly     = (1ull << 3);

        struct
        {

            epiU64 ReadCallback  : 1;
            epiU64 WriteCallback : 1;
            epiU64 ReadOnly: 1;
            epiU64 WriteOnly : 1;
            epiU64 _                : 60;
        };
        epiU64 Mask;
    };
    static_assert(sizeof(Flags) == sizeof(epiU64));

    epiBool IsValid() const;
    epiBool HasNested() const;

    epiMetaTypeID GetTypeID() const;
    epiMetaTypeID GetNestedTypeID() const;
    Flags GetFlags() const;

protected:
    Flags m_Flags;
    epiMetaTypeID m_TypeID;
    epiMetaTypeID m_NestedTypeID;
    void* m_PtrRead;
    void* m_PtrWrite;

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

public:
    friend class PropertyPointer;
    friend MetaProperty epiMetaProperty(const epiChar*, void*, void*, epiU64, epiMetaTypeID, epiMetaTypeID);
};

inline MetaProperty epiMetaProperty(const epiChar* name,
                                    void* ptrRead,
                                    void* ptrWrite,
                                    epiU64 flags,
                                    epiMetaTypeID typeID,
                                    epiMetaTypeID nestedTypeID)
{
    MetaProperty prty;

    prty.SetName(name);
    prty.m_PtrRead = ptrRead;
    prty.m_PtrWrite = ptrWrite;
    prty.m_Flags.Mask = flags;
    prty.m_TypeID = typeID;
    prty.m_NestedTypeID = nestedTypeID;

    assert(prty.IsValid());

    return prty;
}

enum : epiMetaTypeID
{
    epiMetaTypeID_None = 0,
    epiMetaTypeID_Ptr = epiHashCompileTime(Ptr),

    epiMetaTypeID_epiChar = epiHashCompileTime(epiChar),
    epiMetaTypeID_epiWChar = epiHashCompileTime(epiWChar),
    epiMetaTypeID_epiBool = epiHashCompileTime(epiBool),
    epiMetaTypeID_epiByte = epiHashCompileTime(epiByte),
    epiMetaTypeID_epiFloat = epiHashCompileTime(epiFloat),
    epiMetaTypeID_epiDouble = epiHashCompileTime(epiDouble),
    epiMetaTypeID_epiSize_t = epiHashCompileTime(epiSize_t),
    epiMetaTypeID_epiString = epiHashCompileTime(epiString),
    epiMetaTypeID_epiWString = epiHashCompileTime(epiWString),
    epiMetaTypeID_epiU8 = epiHashCompileTime(epiU8),
    epiMetaTypeID_epiU16 = epiHashCompileTime(epiU16),
    epiMetaTypeID_epiU32 = epiHashCompileTime(epiU32),
    epiMetaTypeID_epiU64 = epiHashCompileTime(epiU64),
    epiMetaTypeID_epiS8 = epiHashCompileTime(epiS8),
    epiMetaTypeID_epiS16 = epiHashCompileTime(epiS16),
    epiMetaTypeID_epiS32 = epiHashCompileTime(epiS32),
    epiMetaTypeID_epiS64 = epiHashCompileTime(epiS64),

    epiMetaTypeID_epiArray = epiHashCompileTime(epiArray),
    epiMetaTypeID_epiPtrArray = epiHashCompileTime(epiPtrArray),

    epiMetaTypeID_epiVec2f = epiHashCompileTime(epiVec2f),
    epiMetaTypeID_epiVec2d = epiHashCompileTime(epiVec2d),
    epiMetaTypeID_epiVec2s = epiHashCompileTime(epiVec2s),
    epiMetaTypeID_epiVec2u = epiHashCompileTime(epiVec2u),

    epiMetaTypeID_epiVec3f = epiHashCompileTime(epiVec3f),
    epiMetaTypeID_epiVec3d = epiHashCompileTime(epiVec3d),
    epiMetaTypeID_epiVec3s = epiHashCompileTime(epiVec3s),
    epiMetaTypeID_epiVec3u = epiHashCompileTime(epiVec3u),

    epiMetaTypeID_epiVec4f = epiHashCompileTime(epiVec4f),
    epiMetaTypeID_epiVec4d = epiHashCompileTime(epiVec4d),
    epiMetaTypeID_epiVec4s = epiHashCompileTime(epiVec4s),
    epiMetaTypeID_epiVec4u = epiHashCompileTime(epiVec4u),

    epiMetaTypeID_epiMat2x2f = epiHashCompileTime(epiMat2x2f),
    epiMetaTypeID_epiMat3x3f = epiHashCompileTime(epiMat3x3f),
    epiMetaTypeID_epiMat4x4f = epiHashCompileTime(epiMat4x4f)
};

class MetaType
{
public:
    static epiBool IsFundamental(epiMetaTypeID typeID);
    static epiBool IsString(epiMetaTypeID typeID);
    static epiBool IsMultiDimensional(epiMetaTypeID typeID);
    static epiBool IsMultiDimensionalInplace(epiMetaTypeID typeID);
    static epiBool IsCompound(epiMetaTypeID typeID);

    template<typename T>
    static constexpr epiMetaTypeID TypeOf();

    template<typename T>
    static constexpr epiBool IsFundamental();

    template<typename T>
    static constexpr epiBool IsString();

    template<typename T>
    static constexpr epiBool IsMultiDimensional();

    template<typename T>
    static constexpr epiBool IsMultiDimensionalInplace();

#if 0
    static epiByte* GetElementByIndex(const epiByte* container, const MetaProperty& meta, epiS32 index);
    static epiByte* GetElementByHash(const epiByte* container, const MetaProperty& meta, epiHash_t hash);
#endif
};

class MetaClassData
{
public:
    void AddProperty(epiMetaPropertyID propertyID, MetaProperty&& metaProperty);

    const epiSize_t GetPropertiesCount() const;
    const MetaProperty* GetPropertyAt(epiS32 index) const;
    const MetaProperty* GetPropertyBy(epiMetaPropertyID pid) const;

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
    std::map<epiMetaPropertyID, epiS32> m_ToIndexTable;
};

class MetaClass final
{
public:
    MetaClass(MetaClassData&& classData, epiMetaTypeID typeID, epiMetaTypeID superTypeID, epiSize_t sizeOf, const epiChar* name);

    epiBool IsValid() const;

    const MetaProperty* GetPropertyBy_FromBase(epiMetaPropertyID pid) const;
    const MetaProperty* GetPropertyBy_FromDerived(epiMetaPropertyID pid) const;
    const MetaProperty* GetPropertyBy_FromCurrent(epiMetaPropertyID pid) const;
    const MetaProperty* GetPropertyBy(epiMetaPropertyID pid) const;

    const MetaProperty* GetPropertyAt_FromBase(epiU32 pidx) const;
    const MetaProperty* GetPropertyAt_FromDerived(epiU32 pidx) const;
    const MetaProperty* GetPropertyAt_FromCurrent(epiU32 pidx) const;
    const MetaProperty* GetPropertyAt(epiU32 pidx) const;

    const MetaClassData& GetClassData() const;
    epiMetaTypeID GetTypeID() const;
    epiMetaTypeID GetSuperTypeID() const;
    const epiChar* GetName() const;
    epiSize_t GetSizeOf() const;

protected:
    MetaClassData m_ClassData;
    epiMetaTypeID m_TypeID{epiMetaTypeID_None};
    epiMetaTypeID m_SuperTypeID{epiMetaTypeID_None};
    epiSize_t m_SizeOf{0};
    epiString m_Name;
};

extern std::map<epiMetaTypeID, MetaClass> g_ClassRegistry;

const MetaClass* ClassRegistry_Type_Lookup(epiMetaTypeID typeID);
const MetaClass* ClassRegistry_Name_Lookup(const epiChar* typeName, epiSize_t len);

template<typename T>
MetaClass& Register()
{
    auto& [it, inserted] = g_ClassRegistry.try_emplace(T::TypeID, std::move(T::EmitMetaClass()));
    epiAssert(inserted);
    return it->second;
}

template<typename T>
const MetaClass& ClassRegistry_GetMetaClass()
{
    static MetaClass t = Register<T>();
    return t;
}

template<typename T>
constexpr epiMetaTypeID MetaType::TypeOf()
{
    if constexpr (std::is_same_v<epiChar, T>) return epiMetaTypeID_epiChar;
    else if constexpr (std::is_same_v<epiWChar, T>) return epiMetaTypeID_epiWChar;
    else if constexpr (std::is_same_v<epiBool, T>) return epiMetaTypeID_epiBool;
    else if constexpr (std::is_same_v<epiByte, T>) return epiMetaTypeID_epiByte;
    else if constexpr (std::is_same_v<epiFloat, T>) return epiMetaTypeID_epiFloat;
    else if constexpr (std::is_same_v<epiDouble, T>) return epiMetaTypeID_epiDouble;
    else if constexpr (std::is_same_v<epiSize_t, T>) return epiMetaTypeID_epiSize_t;
    else if constexpr (std::is_same_v<epiString, T>) return epiMetaTypeID_epiString;
    else if constexpr (std::is_same_v<epiWString, T>) return epiMetaTypeID_epiWString;
    else if constexpr (std::is_same_v<epiU8, T>) return epiMetaTypeID_epiU8;
    else if constexpr (std::is_same_v<epiU16, T>) return epiMetaTypeID_epiU16;
    else if constexpr (std::is_same_v<epiU32, T>) return epiMetaTypeID_epiU32;
    else if constexpr (std::is_same_v<epiU64, T>) return epiMetaTypeID_epiU64;
    else if constexpr (std::is_same_v<epiS8, T>) return epiMetaTypeID_epiS8;
    else if constexpr (std::is_same_v<epiS16, T>) return epiMetaTypeID_epiS16;
    else if constexpr (std::is_same_v<epiS32, T>) return epiMetaTypeID_epiS32;
    else if constexpr (std::is_same_v<epiS64, T>) return epiMetaTypeID_epiS64;
    else if constexpr (std::is_same_v<epiVec2f, T>) return epiMetaTypeID_epiVec2f;
    else if constexpr (std::is_same_v<epiVec2d, T>) return epiMetaTypeID_epiVec2d;
    else if constexpr (std::is_same_v<epiVec2s, T>) return epiMetaTypeID_epiVec2s;
    else if constexpr (std::is_same_v<epiVec2u, T>) return epiMetaTypeID_epiVec2u;
    else if constexpr (std::is_same_v<epiVec3f, T>) return epiMetaTypeID_epiVec3f;
    else if constexpr (std::is_same_v<epiVec3d, T>) return epiMetaTypeID_epiVec3d;
    else if constexpr (std::is_same_v<epiVec3s, T>) return epiMetaTypeID_epiVec3s;
    else if constexpr (std::is_same_v<epiVec3u, T>) return epiMetaTypeID_epiVec3u;
    else if constexpr (std::is_same_v<epiVec4f, T>) return epiMetaTypeID_epiVec4f;
    else if constexpr (std::is_same_v<epiVec4d, T>) return epiMetaTypeID_epiVec4d;
    else if constexpr (std::is_same_v<epiVec4s, T>) return epiMetaTypeID_epiVec4s;
    else if constexpr (std::is_same_v<epiVec4u, T>) return epiMetaTypeID_epiVec4u;
    else if constexpr (std::is_same_v<epiMat2x2f, T>) return epiMetaTypeID_epiMat2x2f;
    else if constexpr (std::is_same_v<epiMat3x3f, T>) return epiMetaTypeID_epiMat3x3f;
    else if constexpr (std::is_same_v<epiMat4x4f, T>) return epiMetaTypeID_epiMat4x4f;
    else static_assert(false, "Unhandled case");
}

template<typename T>
constexpr epiBool MetaType::IsFundamental()
{
    if constexpr (std::is_same_v<epiChar, T>) return true;
    else if constexpr (std::is_same_v<epiWChar, T>) return true;
    else if constexpr (std::is_same_v<epiBool, T>) return true;
    else if constexpr (std::is_same_v<epiByte, T>) return true;
    else if constexpr (std::is_same_v<epiFloat, T>) return true;
    else if constexpr (std::is_same_v<epiDouble, T>) return true;
    else if constexpr (std::is_same_v<epiSize_t, T>) return true;
    else if constexpr (std::is_same_v<epiU8, T>) return true;
    else if constexpr (std::is_same_v<epiU16, T>) return true;
    else if constexpr (std::is_same_v<epiU32, T>) return true;
    else if constexpr (std::is_same_v<epiU64, T>) return true;
    else if constexpr (std::is_same_v<epiS8, T>) return true;
    else if constexpr (std::is_same_v<epiS16, T>) return true;
    else if constexpr (std::is_same_v<epiS32, T>) return true;
    else if constexpr (std::is_same_v<epiS64, T>) return true;
    else return false;
}

template<typename T>
constexpr epiBool MetaType::IsString()
{
    return std::is_same_v<epiString, T> || std::is_same_v<epiWString, T>;
}

template<typename T>
constexpr epiBool MetaType::IsMultiDimensional()
{
    return std::is_base_of_v<epiBaseArray, T> || IsMultiDimensionalInplace<T>();
}

template<typename T>
constexpr epiBool MetaType::IsMultiDimensionalInplace()
{
    if constexpr (std::is_same_v<epiVec2f, T>) return true;
    else if constexpr (std::is_same_v<epiVec2d, T>) return true;
    else if constexpr (std::is_same_v<epiVec2s, T>) return true;
    else if constexpr (std::is_same_v<epiVec2u, T>) return true;
    else if constexpr (std::is_same_v<epiVec3f, T>) return true;
    else if constexpr (std::is_same_v<epiVec3d, T>) return true;
    else if constexpr (std::is_same_v<epiVec3s, T>) return true;
    else if constexpr (std::is_same_v<epiVec3u, T>) return true;
    else if constexpr (std::is_same_v<epiVec4f, T>) return true;
    else if constexpr (std::is_same_v<epiVec4d, T>) return true;
    else if constexpr (std::is_same_v<epiVec4s, T>) return true;
    else if constexpr (std::is_same_v<epiVec4u, T>) return true;
    else if constexpr (std::is_same_v<epiMat2x2f, T>) return true;
    else if constexpr (std::is_same_v<epiMat3x3f, T>) return true;
    else if constexpr (std::is_same_v<epiMat4x4f, T>) return true;
    else return false;
}

}
