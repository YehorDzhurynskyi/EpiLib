#include "EpiLib/pch.h"
#include "QtObjectDelegate.h"

#ifdef epiUSE_QT

#include "QtObjectModel.h"
#include "EpiLib/ObjectModel/Object.h"
#include "EpiLib/Containers/Array.h"
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
    const MetaTypeID typeID = item->m_Meta->GetTypeID();
    assert(MetaType::IsFundamental(typeID));

    QWidget* widget = nullptr;
    if (typeID == MetaTypeID::Float)
    {
        QDoubleSpinBox* editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        widget = editor;
    }
    else if (typeID == MetaTypeID::String)
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
    // TODO: replace with model->data(index, Qt::EditRole);

    QtObjectModelItem* item = static_cast<QtObjectModelItem*>(index.internalPointer());
    const MetaTypeID typeID = item->m_Meta->GetTypeID();
    assert(MetaType::IsFundamental(typeID));

    if (typeID == MetaTypeID::Float)
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(*((epiFloat*)item->m_ValueAddr));
    }
    else if (typeID == MetaTypeID::String)
    {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setText(QString((*((epiString*)item->m_ValueAddr)).c_str()));
    }
    else
    {
        assert(!"Unrecognized type");
    }
}

void QtObjectDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    // TODO: replace with model->setData(index, value, Qt::EditRole);

    QtObjectModelItem* item = static_cast<QtObjectModelItem*>(index.internalPointer());
    const MetaTypeID typeID = item->m_Meta->GetTypeID();
    assert(MetaType::IsFundamental(typeID));

    if (typeID == MetaTypeID::Float)
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        epiFloat* value = (epiFloat*)item->m_ValueAddr;
        *value = spinBox->value();
    }
    else if (typeID == MetaTypeID::String)
    {
        QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
        epiString* value = (epiString*)item->m_ValueAddr;
        *value = lineEdit->text().toStdString();
    }
    else
    {
        assert(!"Unrecognized type");
    }
}

void QtObjectDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    editor->setGeometry(option.rect);
}

}

#endif // epiUSE_QT
