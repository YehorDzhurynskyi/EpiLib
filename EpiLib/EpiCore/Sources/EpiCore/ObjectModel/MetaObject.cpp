#include "MetaObject.h"

#include "Object.h"

#include "EpiCore/Containers/Array.h"
#include "EpiCore/Containers/HashMap.h"

namespace epi
{

epiBool MetaProperty::IsValid() const
{
    return m_TypeID != epiMetaTypeID_None;
}

epiBool MetaProperty::HasNested() const
{
    return m_NestedTypeID != epiMetaTypeID_None;
}

epiMetaTypeID MetaProperty::GetTypeID() const
{
    assert(IsValid());
    return m_TypeID;
}

epiMetaTypeID MetaProperty::GetNestedTypeID() const
{
    assert(IsValid());
    return m_NestedTypeID;
}

MetaProperty::Flags MetaProperty::GetFlags() const
{
    return m_Flags;
}

#if 0
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
        case epiMetaTypeID::Vec2: if (index < 0 || index >= 2) goto invalid_input; break;
        case epiMetaTypeID::Vec3: if (index < 0 || index >= 3) goto invalid_input; break;
        case epiMetaTypeID::Vec4: if (index < 0 || index >= 4) goto invalid_input; break;
        default: assert(!"Unrecognized type"); break;
        }
        element = container + index * elemMeta->GetSizeOf();
    }
    else if (meta.GetTypeID() == epiMetaTypeID::epiArray)
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
    if (meta.GetTypeID() != epiMetaTypeID::HashMap || !meta.HasNested()) goto invalid_input;

    const MetaClass* elemMeta = ClassRegistry_Type_Lookup(meta.GetNestedTypeID());
    if (elemMeta == nullptr) goto invalid_input;

    return ((BaseHashMap*)container)->Get(hash);

invalid_input:
    assert(!"Invalid Input");
    return nullptr;
}
#endif

void MetaClassData::AddProperty(epiMetaPropertyID propertyID, MetaProperty&& metaProperty)
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

const MetaProperty* MetaClassData::GetPropertyBy(epiMetaPropertyID pid) const
{
    const auto it = m_ToIndexTable.find(pid);
    if (it == m_ToIndexTable.end())
    {
        return nullptr;
    }

    return GetPropertyAt(it->second);
}

MetaClass::MetaClass(MetaClassData&& classData, epiMetaTypeID typeID, epiMetaTypeID superTypeID, epiSize_t sizeOf, const epiChar* name)
    : m_ClassData(std::move(classData))
    , m_TypeID(typeID)
    , m_SuperTypeID(superTypeID)
    , m_SizeOf(sizeOf)
    , m_Name(name)
{}

epiBool MetaClass::IsValid() const
{
    return m_TypeID != epiMetaTypeID_None && m_SizeOf > 0;
}

const MetaProperty* MetaClass::GetPropertyBy_FromBase(epiMetaPropertyID pid) const
{
    epiAssert(IsValid());

    const MetaProperty* property = nullptr;
    const MetaClass* superMetaClass = this;
    do
    {
        superMetaClass = ClassRegistry_Type_Lookup(superMetaClass->m_SuperTypeID);
        epiAssert(superMetaClass != nullptr);

        if (superMetaClass->m_TypeID == epiMetaTypeID_None)
        {
            return nullptr;
        }

        property = superMetaClass->GetPropertyBy_FromCurrent(pid);
        if (property != nullptr)
        {
            break;
        }
    } while (true);

    return property;
}

const MetaProperty* MetaClass::GetPropertyBy_FromDerived(epiMetaPropertyID pid) const
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

const MetaProperty* MetaClass::GetPropertyBy_FromCurrent(epiMetaPropertyID pid) const
{
    assert(IsValid());

    return m_ClassData.GetPropertyBy(pid);
}

const MetaProperty* MetaClass::GetPropertyBy(epiMetaPropertyID pid) const
{
    if (const MetaProperty* property = GetPropertyBy_FromCurrent(pid))
    {
        return property;
    }

    if (const MetaProperty* property = GetPropertyBy_FromBase(pid))
    {
        return property;
    }

    if (const MetaProperty* property = GetPropertyBy_FromDerived(pid))
    {
        return property;
    }

    return nullptr;
}

const MetaProperty* MetaClass::GetPropertyAt_FromBase(epiU32 pidx) const
{
    epiAssert(IsValid());

    const MetaProperty* property = nullptr;
    const MetaClass* superMetaClass = this;
    do
    {
        superMetaClass = ClassRegistry_Type_Lookup(superMetaClass->m_SuperTypeID);
        epiAssert(superMetaClass != nullptr);

        if (superMetaClass->m_TypeID == epiMetaTypeID_None)
        {
            return nullptr;
        }

        property = superMetaClass->GetPropertyAt_FromCurrent(pidx);
        if (property != nullptr)
        {
            break;
        }
    } while (true);

    return property;
}

const MetaProperty* MetaClass::GetPropertyAt_FromDerived(epiU32 pidx) const
{
    return nullptr;
}

const MetaProperty* MetaClass::GetPropertyAt_FromCurrent(epiU32 pidx) const
{
    assert(IsValid());

    return m_ClassData.GetPropertyAt(pidx);
}

const MetaProperty* MetaClass::GetPropertyAt(epiU32 pidx) const
{
    if (const MetaProperty* property = GetPropertyAt_FromCurrent(pidx))
    {
        return property;
    }

    if (const MetaProperty* property = GetPropertyAt_FromBase(pidx))
    {
        return property;
    }

    if (const MetaProperty* property = GetPropertyAt_FromDerived(pidx))
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

epiMetaTypeID MetaClass::GetTypeID() const
{
    assert(IsValid());

    return m_TypeID;
}

epiMetaTypeID MetaClass::GetSuperTypeID() const
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

using MetaClassEmitter = MetaClass (*)();
std::map<epiMetaTypeID, MetaClass> g_ClassRegistry;

const MetaClass* ClassRegistry_Type_Lookup(epiMetaTypeID typeID)
{
    const MetaClass* meta = nullptr;

    if (const auto classIt = g_ClassRegistry.find(typeID); classIt != g_ClassRegistry.end())
    {
        meta = &classIt->second;
    }
    else
    {
        epiAssert(!"No such class has been registred");
    }

    return meta;
}

const MetaClass* ClassRegistry_Name_Lookup(const epiChar* typeName, epiSize_t len)
{
    for (const auto& [k, v] : g_ClassRegistry)
    {
        const epiChar* name = v.GetName();
        if (strlen(name) == len && strncmp(name, typeName, len) == 0)
        {
            return &v;
        }
    }

    return nullptr;
}

}
