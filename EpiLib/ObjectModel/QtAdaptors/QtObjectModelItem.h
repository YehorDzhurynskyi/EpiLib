#pragma once

#ifdef epiUSE_QT

#include "EpiLib/types.h"
#include <QVariant>

namespace epi
{

enum class MetaTypeID : epiU32;
class BaseArray;
class Object;
class MetaClassData;
class MetaProperty;
class QtObjectModelItem
{
public:
    QtObjectModelItem(epiS32 row, QtObjectModelItem* parent = nullptr);

    void FillMultiDimensional(BaseArray& array, const MetaProperty& itemMeta);
    void FillCompound(Object& object);
    void FillChildren(Object& object, const MetaClassData& meta);

    epiBool IsEditable() const;
    QVariant GetData(epiS32 role) const;
    void SetData(const QVariant& value);
    QVariant GetCaption(epiS32 role) const;

    MetaTypeID GetTypeID() const;

    epiS32 GetRow() const;
    QtObjectModelItem* GetParent();
    QtObjectModelItem* GetChildAt(epiS32 i);
    epiS32 GetChildCount() const;
    epiString GetName() const;

    epiBool IsTracked() const;
    void SetTracked(epiBool tracked);

    void SetValueAddr(void* valueAddr);
    void* GetValueAddr();

protected:
    void* m_ValueAddr;
    const MetaProperty* m_Meta;
    QtObjectModelItem* m_Parent;
    epiS32 m_Row;
    epiBool m_IsTracked;
    std::vector<std::unique_ptr<QtObjectModelItem>> m_Children;
};

}

#endif // epiUSE_QT
