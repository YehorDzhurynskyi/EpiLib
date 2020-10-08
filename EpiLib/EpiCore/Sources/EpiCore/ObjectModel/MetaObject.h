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

static constexpr epiMetaTypeID epiMetaTypeID_None = 0;
static constexpr epiMetaTypeID epiMetaTypeID_Ptr = epiHashCompileTime(Ptr);

static constexpr epiMetaTypeID epiMetaTypeID_epiChar = epiHashCompileTime(epiChar);
static constexpr epiMetaTypeID epiMetaTypeID_epiWChar = epiHashCompileTime(epiWChar);
static constexpr epiMetaTypeID epiMetaTypeID_epiBool = epiHashCompileTime(epiBool);
static constexpr epiMetaTypeID epiMetaTypeID_epiByte = epiHashCompileTime(epiByte);
static constexpr epiMetaTypeID epiMetaTypeID_epiFloat = epiHashCompileTime(epiFloat);
static constexpr epiMetaTypeID epiMetaTypeID_epiDouble = epiHashCompileTime(epiDouble);
static constexpr epiMetaTypeID epiMetaTypeID_epiSize_t = epiHashCompileTime(epiSize_t);
static constexpr epiMetaTypeID epiMetaTypeID_epiString = epiHashCompileTime(epiString);
static constexpr epiMetaTypeID epiMetaTypeID_epiWString = epiHashCompileTime(epiWString);
static constexpr epiMetaTypeID epiMetaTypeID_epiU8 = epiHashCompileTime(epiU8);
static constexpr epiMetaTypeID epiMetaTypeID_epiU16 = epiHashCompileTime(epiU16);
static constexpr epiMetaTypeID epiMetaTypeID_epiU32 = epiHashCompileTime(epiU32);
static constexpr epiMetaTypeID epiMetaTypeID_epiU64 = epiHashCompileTime(epiU64);
static constexpr epiMetaTypeID epiMetaTypeID_epiS8 = epiHashCompileTime(epiS8);
static constexpr epiMetaTypeID epiMetaTypeID_epiS16 = epiHashCompileTime(epiS16);
static constexpr epiMetaTypeID epiMetaTypeID_epiS32 = epiHashCompileTime(epiS32);
static constexpr epiMetaTypeID epiMetaTypeID_epiS64 = epiHashCompileTime(epiS64);

static constexpr epiMetaTypeID epiMetaTypeID_epiArray = epiHashCompileTime(epiArray);
static constexpr epiMetaTypeID epiMetaTypeID_epiPtrArray = epiHashCompileTime(epiPtrArray);

static constexpr epiMetaTypeID epiMetaTypeID_epiSize2 = epiHashCompileTime(epiSize2);
static constexpr epiMetaTypeID epiMetaTypeID_epiSize2f = epiHashCompileTime(epiSize2f);
static constexpr epiMetaTypeID epiMetaTypeID_epiSize2d = epiHashCompileTime(epiSize2d);
static constexpr epiMetaTypeID epiMetaTypeID_epiSize2s = epiHashCompileTime(epiSize2s);
static constexpr epiMetaTypeID epiMetaTypeID_epiSize2u = epiHashCompileTime(epiSize2u);

static constexpr epiMetaTypeID epiMetaTypeID_epiVec2f = epiHashCompileTime(epiVec2f);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec2d = epiHashCompileTime(epiVec2d);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec2s = epiHashCompileTime(epiVec2s);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec2s8 = epiHashCompileTime(epiVec2s8);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec2s16 = epiHashCompileTime(epiVec2s16);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec2s32 = epiHashCompileTime(epiVec2s32);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec2s64 = epiHashCompileTime(epiVec2s64);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec2u = epiHashCompileTime(epiVec2u);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec2u8 = epiHashCompileTime(epiVec2u8);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec2u16 = epiHashCompileTime(epiVec2u16);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec2u32 = epiHashCompileTime(epiVec2u32);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec2u64 = epiHashCompileTime(epiVec2u64);

