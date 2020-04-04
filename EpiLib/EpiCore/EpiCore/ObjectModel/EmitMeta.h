#pragma once

namespace epi
{

class Object;
class MetaProperty final
{
    friend MetaProperty epiMetaProperty_Impl(const epiChar* name, epiSize_t offset, epiHash_t typeID, epiHash_t nestedTypeID);

private:
    MetaProperty() = default;

public:
    MetaProperty(const MetaProperty&) = delete;
    MetaProperty& operator=(const MetaProperty&) = delete;
    MetaProperty(MetaProperty&&);
    MetaProperty& operator=(MetaProperty&&);
    ~MetaProperty();

    epiBool IsValid() const;
    epiBool HasNested() const;

    epiHash_t GetTypeID() const;

    epiByte* GetValue(const Object& object) const;

    MetaProperty* GetNestedMetaProperty();
    const MetaProperty* GetNestedMetaProperty() const;

protected:
    epiHash_t m_TypeID;
    epiHash_t m_NestedTypeID;
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
        auto & m = epiMetaProperty_Impl(#_Name, \
                                        offsetof(_Owner, m_##_Name), \
                                        epiHashCompileTime(#_Type), \
                                        epiHashCompileTime(#_NestedType)); \
        data.AddProperty(epiHashCompileTime(#_Name), std::move(m)); \
    } \

inline MetaProperty epiMetaProperty_Impl(const epiChar* name, epiSize_t offset, epiHash_t typeID, epiHash_t nestedTypeID)
{
    MetaProperty prty;

    prty.m_Name = name;
    prty.m_Offset = offset;
    prty.m_TypeID = typeID;
    prty.m_NestedTypeID = nestedTypeID;

    return prty;
}

}
