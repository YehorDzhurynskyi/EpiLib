#pragma once

#include "EpiCore/ObjectModel/MetaObject.h"

EPI_NAMESPACE_BEGIN()

#define epiPropertyChangedCheckAndTrigger(Property, Value) \
    static_assert(std::is_same_v<std::decay_t<decltype(m_##Property)>, std::decay_t<decltype(Value)>>); \
    PropertyChangedTrigger<decltype(m_##Property)>(PID_##Property, m_##Property, Value);

class epiIPropertyChangedHandler
{
public:
    using PropertyChangedCallback = std::function<void(void)>;

public:
    void PropertyChangedRegister(epiMetaPropertyID propertyID, PropertyChangedCallback callback, epiIPropertyChangedHandler& target);
    void PropertyChangedUnregister(epiMetaPropertyID propertyID, epiIPropertyChangedHandler& target);
    void PropertyChangedRegister(epiMetaPropertyID propertyID, PropertyChangedCallback callback);
    void PropertyChangedUnregister(epiMetaPropertyID propertyID);

    template<typename PropertyType>
    void PropertyChangedTrigger(epiMetaPropertyID propertyID, PropertyType& property, const PropertyType& value, epiBool forceAssignment = false);

    void PropertyChangedTriggerCallbacks(epiMetaPropertyID propertyID);

private:
    std::map<epiIPropertyChangedHandler*, std::map<epiMetaPropertyID, PropertyChangedCallback>> m_PropertyChangedListeners;
};

template<typename PropertyType>
void epiIPropertyChangedHandler::PropertyChangedTrigger(epiMetaPropertyID propertyID, PropertyType& property, const PropertyType& value, epiBool forceAssignment)
{
    epiProfileFunction;

    if (forceAssignment || !epiEqual(property, value))
    {
        property = value;
        PropertyChangedTriggerCallbacks(propertyID);
    }
}

EPI_NAMESPACE_END()