static constexpr epiMetaTypeID epiMetaTypeID_epiVec3f = epiHashCompileTime(epiVec3f);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec3d = epiHashCompileTime(epiVec3d);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec3s = epiHashCompileTime(epiVec3s);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec3s8 = epiHashCompileTime(epiVec3s8);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec3s16 = epiHashCompileTime(epiVec3s16);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec3s32 = epiHashCompileTime(epiVec3s32);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec3s64 = epiHashCompileTime(epiVec3s64);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec3u = epiHashCompileTime(epiVec3u);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec3u8 = epiHashCompileTime(epiVec3u8);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec3u16 = epiHashCompileTime(epiVec3u16);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec3u32 = epiHashCompileTime(epiVec3u32);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec3u64 = epiHashCompileTime(epiVec3u64);

static constexpr epiMetaTypeID epiMetaTypeID_epiVec4f = epiHashCompileTime(epiVec4f);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec4d = epiHashCompileTime(epiVec4d);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec4s = epiHashCompileTime(epiVec4s);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec4s8 = epiHashCompileTime(epiVec4s8);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec4s16 = epiHashCompileTime(epiVec4s16);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec4s32 = epiHashCompileTime(epiVec4s32);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec4s64 = epiHashCompileTime(epiVec4s64);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec4u = epiHashCompileTime(epiVec4u);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec4u8 = epiHashCompileTime(epiVec4u8);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec4u16 = epiHashCompileTime(epiVec4u16);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec4u32 = epiHashCompileTime(epiVec4u32);
static constexpr epiMetaTypeID epiMetaTypeID_epiVec4u64 = epiHashCompileTime(epiVec4u64);

static constexpr epiMetaTypeID epiMetaTypeID_epiMat2x2f = epiHashCompileTime(epiMat2x2f);
static constexpr epiMetaTypeID epiMetaTypeID_epiMat3x3f = epiHashCompileTime(epiMat3x3f);
static constexpr epiMetaTypeID epiMetaTypeID_epiMat4x4f = epiHashCompileTime(epiMat4x4f);

static constexpr epiMetaTypeID epiMetaTypeID_epiComplexf = epiHashCompileTime(epiComplexf);
static constexpr epiMetaTypeID epiMetaTypeID_epiComplexd = epiHashCompileTime(epiComplexd);

static constexpr epiMetaTypeID epiMetaTypeID_epiRect2f = epiHashCompileTime(epiRect2f);
static constexpr epiMetaTypeID epiMetaTypeID_epiRect2d = epiHashCompileTime(epiRect2d);
static constexpr epiMetaTypeID epiMetaTypeID_epiRect2s = epiHashCompileTime(epiRect2s);
static constexpr epiMetaTypeID epiMetaTypeID_epiRect2u = epiHashCompileTime(epiRect2u);

class MetaType
{
public:
    static constexpr epiBool IsFundamental(epiMetaTypeID typeID);
    static constexpr epiBool IsString(epiMetaTypeID typeID);
    static constexpr epiBool IsMultiDimensional(epiMetaTypeID typeID);
    static constexpr epiBool IsMultiDimensionalInplace(epiMetaTypeID typeID);
    static constexpr epiBool IsCompound(epiMetaTypeID typeID);
    static constexpr epiBool IsPointer(epiMetaTypeID typeID);
    static constexpr epiBool IsNumeric(epiMetaTypeID typeID);
    static constexpr epiBool IsFloating(epiMetaTypeID typeID);

    template<typename T> static constexpr epiBool IsFundamental();
    template<typename T> static constexpr epiBool IsString();
    template<typename T> static constexpr epiBool IsMultiDimensional();
    template<typename T> static constexpr epiBool IsMultiDimensionalInplace();
    template<typename T> static constexpr epiBool IsCompound();
    template<typename T> static constexpr epiBool IsPointer();
    template<typename T> static constexpr epiBool IsNumeric();
    template<typename T> static constexpr epiBool IsFloating();

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

