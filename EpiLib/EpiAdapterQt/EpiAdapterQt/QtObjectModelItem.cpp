#include "EpiAdapterQt/pch.h"
#include "QtObjectModelItem.h"

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/Containers/Array.h"
#include <QBrush>
#include <QFont>

namespace epi
{

static QColor NotEditableBGColor = QColor::fromRgb(220, 220, 220);
static QColor EditableBGColor1 = QColor::fromRgb(255, 255, 255);
static QColor EditableBGColor2 = QColor::fromRgb(240, 240, 240);
static QColor TrackedColor = QColor::fromRgb(255, 213, 25);

QtObjectModelItem::QtObjectModelItem(epiS32 row, QtObjectModelItem* parent /* = nullptr*/)
    : m_ValueAddr(nullptr)
    , m_Meta(nullptr)
    , m_Parent(parent)
    , m_Row(row)
    , m_IsTracked(false)
{}

QVariant QtObjectModelItem::GetData(epiS32 role) const
{
    if (role == Qt::EditRole || role == Qt::DisplayRole)
    {
        if (MetaType::IsFundamental(m_Meta->GetTypeID()))
        {
            switch (m_Meta->GetTypeID())
            {
            case MetaTypeID_epiChar: return *((epiChar*)m_ValueAddr);
            case MetaTypeID_epiBool: return *((epiBool*)m_ValueAddr);
            case MetaTypeID_epiByte: return *((epiByte*)m_ValueAddr);
            case MetaTypeID_epiFloat: return *((epiFloat*)m_ValueAddr);
            case MetaTypeID_epiDouble: return *((epiDouble*)m_ValueAddr);
            case MetaTypeID_epiSize_t: return *((epiSize_t*)m_ValueAddr);
            case MetaTypeID_epiString: return QString(((epiString*)m_ValueAddr)->c_str());
            case MetaTypeID_epiU8: return *((epiU8*)m_ValueAddr);
            case MetaTypeID_epiU16: return *((epiU16*)m_ValueAddr);
            case MetaTypeID_epiU32: return *((epiU32*)m_ValueAddr);
            case MetaTypeID_epiU64: return *((epiU64*)m_ValueAddr);
            case MetaTypeID_epiS8: return *((epiS8*)m_ValueAddr);
            case MetaTypeID_epiS16: return *((epiS16*)m_ValueAddr);
            case MetaTypeID_epiS32: return *((epiS32*)m_ValueAddr);
            case MetaTypeID_epiS64: return *((epiS64*)m_ValueAddr);
            default: assert(!"Unrecognized type");
            }
        }
        else if (MetaType::IsCompound(m_Meta->GetTypeID()))
        {
            const Object* object = reinterpret_cast<const Object*>(m_ValueAddr);
            return QString(object->ToString().c_str());
        }
        else if (MetaType::IsMultiDimensional(m_Meta->GetTypeID()))
        {
            if (role == Qt::DisplayRole)
            {
                const epiBaseArray* array = reinterpret_cast<const epiBaseArray*>(m_ValueAddr);
                return  QStringLiteral("Array (Size=%1)").arg(array->GetSize());
            }
        }
    }

    if (role == Qt::BackgroundRole)
    {
        if (!IsEditable())
        {
            return QBrush(NotEditableBGColor);
        }
        else if (m_IsTracked)
        {
            return QBrush(TrackedColor);
        }
        else
        {
            return m_Row % 2 == 0 ? QBrush(EditableBGColor1) : QBrush(EditableBGColor2);
        }
    }

    if (role == Qt::FontRole)
    {
        if (!IsEditable())
        {
            QFont font;
            font.setItalic(true);

            return font;
        }
    }

    return QVariant();
}

void QtObjectModelItem::SetData(const QVariant& value)
{
    assert(IsEditable());

    const MetaTypeID typeID = m_Meta->GetTypeID();
    switch (typeID)
    {
    case MetaTypeID_epiFloat: *((epiFloat*)m_ValueAddr) = value.toFloat(); break;
    case MetaTypeID_epiString: *((epiString*)m_ValueAddr) = value.toString().toStdString(); break;
    default: assert(!"Unrecognized type");
    }
}

QVariant QtObjectModelItem::GetCaption(epiS32 role) const
{
    if (role == Qt::DisplayRole)
    {
        QString result;
        if (m_Parent->m_Meta && MetaType::IsMultiDimensional(m_Parent->m_Meta->GetTypeID()))
        {
            result = QStringLiteral("[%1]").arg(m_Row);
        }
        else if (MetaType::IsCompound(m_Meta->GetTypeID()))
        {
            const Object* object = reinterpret_cast<const Object*>(m_ValueAddr);
            result = QString(object->ToString().c_str());
        }
        else
        {
            result = QString(m_Meta->GetName());
        }

        return result;
    }

    if (role == Qt::BackgroundRole)
    {
        if (!IsEditable())
        {
            return QBrush(NotEditableBGColor);
        }
        else if (m_IsTracked)
        {
            return QBrush(TrackedColor);
        }
        else
        {
            return m_Row % 2 == 0 ? QBrush(EditableBGColor1) : QBrush(EditableBGColor2);
        }
    }

    return QVariant();
}

epiBool QtObjectModelItem::IsEditable() const
{
    return MetaType::IsFundamental(m_Meta->GetTypeID());
}

void QtObjectModelItem::FillMultiDimensional(epiBaseArray& array, MetaTypeID nestedTypeID)
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
        nestedItem->m_Meta = nullptr;

