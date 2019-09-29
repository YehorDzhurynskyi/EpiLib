#pragma once

#ifdef epiUSE_QT

#include "EpiLib/types.h"
#include <QAbstractItemModel>

namespace epi
{

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

    epiS32 GetRow() const;
    QtObjectModelItem* GetParent();
    QtObjectModelItem* GetChildAt(epiS32 i);
    epiS32 GetChildCount() const;
    QVariant GetData(epiS32 role) const;

public:
    void* m_ValueAddr;
    const MetaProperty* m_Meta;
    QtObjectModelItem* m_Parent;
    epiS32 m_Row;
    std::vector<std::unique_ptr<QtObjectModelItem>> m_Children;
};

class QtObjectModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    QtObjectModel(Object& object, QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, epiS32 role) const override;
    epiBool setData(const QModelIndex& index, const QVariant& value, epiS32 role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(epiS32 section, Qt::Orientation orientation, epiS32 role = Qt::DisplayRole) const override;
    epiBool setHeaderData(epiS32 section, Qt::Orientation orientation, const QVariant& value, epiS32 role = Qt::EditRole) override;
    QModelIndex index(epiS32 row, epiS32 column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    epiS32 rowCount(const QModelIndex& parent = QModelIndex()) const override;
    epiS32 columnCount(const QModelIndex& parent = QModelIndex()) const override;

protected:
    QtObjectModelItem* ItemOf(const QModelIndex& parent) const;

protected:
    std::unique_ptr<QtObjectModelItem> m_Root;
};

}

#endif // epiUSE_QT