    auto beginPID_PIDX() -> typename std::map<epiMetaPropertyID, epiS32>::iterator { return m_ToIndexTable.begin(); }
    auto endPID_PIDX() -> typename std::map<epiMetaPropertyID, epiS32>::iterator { return m_ToIndexTable.end(); }
    auto beginPID_PIDX() const -> typename std::map<epiMetaPropertyID, epiS32>::const_iterator { return m_ToIndexTable.cbegin(); }
    auto endPID_PIDX() const -> typename std::map<epiMetaPropertyID, epiS32>::const_iterator { return m_ToIndexTable.cend(); }

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

constexpr epiBool MetaType::IsFundamental(epiMetaTypeID typeID)
{
    switch (typeID)
    {
    case epiMetaTypeID_epiChar:
    case epiMetaTypeID_epiWChar:
    case epiMetaTypeID_epiBool:
    case epiMetaTypeID_epiByte:
    case epiMetaTypeID_epiFloat:
    case epiMetaTypeID_epiDouble:
    case epiMetaTypeID_epiSize_t:
    case epiMetaTypeID_epiU8:
    case epiMetaTypeID_epiU16:
    case epiMetaTypeID_epiU32:
    case epiMetaTypeID_epiU64:
    case epiMetaTypeID_epiS8:
    case epiMetaTypeID_epiS16:
    case epiMetaTypeID_epiS32:
    case epiMetaTypeID_epiS64:
        return true;
    default: return false;
    }
}

constexpr epiBool MetaType::IsString(epiMetaTypeID typeID)
{
    return typeID == epiMetaTypeID_epiString || typeID == epiMetaTypeID_epiWString;
}

constexpr epiBool MetaType::IsMultiDimensional(epiMetaTypeID typeID)
{
    return
        typeID == epiMetaTypeID_epiArray ||
        typeID == epiMetaTypeID_epiPtrArray ||
        IsMultiDimensionalInplace(typeID);
}

constexpr epiBool MetaType::IsMultiDimensionalInplace(epiMetaTypeID typeID)
{
    switch (typeID)
    {
    case epiMetaTypeID_epiSize2:
    case epiMetaTypeID_epiSize2f:
    case epiMetaTypeID_epiSize2d:
    case epiMetaTypeID_epiSize2s:
    case epiMetaTypeID_epiSize2u:
    case epiMetaTypeID_epiVec2f:
    case epiMetaTypeID_epiVec2d:
    case epiMetaTypeID_epiVec2s:
    case epiMetaTypeID_epiVec2s8:
    case epiMetaTypeID_epiVec2s16:
    case epiMetaTypeID_epiVec2s32:
    case epiMetaTypeID_epiVec2s64:
    case epiMetaTypeID_epiVec2u:
    case epiMetaTypeID_epiVec2u8:
    case epiMetaTypeID_epiVec2u16:
    case epiMetaTypeID_epiVec2u32:
    case epiMetaTypeID_epiVec2u64:
    case epiMetaTypeID_epiVec3f:
    case epiMetaTypeID_epiVec3d:
    case epiMetaTypeID_epiVec3s:
    case epiMetaTypeID_epiVec3s8:
    case epiMetaTypeID_epiVec3s16:
    case epiMetaTypeID_epiVec3s32:
    case epiMetaTypeID_epiVec3s64:
    case epiMetaTypeID_epiVec3u:
    case epiMetaTypeID_epiVec3u8:
    case epiMetaTypeID_epiVec3u16:
    case epiMetaTypeID_epiVec3u32:
    case epiMetaTypeID_epiVec3u64:
    case epiMetaTypeID_epiVec4f:
    case epiMetaTypeID_epiVec4d:
    case epiMetaTypeID_epiVec4s:
    case epiMetaTypeID_epiVec4s8:
    case epiMetaTypeID_epiVec4s16:
    case epiMetaTypeID_epiVec4s32:
    case epiMetaTypeID_epiVec4s64:
    case epiMetaTypeID_epiVec4u:
    case epiMetaTypeID_epiVec4u8:
    case epiMetaTypeID_epiVec4u16:
    case epiMetaTypeID_epiVec4u32:
    case epiMetaTypeID_epiVec4u64:
    case epiMetaTypeID_epiMat2x2f:
    case epiMetaTypeID_epiMat3x3f:
    case epiMetaTypeID_epiMat4x4f:
    case epiMetaTypeID_epiComplexf:
    case epiMetaTypeID_epiComplexd:
    case epiMetaTypeID_epiRect2f:
    case epiMetaTypeID_epiRect2d:
    case epiMetaTypeID_epiRect2s:
    case epiMetaTypeID_epiRect2u:
    return true;
    default: return false;
    }
}

constexpr epiBool MetaType::IsCompound(epiMetaTypeID typeID)
{
    return
        typeID != epiMetaTypeID_None &&
        !IsPointer(typeID) &&
        !IsString(typeID) &&
        !IsFundamental(typeID) &&
        !IsMultiDimensional(typeID);
}

constexpr epiBool MetaType::IsPointer(epiMetaTypeID typeID)
{
    return epiMetaTypeID_Ptr == typeID;
}

constexpr epiBool MetaType::IsNumeric(epiMetaTypeID typeID)
{
    switch (typeID)
    {
    case epiMetaTypeID_epiByte:
    case epiMetaTypeID_epiFloat:
    case epiMetaTypeID_epiDouble:
    case epiMetaTypeID_epiSize_t:
    case epiMetaTypeID_epiU8:
    case epiMetaTypeID_epiU16:
    case epiMetaTypeID_epiU32:
    case epiMetaTypeID_epiU64:
    case epiMetaTypeID_epiS8:
    case epiMetaTypeID_epiS16:
    case epiMetaTypeID_epiS32:
    case epiMetaTypeID_epiS64:
    return true;
    default: return false;
    }
}

constexpr epiBool MetaType::IsFloating(epiMetaTypeID typeID)
{
    switch (typeID)
    {
    case epiMetaTypeID_epiFloat:
    case epiMetaTypeID_epiDouble:
    case epiMetaTypeID_epiVec2f:
    case epiMetaTypeID_epiVec2d:
    case epiMetaTypeID_epiVec3f:
    case epiMetaTypeID_epiVec3d:
    case epiMetaTypeID_epiVec4f:
    case epiMetaTypeID_epiVec4d:
    case epiMetaTypeID_epiMat2x2f:
    case epiMetaTypeID_epiMat3x3f:
    case epiMetaTypeID_epiMat4x4f:
    case epiMetaTypeID_epiComplexf:
    case epiMetaTypeID_epiComplexd:
    case epiMetaTypeID_epiRect2f:
    case epiMetaTypeID_epiRect2d:
    return true;
    default: return false;
    }
}

template<typename T>
constexpr epiBool MetaType::IsFundamental()
{
    if constexpr (std::is_same_v<epiChar, T>) { static_assert(IsFundamental(epiMetaTypeID_epiChar)); return true; }
    else if constexpr (std::is_same_v<epiWChar, T>) { static_assert(IsFundamental(epiMetaTypeID_epiWChar)); return true; }
    else if constexpr (std::is_same_v<epiBool, T>) { static_assert(IsFundamental(epiMetaTypeID_epiBool)); return true; }
    else if constexpr (std::is_same_v<epiByte, T>) { static_assert(IsFundamental(epiMetaTypeID_epiByte)); return true; }
    else if constexpr (std::is_same_v<epiFloat, T>) { static_assert(IsFundamental(epiMetaTypeID_epiFloat)); return true; }
    else if constexpr (std::is_same_v<epiDouble, T>) { static_assert(IsFundamental(epiMetaTypeID_epiDouble)); return true; }
    else if constexpr (std::is_same_v<epiSize_t, T>) { static_assert(IsFundamental(epiMetaTypeID_epiSize_t)); return true; }
    else if constexpr (std::is_same_v<epiU8, T>) { static_assert(IsFundamental(epiMetaTypeID_epiU8)); return true; }
    else if constexpr (std::is_same_v<epiU16, T>) { static_assert(IsFundamental(epiMetaTypeID_epiU16)); return true; }
    else if constexpr (std::is_same_v<epiU32, T>) { static_assert(IsFundamental(epiMetaTypeID_epiU32)); return true; }
    else if constexpr (std::is_same_v<epiU64, T>) { static_assert(IsFundamental(epiMetaTypeID_epiU64)); return true; }
    else if constexpr (std::is_same_v<epiS8, T>) { static_assert(IsFundamental(epiMetaTypeID_epiS8)); return true; }
    else if constexpr (std::is_same_v<epiS16, T>) { static_assert(IsFundamental(epiMetaTypeID_epiS16)); return true; }
    else if constexpr (std::is_same_v<epiS32, T>) { static_assert(IsFundamental(epiMetaTypeID_epiS32)); return true; }
    else if constexpr (std::is_same_v<epiS64, T>) { static_assert(IsFundamental(epiMetaTypeID_epiS64)); return true; }
    else return false;
}

template<typename T>
constexpr epiBool MetaType::IsString()
{
    static_assert(IsString(epiMetaTypeID_epiString) && IsString(epiMetaTypeID_epiWString));
 
    return std::is_same_v<epiString, T> || std::is_same_v<epiWString, T>;
}

template<typename T>
constexpr epiBool MetaType::IsMultiDimensional()
{
    static_assert(IsMultiDimensional(epiMetaTypeID_epiArray) || IsMultiDimensional(epiMetaTypeID_epiPtrArray));

    return std::is_base_of_v<epiBaseArray, T> || IsMultiDimensionalInplace<T>();
}

template<typename T>
constexpr epiBool MetaType::IsMultiDimensionalInplace()
{
    if constexpr (std::is_same_v<epiSize2, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiSize2)); return true; }
    else if constexpr (std::is_same_v<epiSize2f, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiSize2f)); return true; }
    else if constexpr (std::is_same_v<epiSize2d, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiSize2d)); return true; }
    else if constexpr (std::is_same_v<epiSize2s, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiSize2s)); return true; }
    else if constexpr (std::is_same_v<epiSize2u, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiSize2u)); return true; }
    else if constexpr (std::is_same_v<epiVec2f, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec2f)); return true; }
    else if constexpr (std::is_same_v<epiVec2d, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec2d)); return true; }
    else if constexpr (std::is_same_v<epiVec2s, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec2s)); return true; }
    else if constexpr (std::is_same_v<epiVec2s8, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec2s8)); return true; }
    else if constexpr (std::is_same_v<epiVec2s16, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec2s16)); return true; }
    else if constexpr (std::is_same_v<epiVec2s32, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec2s32)); return true; }
    else if constexpr (std::is_same_v<epiVec2s64, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec2s64)); return true; }
    else if constexpr (std::is_same_v<epiVec2u, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec2u)); return true; }
    else if constexpr (std::is_same_v<epiVec2u8, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec2u8)); return true; }
    else if constexpr (std::is_same_v<epiVec2u16, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec2u16)); return true; }
    else if constexpr (std::is_same_v<epiVec2u32, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec2u32)); return true; }
    else if constexpr (std::is_same_v<epiVec2u64, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec2u64)); return true; }
    else if constexpr (std::is_same_v<epiVec3f, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec3f)); return true; }
    else if constexpr (std::is_same_v<epiVec3d, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec3d)); return true; }
    else if constexpr (std::is_same_v<epiVec3s, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec3s)); return true; }
    else if constexpr (std::is_same_v<epiVec3s8, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec3s8)); return true; }
    else if constexpr (std::is_same_v<epiVec3s16, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec3s16)); return true; }
    else if constexpr (std::is_same_v<epiVec3s32, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec3s32)); return true; }
    else if constexpr (std::is_same_v<epiVec3s64, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec3s64)); return true; }
    else if constexpr (std::is_same_v<epiVec3u, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec3u)); return true; }
    else if constexpr (std::is_same_v<epiVec3u8, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec3u8)); return true; }
    else if constexpr (std::is_same_v<epiVec3u16, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec3u16)); return true; }
    else if constexpr (std::is_same_v<epiVec3u32, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec3u32)); return true; }
    else if constexpr (std::is_same_v<epiVec3u64, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec3u64)); return true; }
    else if constexpr (std::is_same_v<epiVec4f, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec4f)); return true; }
    else if constexpr (std::is_same_v<epiVec4d, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec4d)); return true; }
    else if constexpr (std::is_same_v<epiVec4s, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec4s)); return true; }
    else if constexpr (std::is_same_v<epiVec4s8, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec4s8)); return true; }
    else if constexpr (std::is_same_v<epiVec4s16, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec4s16)); return true; }
    else if constexpr (std::is_same_v<epiVec4s32, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec4s32)); return true; }
    else if constexpr (std::is_same_v<epiVec4s64, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec4s64)); return true; }
    else if constexpr (std::is_same_v<epiVec4u, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec4u)); return true; }
    else if constexpr (std::is_same_v<epiVec4u8, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec4u8)); return true; }
    else if constexpr (std::is_same_v<epiVec4u16, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec4u16)); return true; }
    else if constexpr (std::is_same_v<epiVec4u32, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec4u32)); return true; }
    else if constexpr (std::is_same_v<epiVec4u64, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiVec4u64)); return true; }
    else if constexpr (std::is_same_v<epiMat2x2f, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiMat2x2f)); return true; }
    else if constexpr (std::is_same_v<epiMat3x3f, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiMat3x3f)); return true; }
    else if constexpr (std::is_same_v<epiMat4x4f, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiMat4x4f)); return true; }
    else if constexpr (std::is_same_v<epiComplexf, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiComplexf)); return true; }
    else if constexpr (std::is_same_v<epiComplexd, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiComplexd)); return true; }
    else if constexpr (std::is_same_v<epiRect2f, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiRect2f)); return true; }
    else if constexpr (std::is_same_v<epiRect2d, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiRect2d)); return true; }
    else if constexpr (std::is_same_v<epiRect2s, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiRect2s)); return true; }
    else if constexpr (std::is_same_v<epiRect2u, T>) { static_assert(IsMultiDimensionalInplace(epiMetaTypeID_epiRect2u)); return true; }
    else return false;
}

