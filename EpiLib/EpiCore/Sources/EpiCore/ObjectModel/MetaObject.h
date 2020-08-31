#pragma once

#include "EpiCore/Hash.h"

namespace epi
{

using MetaPropertyID = epiHash_t;
using MetaTypeID = epiHash_t;

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

    MetaTypeID GetTypeID() const;
    MetaTypeID GetNestedTypeID() const;
    Flags GetFlags() const;

protected:
    Flags m_Flags;
    MetaTypeID m_TypeID;
    MetaTypeID m_NestedTypeID;
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
    friend MetaProperty epiMetaProperty(const epiChar*, void*, void*, epiU64, MetaTypeID, MetaTypeID);
};

inline MetaProperty epiMetaProperty(const epiChar* name,
                                    void* ptrRead,
                                    void* ptrWrite,
                                    epiU64 flags,
                                    MetaTypeID typeID,
                                    MetaTypeID nestedTypeID)
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

enum : MetaTypeID
{
    MetaTypeID_None = 0,
    MetaTypeID_Ptr = epiHashCompileTime(Ptr),

    MetaTypeID_epiChar = epiHashCompileTime(epiChar),
    MetaTypeID_epiWChar = epiHashCompileTime(epiWChar),
    MetaTypeID_epiBool = epiHashCompileTime(epiBool),
    MetaTypeID_epiByte = epiHashCompileTime(epiByte),
    MetaTypeID_epiFloat = epiHashCompileTime(epiFloat),
    MetaTypeID_epiDouble = epiHashCompileTime(epiDouble),
    MetaTypeID_epiSize_t = epiHashCompileTime(epiSize_t),
    MetaTypeID_epiString = epiHashCompileTime(epiString),
    MetaTypeID_epiWString = epiHashCompileTime(epiWString),
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

    MetaTypeID_epiVec2f = epiHashCompileTime(epiVec2f),
    MetaTypeID_epiVec2d = epiHashCompileTime(epiVec2d),
    MetaTypeID_epiVec2s = epiHashCompileTime(epiVec2s),
    MetaTypeID_epiVec2u = epiHashCompileTime(epiVec2u),

    MetaTypeID_epiVec3f = epiHashCompileTime(epiVec3f),
    MetaTypeID_epiVec3d = epiHashCompileTime(epiVec3d),
    MetaTypeID_epiVec3s = epiHashCompileTime(epiVec3s),
    MetaTypeID_epiVec3u = epiHashCompileTime(epiVec3u),

    MetaTypeID_epiVec4f = epiHashCompileTime(epiVec4f),
    MetaTypeID_epiVec4d = epiHashCompileTime(epiVec4d),
    MetaTypeID_epiVec4s = epiHashCompileTime(epiVec4s),
    MetaTypeID_epiVec4u = epiHashCompileTime(epiVec4u),

    MetaTypeID_epiMat2x2f = epiHashCompileTime(epiMat2x2f),
    MetaTypeID_epiMat3x3f = epiHashCompileTime(epiMat3x3f),
    MetaTypeID_epiMat4x4f = epiHashCompileTime(epiMat4x4f)
};

class MetaType
{
public:
    static epiBool IsFundamental(MetaTypeID typeID);
    static epiBool IsString(MetaTypeID typeID);
    static epiBool IsMultiDimensional(MetaTypeID typeID);
    static epiBool IsMultiDimensionalInplace(MetaTypeID typeID);
    static epiBool IsCompound(MetaTypeID typeID);

    template<typename T>
    static constexpr MetaTypeID TypeOf();

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

    const MetaProperty* GetPropertyBy_FromBase(MetaPropertyID pid) const;
    const MetaProperty* GetPropertyBy_FromDerived(MetaPropertyID pid) const;
    const MetaProperty* GetPropertyBy_FromCurrent(MetaPropertyID pid) const;
    const MetaProperty* GetPropertyBy(MetaPropertyID pid) const;

    const MetaProperty* GetPropertyAt_FromBase(epiU32 pidx) const;
    const MetaProperty* GetPropertyAt_FromDerived(epiU32 pidx) const;
    const MetaProperty* GetPropertyAt_FromCurrent(epiU32 pidx) const;
    const MetaProperty* GetPropertyAt(epiU32 pidx) const;

