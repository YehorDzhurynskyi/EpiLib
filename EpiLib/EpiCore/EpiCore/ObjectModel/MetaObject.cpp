#include "EpiCore/pch.h"
#include "MetaObject.h"

#include "Object.h"

#include "EpiCore/Containers/Array.h"
#include "EpiCore/Containers/HashMap.h"

namespace epi
{

epiBool MetaProperty::IsValid() const
{
    return m_TypeID != MetaTypeID::None;
}

epiBool MetaProperty::HasNested() const
{
    return m_NestedTypeID != MetaTypeID::None;
}

MetaTypeID MetaProperty::GetTypeID() const
{
    assert(IsValid());
    return m_TypeID;
}

MetaTypeID MetaProperty::GetNestedTypeID() const
{
    assert(IsValid());
    return m_NestedTypeID;
}

epiByte* MetaProperty::GetValue(const Object& object) const
{
    assert(IsValid());
    return (epiByte*)&object + m_Offset;
}

epiBool MetaType::IsFundamental(MetaTypeID typeID)
{
    return typeID >= MetaTypeID::epiChar && typeID <= MetaTypeID::epiS64;
}

epiBool MetaType::IsHandle(MetaTypeID typeID)
{
    return typeID == MetaTypeID::Handle;
}

epiBool MetaType::IsMultiDimensional(MetaTypeID typeID)
{
    return typeID == MetaTypeID::epiArray ||
        typeID == MetaTypeID::HashMap ||
        IsMultiDimensionalInplace(typeID);
}

epiBool MetaType::IsMultiDimensionalInplace(MetaTypeID typeID)
{
    return
        typeID == MetaTypeID::Vec2 ||
        typeID == MetaTypeID::Vec3 ||
        typeID == MetaTypeID::Vec4;
}

epiBool MetaType::IsCompound(MetaTypeID typeID)
{
    return
        typeID != MetaTypeID::None &&
        !IsFundamental(typeID) &&
        !IsMultiDimensional(typeID) &&
        !IsHandle(typeID);
}

epiByte* MetaType::GetElementByIndex(const epiByte* container, const MetaProperty& meta, epiS32 index)
{
    if (!IsMultiDimensional(meta.GetTypeID()) || !meta.HasNested()) goto invalid_input;

    const MetaClass* elemMeta = ClassRegistry_Type_Lookup(meta.GetNestedTypeID());
    if (elemMeta == nullptr) goto invalid_input;

    const epiByte* element = nullptr;
    if (IsMultiDimensionalInplace(meta.GetTypeID()))
    {
        switch (meta.GetTypeID())
        {
        case MetaTypeID::Vec2: if (index < 0 || index >= 2) goto invalid_input; break;
        case MetaTypeID::Vec3: if (index < 0 || index >= 3) goto invalid_input; break;
        case MetaTypeID::Vec4: if (index < 0 || index >= 4) goto invalid_input; break;
        default: assert(!"Unrecognized type"); break;
        }
        element = container + index * elemMeta->GetSizeOf();
    }
    else if (meta.GetTypeID() == MetaTypeID::epiArray)
    {
        epiBaseArray* array = (epiBaseArray*)container;
        if (index < 0 || index >= array->GetSize()) goto invalid_input;

        element = array->GetData() + index * elemMeta->GetSizeOf();
    }
    else
    {
        assert(!"Unrecognized Array type");
        goto invalid_input;
    }

    return const_cast<epiByte*>(element);

invalid_input:
    assert(!"Invalid Input");
    return nullptr;
}

epiByte* MetaType::GetElementByHash(const epiByte* container, const MetaProperty& meta, epiHash_t hash)
{
    if (meta.GetTypeID() != MetaTypeID::HashMap || !meta.HasNested()) goto invalid_input;

    const MetaClass* elemMeta = ClassRegistry_Type_Lookup(meta.GetNestedTypeID());
    if (elemMeta == nullptr) goto invalid_input;

    return ((BaseHashMap*)container)->Get(hash);

invalid_input:
    assert(!"Invalid Input");
    return nullptr;
}

void MetaClassData::AddProperty(MetaPropertyID propertyID, MetaProperty&& metaProperty)
{
    const epiS32 index = m_Properties.size();
    m_Properties.push_back(std::move(metaProperty));

    assert(m_ToIndexTable.find(propertyID) == m_ToIndexTable.end());
    m_ToIndexTable[propertyID] = index;
}

const epiSize_t MetaClassData::GetPropertiesCount() const
{
    return m_Properties.size();
}

const MetaProperty* MetaClassData::GetPropertyAt(epiS32 index) const
{
    if (index < 0 || index >= m_Properties.size())
    {
        return nullptr;
    }

    return &m_Properties[index];
}

const MetaProperty* MetaClassData::GetPropertyBy(MetaPropertyID pid) const
{
    const auto it = m_ToIndexTable.find(pid);
    if (it == m_ToIndexTable.end())
    {
        return nullptr;
    }

    return GetPropertyAt(it->second);
}

MetaClass::MetaClass(MetaClassData&& classData, MetaTypeID typeID, MetaTypeID superTypeID, epiSize_t sizeOf, const epiChar* name)
    : m_ClassData(std::move(classData))
    , m_TypeID(typeID)
    , m_SuperTypeID(superTypeID)
    , m_SizeOf(sizeOf)
    , m_Name(name)
{}

epiBool MetaClass::IsValid() const
{
    return !MetaType::IsCompound(m_TypeID);
}

const MetaProperty* MetaClass::GetProperty_FromBase(MetaPropertyID pid) const
{
    assert(IsValid());

    const MetaProperty* property = nullptr;
    const MetaClass* superMetaClass = this;
    do
    {
        superMetaClass = ClassRegistry_Type_Lookup(superMetaClass->m_SuperTypeID);
        assert(superMetaClass != nullptr);

        if (superMetaClass->m_TypeID == MetaTypeID::None)
        {
            return nullptr;
        }

        property = superMetaClass->GetProperty_FromCurrent(pid);
        if (property != nullptr)
        {
            break;
        }
    } while (true);

    return property;
}

const MetaProperty* MetaClass::GetProperty_FromDerived(MetaPropertyID pid) const
{
    // TODO: FIXME
    // if both derived classes have same property name (and its ID)
    // than it could give wrong offset of variable
#if 0
    for (const auto& [type, meta] : g_ClassRegistry)
    {
        const MetaClass* childMeta = &meta;
        while (MetaType::IsCompound(childMeta->GetTypeID()))
        {
            if (childMeta->GetTypeID() == m_TypeID && type != m_TypeID)
            {
                if (const MetaProperty* property = meta.GetProperty_FromCurrent(pid))
                {
                    return property;
                }
                break;
            }
            childMeta = ClassRegistry_Type_Lookup(childMeta->m_SuperTypeID);
            assert(childMeta);
        }
    }
#endif

    return nullptr;
}

const MetaProperty* MetaClass::GetProperty_FromCurrent(MetaPropertyID pid) const
{
    assert(IsValid());

    return m_ClassData.GetPropertyBy(pid);
}

const MetaProperty* MetaClass::GetProperty(MetaPropertyID pid) const
{
    if (const MetaProperty* property = GetProperty_FromCurrent(pid))
    {
        return property;
    }

    if (const MetaProperty* property = GetProperty_FromBase(pid))
    {
        return property;
    }

    if (const MetaProperty* property = GetProperty_FromDerived(pid))
    {
        return property;
    }

    return nullptr;
}

const MetaClassData& MetaClass::GetClassData() const
{
    assert(IsValid());

    return m_ClassData;
}

MetaTypeID MetaClass::GetTypeID() const
{
    assert(IsValid());

    return m_TypeID;
}

MetaTypeID MetaClass::GetSuperTypeID() const
{
    assert(IsValid());

    return m_SuperTypeID;
}

const char* MetaClass::GetName() const
{
    assert(IsValid());

    return m_Name.c_str();
}

epiSize_t MetaClass::GetSizeOf() const
{
    assert(IsValid());

    return m_SizeOf;
}

}