        if (MetaType::IsCompound(nestedTypeID))
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
        const MetaClassData& metaClassData = meta->GetClassData();

        FillChildren(object, metaClassData);

        assert(MetaType::IsCompound(meta->GetSuperTypeID()) || meta->GetSuperTypeID() == MetaTypeID_epiNone);
        meta = ClassRegistry_Type_Lookup(meta->GetSuperTypeID());
        assert(meta);
    } while (meta->GetTypeID() != MetaTypeID_epiNone);
}

void QtObjectModelItem::FillChildren(Object& object, const MetaClassData& meta)
{
    m_Children.reserve(meta.GetPropertiesCount());

    epiS32 index = m_Children.size();
    for (const MetaProperty& property : meta)
    {
        std::unique_ptr<QtObjectModelItem> item = std::make_unique<QtObjectModelItem>(index++, this);

        // TODO: repair
        item->m_ValueAddr = nullptr; // property.GetValue(object);
        item->m_Meta = &property;

        if (MetaType::IsCompound(property.GetTypeID()))
        {
            item->FillCompound(*reinterpret_cast<Object*>(item->m_ValueAddr));
        }
        else if (MetaType::IsMultiDimensional(property.GetTypeID()))
        {
            item->FillMultiDimensional(*reinterpret_cast<epiBaseArray*>(item->m_ValueAddr), property.GetNestedTypeID());
        }

        m_Children.push_back(std::move(item));
    }
}

MetaTypeID QtObjectModelItem::GetTypeID() const
{
    return m_Meta->GetTypeID();
}

epiS32 QtObjectModelItem::GetRow() const
{
    return m_Row;
}

void* QtObjectModelItem::GetValueAddr()
{
    return m_ValueAddr;
}

void QtObjectModelItem::SetValueAddr(void* valueAddr)
{
    m_ValueAddr = valueAddr;
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

epiBool QtObjectModelItem::IsTracked() const
{
    return m_IsTracked;
}

void QtObjectModelItem::SetTracked(epiBool tracked)
{
    m_IsTracked = tracked;
}

epiString QtObjectModelItem::GetName() const
{
    if (MetaType::IsCompound(m_Meta->GetTypeID()))
    {
        Object* object = reinterpret_cast<Object*>(m_ValueAddr);
        return object->ToString();
    }
    else
    {
        assert(m_Parent);
        Object* object = reinterpret_cast<Object*>(m_Parent->GetValueAddr());
        return epiString(m_Meta->GetName()) + " (" + object->ToString() + ")";
    }
}

}