    const MetaClassData& GetClassData() const;
    MetaTypeID GetTypeID() const;
    MetaTypeID GetSuperTypeID() const;
    const epiChar* GetName() const;
    epiSize_t GetSizeOf() const;

protected:
    MetaClassData m_ClassData;
    MetaTypeID m_TypeID{MetaTypeID_None};
    MetaTypeID m_SuperTypeID{MetaTypeID_None};
    epiSize_t m_SizeOf{0};
    epiString m_Name;
};

extern std::map<MetaTypeID, MetaClass> g_ClassRegistry;

const MetaClass* ClassRegistry_Type_Lookup(MetaTypeID typeID);
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
constexpr MetaTypeID MetaType::TypeOf()
{
    if constexpr (std::is_same_v<epiChar, T>) return MetaTypeID_epiChar;
    else if constexpr (std::is_same_v<epiWChar, T>) return MetaTypeID_epiWChar;
    else if constexpr (std::is_same_v<epiBool, T>) return MetaTypeID_epiBool;
    else if constexpr (std::is_same_v<epiByte, T>) return MetaTypeID_epiByte;
    else if constexpr (std::is_same_v<epiFloat, T>) return MetaTypeID_epiFloat;
    else if constexpr (std::is_same_v<epiDouble, T>) return MetaTypeID_epiDouble;
    else if constexpr (std::is_same_v<epiSize_t, T>) return MetaTypeID_epiSize_t;
    else if constexpr (std::is_same_v<epiString, T>) return MetaTypeID_epiString;
    else if constexpr (std::is_same_v<epiWString, T>) return MetaTypeID_epiWString;
    else if constexpr (std::is_same_v<epiU8, T>) return MetaTypeID_epiU8;
    else if constexpr (std::is_same_v<epiU16, T>) return MetaTypeID_epiU16;
    else if constexpr (std::is_same_v<epiU32, T>) return MetaTypeID_epiU32;
    else if constexpr (std::is_same_v<epiU64, T>) return MetaTypeID_epiU64;
    else if constexpr (std::is_same_v<epiS8, T>) return MetaTypeID_epiS8;
    else if constexpr (std::is_same_v<epiS16, T>) return MetaTypeID_epiS16;
    else if constexpr (std::is_same_v<epiS32, T>) return MetaTypeID_epiS32;
    else if constexpr (std::is_same_v<epiS64, T>) return MetaTypeID_epiS64;
    else if constexpr (std::is_same_v<epiVec2f, T>) return MetaTypeID_epiVec2f;
    else if constexpr (std::is_same_v<epiVec2d, T>) return MetaTypeID_epiVec2d;
    else if constexpr (std::is_same_v<epiVec2s, T>) return MetaTypeID_epiVec2s;
    else if constexpr (std::is_same_v<epiVec2u, T>) return MetaTypeID_epiVec2u;
    else if constexpr (std::is_same_v<epiVec3f, T>) return MetaTypeID_epiVec3f;
    else if constexpr (std::is_same_v<epiVec3d, T>) return MetaTypeID_epiVec3d;
    else if constexpr (std::is_same_v<epiVec3s, T>) return MetaTypeID_epiVec3s;
    else if constexpr (std::is_same_v<epiVec3u, T>) return MetaTypeID_epiVec3u;
    else if constexpr (std::is_same_v<epiVec4f, T>) return MetaTypeID_epiVec4f;
    else if constexpr (std::is_same_v<epiVec4d, T>) return MetaTypeID_epiVec4d;
    else if constexpr (std::is_same_v<epiVec4s, T>) return MetaTypeID_epiVec4s;
    else if constexpr (std::is_same_v<epiVec4u, T>) return MetaTypeID_epiVec4u;
    else if constexpr (std::is_same_v<epiMat2x2f, T>) return MetaTypeID_epiMat2x2f;
    else if constexpr (std::is_same_v<epiMat3x3f, T>) return MetaTypeID_epiMat3x3f;
    else if constexpr (std::is_same_v<epiMat4x4f, T>) return MetaTypeID_epiMat4x4f;
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
