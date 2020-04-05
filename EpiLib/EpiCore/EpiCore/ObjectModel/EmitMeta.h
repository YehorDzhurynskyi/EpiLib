#pragma once

#include "EpiCore/pch.h"

namespace epi
{

class Object;
enum class MetaTypeID : epiU32;
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
                                      MetaTypeID::_Type, \
                                      MetaTypeID::_NestedType); \
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

}