template<typename T>
constexpr epiBool MetaType::IsCompound()
{
    if constexpr (std::is_base_of_v<Object, T>)
    {
        static_assert(IsCompound(T::TypeID));
        return true;
    }

    return false;
}

template<typename T>
constexpr epiBool MetaType::IsPointer()
{
    static_assert(IsPointer(epiMetaTypeID_Ptr));

    return std::is_pointer_v<T>;
}

template<typename T>
constexpr epiBool MetaType::IsNumeric()
{
    if constexpr (std::is_same_v<epiByte, T>) { static_assert(IsNumeric(epiMetaTypeID_epiByte)) return true; }
    else if constexpr (std::is_same_v<epiFloat, T>) { static_assert(IsNumeric(epiMetaTypeID_epiFloat)) return true; }
    else if constexpr (std::is_same_v<epiDouble, T>) { static_assert(IsNumeric(epiMetaTypeID_epiDouble)) return true; }
    else if constexpr (std::is_same_v<epiSize_t, T>) { static_assert(IsNumeric(epiMetaTypeID_epiSize_t)) return true; }
    else if constexpr (std::is_same_v<epiU8, T>) { static_assert(IsNumeric(epiMetaTypeID_epiU8)) return true; }
    else if constexpr (std::is_same_v<epiU16, T>) { static_assert(IsNumeric(epiMetaTypeID_epiU16)) return true; }
    else if constexpr (std::is_same_v<epiU32, T>) { static_assert(IsNumeric(epiMetaTypeID_epiU32)) return true; }
    else if constexpr (std::is_same_v<epiU64, T>) { static_assert(IsNumeric(epiMetaTypeID_epiU64)) return true; }
    else if constexpr (std::is_same_v<epiS8, T>) { static_assert(IsNumeric(epiMetaTypeID_epiS8)) return true; }
    else if constexpr (std::is_same_v<epiS16, T>) { static_assert(IsNumeric(epiMetaTypeID_epiS16)) return true; }
    else if constexpr (std::is_same_v<epiS32, T>) { static_assert(IsNumeric(epiMetaTypeID_epiS32)) return true; }
    else if constexpr (std::is_same_v<epiS64, T>) { static_assert(IsNumeric(epiMetaTypeID_epiS64)) return true; }
    else return false;
}

