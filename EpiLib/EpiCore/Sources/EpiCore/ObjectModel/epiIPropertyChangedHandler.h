#pragma once

#include "EpiCore/ObjectModel/MetaObject.h"

EPI_NAMESPACE_BEGIN()

#define epiPropertyChangedCheckAndTrigger(Property, Value) \
    do \
    { \
        static_assert(std::is_same_v<std::decay_t<decltype(m_##Property)>, std::decay_t<decltype(Value)>>); \
        if (!epiEqual(m_##Property, Value)) \
        { \
            m_##Property = Value; \
            PropertyChangedTrigger(PID_##Property); \
        } \
    } while (0); \

class epiIPropertyChangedHandler
{
public:
    using PropertyChangedCallback = std::function<void(void)>;

public:
    void PropertyChangedRegister(epiMetaPropertyID propertyID, PropertyChangedCallback callback, epiIPropertyChangedHandler& target);
    void PropertyChangedUnregister(epiMetaPropertyID propertyID, epiIPropertyChangedHandler& target);
    void PropertyChangedRegister(epiMetaPropertyID propertyID, PropertyChangedCallback callback);
    void PropertyChangedUnregister(epiMetaPropertyID propertyID);

    void PropertyChangedTrigger(epiMetaPropertyID propertyID);

private:
    std::map<epiIPropertyChangedHandler*, std::map<epiMetaPropertyID, PropertyChangedCallback>> m_PropertyChangedListeners;
};

EPI_NAMESPACE_END()
