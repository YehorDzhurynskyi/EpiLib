#include "EpiLib/pch.h"
#include "QtObjectModel.h"

#ifdef epiUSE_QT

#include "EpiLib/ObjectModel/Object.h"
#include "EpiLib/Containers/Array.h"

namespace epi
{

QtObjectModelItem::QtObjectModelItem(epiS32 row, QtObjectModelItem* parent /* = nullptr*/)
    : m_ValueAddr(nullptr)
    , m_Meta(nullptr)
    , m_Parent(parent)
    , m_Row(row)
{}

epiS32 QtObjectModelItem::GetRow() const
{
    return m_Row;
}

QtObjectModelItem* QtObjectModelItem::GetParent()
{
    return m_Parent;
}

QtObjectModelItem* QtObjectModelItem::GetChildAt(epiS32 i)
{
    assert(i >= 0 && i < m_Children.size());
    return m_Children[i].get();
}

epiS32 QtObjectModelItem::GetChildCount() const
{
    return m_Children.size();
}

QVariant QtObjectModelItem::GetData(epiS32 role) const
{
    assert(role == Qt::DisplayRole || role == Qt::EditRole);

    if (role == Qt::DisplayRole)
    {
        if (m_Parent->m_Meta && MetaType::IsMultiDimensional(m_Parent->m_Meta->GetTypeID()))
        {
            return QStringLiteral("[%1]").arg(m_Row);
        }
        else if (MetaType::IsCompound(m_Meta->GetTypeID()))
        {
            const Object* object = reinterpret_cast<const Object*>(m_ValueAddr);
            return QString(object->ToString().c_str());
        }
        else
        {
            return QString(m_Meta->GetName());
        }
    }

    if (role == Qt::EditRole)
    {
        if (MetaType::IsFundamental(m_Meta->GetTypeID()))
        {
            switch (m_Meta->GetTypeID())
            {
            case MetaTypeID::Char: return *((epiChar*)m_ValueAddr);
            case MetaTypeID::Bool: return *((epiBool*)m_ValueAddr);
            case MetaTypeID::Byte: return *((epiByte*)m_ValueAddr);
            case MetaTypeID::Float: return *((epiFloat*)m_ValueAddr);
            case MetaTypeID::Double: return *((epiDouble*)m_ValueAddr);
            case MetaTypeID::Size_t: return *((epiSize_t*)m_ValueAddr);
            case MetaTypeID::String: return QString(((epiString*)m_ValueAddr)->c_str());
            case MetaTypeID::U8: return *((epiU8*)m_ValueAddr);
            case MetaTypeID::U16: return *((epiU16*)m_ValueAddr);
            case MetaTypeID::U32: return *((epiU32*)m_ValueAddr);
            case MetaTypeID::U64: return *((epiU64*)m_ValueAddr);
            case MetaTypeID::S8: return *((epiS8*)m_ValueAddr);
            case MetaTypeID::S16: return *((epiS16*)m_ValueAddr);
            case MetaTypeID::S32: return *((epiS32*)m_ValueAddr);
            case MetaTypeID::S64: return *((epiS64*)m_ValueAddr);
            default: assert(!"Unrecognized type");
            }
        }
        else if (MetaType::IsCompound(m_Meta->GetTypeID()))
        {
            const Object* object = reinterpret_cast<const Object*>(m_ValueAddr);
            return QString(object->ToString().c_str());
        }
    }
}

void QtObjectModelItem::FillMultiDimensional(BaseArray& array, const MetaProperty& itemMeta)
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

void QtObjectModelItem::FillCompound(Object& object)
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

void QtObjectModelItem::FillChildren(Object& object, const MetaClassData& meta)
{
    m_Children.reserve(meta.GetPropertiesCount());

    epiS32 index = m_Children.size();
    for (const MetaProperty& property : meta)
    {
        std::unique_ptr<QtObjectModelItem> item = std::make_unique<QtObjectModelItem>(index, this);

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

QtObjectModel::QtObjectModel(Object& object, QObject* parent /* = nullptr*/)
    : QAbstractItemModel(parent)
{
    const MetaClass& metaClass = object.GetMetaClass();
    assert(MetaType::IsCompound(metaClass.GetTypeID()));
    const MetaClassData* metaClassData = metaClass.GetClassData();
    assert(metaClassData);

    m_Root = std::make_unique<QtObjectModelItem>(0);
    m_Root->FillCompound(object);
}

QVariant QtObjectModel::data(const QModelIndex& index, epiS32 role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole && role != Qt::EditRole)
    {
        return QVariant();
    }

    if (index.column() == 0)
    {
        role = Qt::DisplayRole;
    }
    else if (index.column() == 1)
    {
        role = Qt::EditRole;
    }

    QtObjectModelItem* item = static_cast<QtObjectModelItem*>(index.internalPointer());
    return item->GetData(role);
}

epiBool QtObjectModel::setData(const QModelIndex& index, const QVariant& value, epiS32 role /* = Qt::EditRole*/)
{
    return false;
}

Qt::ItemFlags QtObjectModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    QtObjectModelItem* item = static_cast<QtObjectModelItem*>(index.internalPointer());
    if (index.column() == 1 && MetaType::IsFundamental(item->m_Meta->GetTypeID()))
    {
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }
    else
    {
        return QAbstractItemModel::flags(index);
    }
}

QVariant QtObjectModel::headerData(epiS32 section, Qt::Orientation orientation, epiS32 role /* = Qt::DisplayRole*/) const
{
    if (role == Qt::DisplayRole)
    {
        return QStringLiteral("Header %1").arg(section);
    }

    return QVariant();
}

epiBool QtObjectModel::setHeaderData(epiS32 section, Qt::Orientation orientation, const QVariant& value, epiS32 role /* = Qt::EditRole*/)
{
    return false;
}

QModelIndex QtObjectModel::index(epiS32 row, epiS32 column, const QModelIndex& parent /* = QModelIndex()*/) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    QtObjectModelItem* item = ItemOf(parent);
    QtObjectModelItem* child = item->GetChildAt(row);

    return child ? createIndex(row, column, child) : QModelIndex();
}

QModelIndex QtObjectModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    QtObjectModelItem* item = static_cast<QtObjectModelItem*>(index.internalPointer());
    QtObjectModelItem* parentItem = item->GetParent();
    if (parentItem == m_Root.get())
    {
        return QModelIndex();
    }

    return createIndex(parentItem->GetRow(), 0, parentItem);
}

epiS32 QtObjectModel::rowCount(const QModelIndex& parent /* = QModelIndex()*/) const
{
    if (parent.column() > 0)
    {
        return 0;
    }

    QtObjectModelItem* item = ItemOf(parent);

    return item->GetChildCount();
}

epiS32 QtObjectModel::columnCount(const QModelIndex& parent /* = QModelIndex()*/) const
{
    return 2;
}

QtObjectModelItem* QtObjectModel::ItemOf(const QModelIndex& parent) const
{
    return !parent.isValid() ? m_Root.get() : static_cast<QtObjectModelItem*>(parent.internalPointer());
}

}

#endif // epiUSE_QT