template<typename T>
constexpr epiBool MetaType::IsFloating()
{
    if constexpr (std::is_same_v<epiFloat, T>) { static_assert(IsFloating(epiMetaTypeID_epiFloat)) return true; }
    else if constexpr (std::is_same_v<epiDouble, T>) { static_assert(IsFloating(epiMetaTypeID_epiDouble)) return true; }
    else if constexpr (std::is_same_v<epiVec2f, T>) { static_assert(IsFloating(epiMetaTypeID_epiVec2f)) return true; }
    else if constexpr (std::is_same_v<epiVec2d, T>) { static_assert(IsFloating(epiMetaTypeID_epiVec2d)) return true; }
    else if constexpr (std::is_same_v<epiVec3f, T>) { static_assert(IsFloating(epiMetaTypeID_epiVec3f)) return true; }
    else if constexpr (std::is_same_v<epiVec3d, T>) { static_assert(IsFloating(epiMetaTypeID_epiVec3d)) return true; }
    else if constexpr (std::is_same_v<epiVec4f, T>) { static_assert(IsFloating(epiMetaTypeID_epiVec4f)) return true; }
    else if constexpr (std::is_same_v<epiVec4d, T>) { static_assert(IsFloating(epiMetaTypeID_epiVec4d)) return true; }
    else if constexpr (std::is_same_v<epiMat2x2f, T>) { static_assert(IsFloating(epiMetaTypeID_epiMat2x2f)) return true; }
    else if constexpr (std::is_same_v<epiMat3x3f, T>) { static_assert(IsFloating(epiMetaTypeID_epiMat3x3f)) return true; }
    else if constexpr (std::is_same_v<epiMat4x4f, T>) { static_assert(IsFloating(epiMetaTypeID_epiMat4x4f)) return true; }
    else if constexpr (std::is_same_v<epiComplexf, T>) { static_assert(IsFloating(epiMetaTypeID_epiComplexf)) return true; }
    else if constexpr (std::is_same_v<epiComplexd, T>) { static_assert(IsFloating(epiMetaTypeID_epiComplexd)) return true; }
    else if constexpr (std::is_same_v<epiRect2f, T>) { static_assert(IsFloating(epiMetaTypeID_epiRect2f)) return true; }
    else if constexpr (std::is_same_v<epiRect2d, T>) { static_assert(IsFloating(epiMetaTypeID_epiRect2d)) return true; }
    else return false;
}

}
