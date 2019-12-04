#pragma once

#ifdef 0

#include "EpiLib/types.h"
#include "Extern/QtPropertyBrowser/src/qtvariantproperty.h"

namespace epi
{

enum class MetaTypeID : epiU32;
class BaseArray;
class Object;
class MetaClassData;
class MetaProperty;
class QtEpiPropertyManager : QtAbstractPropertyManager
{
    Q_OBJECT

public:
    QtEpiPropertyManager(QObject* parent = nullptr);

    virtual QtVariantProperty *addProperty(int propertyType, const QString &name = QString());

    void setProperties(QSet<QtProperty *> properties);

    MetaTypeID GetPropertyType(const QtProperty *property) const;
    MetaTypeID GetValueType(const QtProperty *property) const;
    QtVariantProperty *variantProperty(const QtProperty *property) const;

    virtual bool isPropertyTypeSupported(int propertyType) const;
    virtual int valueType(int propertyType) const;
    virtual QStringList attributes(int propertyType) const;
    virtual int attributeType(int propertyType, const QString &attribute) const;

    virtual QVariant value(const QtProperty *property) const;
    virtual QVariant attributeValue(const QtProperty *property, const QString &attribute) const;

    static int enumTypeId();
    static int flagTypeId();
    static int groupTypeId();
    static int iconMapTypeId();
public Q_SLOTS:
    virtual void setValue(QtProperty *property, const QVariant &val);
    virtual void setAttribute(QtProperty *property,
                              const QString &attribute, const QVariant &value);
Q_SIGNALS:
    void valueChanged(QtProperty *property, const QVariant &val);
    void attributeChanged(QtProperty *property,
                          const QString &attribute, const QVariant &val);
protected:
    virtual bool hasValue(const QtProperty *property) const;
    QString valueText(const QtProperty *property) const;
    QIcon valueIcon(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
    virtual QtProperty *createProperty();
};

}

#endif
