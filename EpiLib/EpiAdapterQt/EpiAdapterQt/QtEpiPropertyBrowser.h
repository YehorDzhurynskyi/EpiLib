#pragma once

#if 0

#include "EpiCore/types.h"
#include "Extern/QtPropertyBrowser/src/QtTreePropertyBrowser.h"
#include "Extern/QtPropertyBrowser/src/qtvariantproperty.h"

namespace epi
{

enum class MetaTypeID : epiU32;
class BaseArray;
class Object;
class MetaClassData;
class MetaProperty;
class QtEpiPropertyBrowser : public QtTreePropertyBrowser
{
    Q_OBJECT

public:
    QtEpiPropertyBrowser(Object& object, QWidget* parent = nullptr);

protected:
    void FillMultiDimensional(QtProperty* parent, BaseArray& array, const MetaProperty& itemMeta);
    void FillCompound(QtProperty* parent, Object& object);
    void FillChildren(QtProperty* parent, Object& object, const MetaClassData& meta);

    epiS32 PropertyTypeOf(const MetaProperty& meta);

protected:
    QtVariantPropertyManager m_PropertyManager;
    QtVariantEditorFactory m_PropertyFactory;
};

class QtEpiProperty : QtVariantProperty
{
public:
    void Init(Object& object, const MetaProperty& meta);

    epiBool IsValid() const;

    void Apply();
    void Reset();

protected:
    void* m_ValueAddr;
    const MetaProperty* m_Meta;
};

}

#endif
