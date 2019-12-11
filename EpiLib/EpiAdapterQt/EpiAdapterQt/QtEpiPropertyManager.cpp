#include "EpiAdapterQt/pch.h"
#include "QtEpiPropertyManager.h"

#if 0

#include "EpiLib/ObjectModel/Object.h"
#include "EpiLib/Containers/Array.h"

namespace epi
{

QtEpiPropertyBrowser::QtEpiPropertyBrowser(Object& object, QWidget* parent /* = nullptr*/)
    : QtTreePropertyBrowser(parent)
{
    const MetaClass& metaClass = object.GetMetaClass();
    assert(MetaType::IsCompound(metaClass.GetTypeID()));
    const MetaClassData* metaClassData = metaClass.GetClassData();
    assert(metaClassData);

    QtProperty* root = m_PropertyManager.addProperty(
        QtVariantPropertyManager::groupTypeId(),
        QLatin1String("Object"));

    FillCompound(root, object);

    setFactoryForManager(&m_PropertyManager, &m_PropertyFactory);
    addProperty(root);
    setPropertiesWithoutValueMarked(true);
    setRootIsDecorated(false);
}

void QtEpiPropertyBrowser::FillMultiDimensional(QtProperty* parent, BaseArray& array, const MetaProperty& itemMeta)
{
    epiByte* data = array.GetData();
    const epiSize_t arraySz = array.GetSize();
    const epiSize_t itemSz = array.GetSizeOfItem();

    assert(m_Children.empty());
    m_Children.reserve(arraySz);
    for (epiU32 i = 0; i < arraySz; ++i)
    {
        std::unique_ptr<QtObjectModelItem> nestedItem = std::make_unique<QtObjectModelItem>(i, this);
        nestedItem->m_ValueAddr = data + i * itemSz;
        nestedItem->m_Meta = &itemMeta;

        if (MetaType::IsCompound(itemMeta.GetTypeID()))
        {
            nestedItem->FillCompound(*reinterpret_cast<Object*>(nestedItem->m_ValueAddr));
        }

        m_Children.push_back(std::move(nestedItem));
    }
}

void QtEpiPropertyBrowser::FillCompound(QtProperty* parent, Object& object)
{
    const MetaClass& metaClass = object.GetMetaClass();
    assert(MetaType::IsCompound(metaClass.GetTypeID()));

    const MetaClass* meta = &metaClass;
    do
    {
        const MetaClassData* metaClassData = meta->GetClassData();
        assert(metaClassData);

        FillChildren(object, *metaClassData);

        assert(MetaType::IsCompound(meta->GetSuperTypeID()) || meta->GetSuperTypeID() == MetaTypeID::None);
        meta = ClassRegistry_Type_Lookup(meta->GetSuperTypeID());
        assert(meta);
    } while (meta->GetTypeID() != MetaTypeID::None);
}

void QtEpiPropertyBrowser::FillChildren(QtProperty* parent, Object& object, const MetaClassData& meta)
{
    parent->subProperties().reserve(meta.GetPropertiesCount());

    //epiS32 index = parent->subProperties().size();
    for (const MetaProperty& property : meta)
    {
        //std::unique_ptr<QtObjectModelItem> item = std::make_unique<QtObjectModelItem>(index++, this);

        item->m_ValueAddr = property.GetValue(object);
        item->m_Meta = &property;

        if (MetaType::IsCompound(property.GetTypeID()))
        {
            item->FillCompound(*reinterpret_cast<Object*>(item->m_ValueAddr));
        }
        else if (MetaType::IsMultiDimensional(property.GetTypeID()))
        {
            item->FillMultiDimensional(*reinterpret_cast<BaseArray*>(item->m_ValueAddr), *property.GetNestedMetaProperty());
        }

        m_Children.push_back(std::move(item));
    }
}

}

#endif
