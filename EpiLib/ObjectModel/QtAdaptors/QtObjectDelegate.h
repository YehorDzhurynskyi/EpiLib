#pragma once

#ifdef epiUSE_QT

#include "EpiLib/types.h"
#include <QStyledItemDelegate>

namespace epi
{

class QtObjectDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    QtObjectDelegate(QObject* parent = nullptr);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

}

#endif // epiUSE_QT
