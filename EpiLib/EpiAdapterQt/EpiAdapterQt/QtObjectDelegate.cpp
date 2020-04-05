#include "EpiAdapterQt/pch.h"
#include "QtObjectDelegate.h"

#include "QtObjectModel.h"
#include "EpiCore/ObjectModel/Object.h"
#include <QSpinBox>
#include <QLineEdit>

namespace epi
{

QtObjectDelegate::QtObjectDelegate(QObject* parent /* = nullptr*/)
    : QStyledItemDelegate(parent)
{}

QWidget* QtObjectDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QtObjectModelItem* item = static_cast<QtObjectModelItem*>(index.internalPointer());
    const MetaTypeID typeID = item->GetTypeID();
    assert(MetaType::IsFundamental(typeID));

    QWidget* widget = nullptr;
    if (typeID == MetaTypeID::epiFloat)
    {
        QDoubleSpinBox* editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setRange(-FLT_MAX, FLT_MAX);
        editor->setDecimals(FLT_DIG);
        widget = editor;
    }
    else if (typeID == MetaTypeID::epiString)
    {
        QLineEdit* editor = new QLineEdit(parent);
        editor->setFrame(false);
        widget = editor;
    }
    else
    {
        assert(!"Unrecognized type");
    }

    return widget;
}

void QtObjectDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QtObjectModelItem* item = static_cast<QtObjectModelItem*>(index.internalPointer());
    const MetaTypeID typeID = item->GetTypeID();
    assert(item->IsEditable());

    const QVariant value = index.model()->data(index, Qt::EditRole);
    if (typeID == MetaTypeID::epiFloat)
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value.toFloat());
    }
    else if (typeID == MetaTypeID::epiString)
    {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setText(value.toString());
    }
    else
    {
        assert(!"Unrecognized type");
    }
}

void QtObjectDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QtObjectModelItem* item = static_cast<QtObjectModelItem*>(index.internalPointer());
    const MetaTypeID typeID = item->GetTypeID();
    assert(item->IsEditable());

    QVariant value;
    if (typeID == MetaTypeID::epiFloat)
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        value = spinBox->value();
    }
    else if (typeID == MetaTypeID::epiString)
    {
        QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
        value = lineEdit->text();
    }
    else
    {
        assert(!"Unrecognized type");
    }

    model->setData(index, value, Qt::EditRole);
}

void QtObjectDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    editor->setGeometry(option.rect);
}

}
