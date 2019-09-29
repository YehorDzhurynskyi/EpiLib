#pragma once

#ifdef epiUSE_QT

#include "EpiLib/types.h"
#include "QtObjectModelItem.h"
#include <QAbstractItemModel>

namespace epi
{

class QtObjectModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    QtObjectModel(Object& object, QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, epiS32 role) const override;
    epiBool setData(const QModelIndex& index, const QVariant& value, epiS32 role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(epiS32 section, Qt::Orientation orientation, epiS32 role = Qt::DisplayRole) const override;
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
