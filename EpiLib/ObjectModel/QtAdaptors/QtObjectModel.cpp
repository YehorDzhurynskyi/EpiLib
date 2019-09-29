#include "EpiLib/pch.h"
#include "QtObjectModel.h"

#ifdef epiUSE_QT

#include "EpiLib/ObjectModel/Object.h"

namespace epi
{

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

    QtObjectModelItem* item = static_cast<QtObjectModelItem*>(index.internalPointer());

    QVariant result;
    if (index.column() == 0)
    {
        result = item->GetCaption(role);
    }
    else if (index.column() == 1)
    {
        result = item->GetData(role);
    }
    else
    {
        assert(!"Unexpected column index");
    }

    return result;
}

epiBool QtObjectModel::setData(const QModelIndex& index, const QVariant& value, epiS32 role /* = Qt::EditRole*/)
{
    if (role != Qt::EditRole)
    {
        return false;
    }

    QtObjectModelItem* item = static_cast<QtObjectModelItem*>(index.internalPointer());
    item->SetData(value);

    return true;
}

Qt::ItemFlags QtObjectModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    Qt::ItemFlags flags = QAbstractItemModel::flags(index);

    QtObjectModelItem* item = static_cast<QtObjectModelItem*>(index.internalPointer());
    if (item->IsEditable() && index.column() == 1)
    {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

QVariant QtObjectModel::headerData(epiS32 section, Qt::Orientation orientation, epiS32 role /* = Qt::DisplayRole*/) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        QString result;

        if (section == 0)
        {
            result = QString("Caption");
        }
        else if (section == 1)
        {
            result = QString("Value");
        }

        return result;
    }

    return QVariant();
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
