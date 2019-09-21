#include "EpiLib/pch.h"
#include "MetaObject.h"

#include "Object.h"

#include "EpiLib/Containers/Array.h"
#include "EpiLib/Containers/HashMap.h"

namespace epi
{

MetaProperty::MetaProperty(MetaTypeID propertyTypeID,
                           epiSize_t offset,
                           MetaProperty* nestedMetaProperty)
    : m_PropertyTypeID(propertyTypeID)
    , m_Offset(offset)
    , m_NestedMetaProperty(nestedMetaProperty)
{
    assert(IsValid());
}

MetaProperty::MetaProperty(MetaProperty&& rhs)
{
    m_PropertyTypeID = std::move(rhs.m_PropertyTypeID);
    m_Offset = std::move(rhs.m_Offset);
    m_NestedMetaProperty = std::move(rhs.m_NestedMetaProperty);
    rhs.m_NestedMetaProperty = nullptr;
}

MetaProperty& MetaProperty::operator=(MetaProperty&& rhs)
{
    m_PropertyTypeID = std::move(rhs.m_PropertyTypeID);
    m_Offset = std::move(rhs.m_Offset);
    m_NestedMetaProperty = std::move(rhs.m_NestedMetaProperty);
    rhs.m_NestedMetaProperty = nullptr;
    return *this;
}

MetaProperty::~MetaProperty()
{
    delete m_NestedMetaProperty;
}

epiBool MetaProperty::IsValid() const
{
    return m_PropertyTypeID != MetaTypeID::None;
}

epiBool MetaProperty::HasNested() const
{
    return m_NestedMetaProperty != nullptr;
}

MetaTypeID MetaProperty::GetTypeID() const
{
    assert(IsValid());
    return m_PropertyTypeID;
}

epiByte* MetaProperty::GetValue(const Object& object) const
{
    assert(IsValid());
    return (epiByte*)&object + m_Offset;
}

MetaProperty* MetaProperty::GetNestedMetaProperty()
{
    assert(HasNested());
    return m_NestedMetaProperty;
}

const MetaProperty* MetaProperty::GetNestedMetaProperty() const
{
    assert(HasNested());
    return m_NestedMetaProperty;
}

epiBool MetaType::IsFundamental(MetaTypeID typeID)
{
    return typeID >= MetaTypeID::Char && typeID <= MetaTypeID::S64;
}

epiBool MetaType::IsHandle(MetaTypeID typeID)
{
    return typeID == MetaTypeID::Handle;
}

epiBool MetaType::IsMultiDimensional(MetaTypeID typeID)
{
    return typeID == MetaTypeID::Array ||
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

    const MetaClass* elemMeta = ClassRegistry_Lookup(meta.GetNestedMetaProperty()->GetTypeID());
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
    else if (meta.GetTypeID() == MetaTypeID::Array)
    {
        BaseArray* array = (BaseArray*)container;
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

    const MetaClass* elemMeta = ClassRegistry_Lookup(meta.GetNestedMetaProperty()->GetTypeID());
    if (elemMeta == nullptr) goto invalid_input;

    return ((BaseHashMap*)container)->Get(hash);

invalid_input:
    assert(!"Invalid Input");
    return nullptr;
}

void MetaClassData::AddProperty(MetaPropertyID propertyID, MetaProperty&& metaProperty)
{
    assert(Properties.find(propertyID) == Properties.end());
    Properties.try_emplace(propertyID, std::move(metaProperty));
}

MetaClass::MetaClass(MetaClassData* classData, MetaTypeID typeID, MetaTypeID superTypeID, epiSize_t sizeOf)
    : m_ClassData(classData)
    , m_TypeID(typeID)
    , m_SuperTypeID(superTypeID)
    , m_SizeOf(sizeOf)
{}

epiBool MetaClass::IsValid() const
{
    return !MetaType::IsCompound(m_TypeID) || m_ClassData != nullptr;
}

const MetaProperty* MetaClass::GetProperty_FromBase(MetaPropertyID pid) const
{
    assert(IsValid());

    const MetaProperty* property = nullptr;
    const MetaClass* superMetaClass = this;
    do
    {
        superMetaClass = ClassRegistry_Lookup(superMetaClass->m_SuperTypeID);
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
            childMeta = ClassRegistry_Lookup(childMeta->m_SuperTypeID);
            assert(childMeta);
        }
    }

    return nullptr;
}

const MetaProperty* MetaClass::GetProperty_FromCurrent(MetaPropertyID pid) const
{
    assert(IsValid());

    auto it = m_ClassData->Properties.find(pid);
    return it == m_ClassData->Properties.end() ? nullptr : &it->second;
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

MetaTypeID MetaClass::GetTypeID() const
{
    assert(IsValid());

    return m_TypeID;
}

const char* MetaClass::GetClassName() const
{
    assert(IsValid());

    return ClassNameRegistry_Lookup(m_TypeID);
}

epiSize_t MetaClass::GetSizeOf() const
{
    assert(IsValid());

    return m_SizeOf;
}

}
