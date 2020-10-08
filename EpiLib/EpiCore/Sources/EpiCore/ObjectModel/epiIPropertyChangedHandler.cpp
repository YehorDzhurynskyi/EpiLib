#include "EpiCore/ObjectModel/epiIPropertyChangedHandler.h"

EPI_NAMESPACE_BEGIN()

void epiIPropertyChangedHandler::PropertyChangedRegister(epiMetaPropertyID propertyID, PropertyChangedCallback callback, epiIPropertyChangedHandler& target)
{
    epiAssert(m_PropertyChangedListeners[&target].find(propertyID) == m_PropertyChangedListeners[&target].end());

    m_PropertyChangedListeners[&target][propertyID] = callback;
}

void epiIPropertyChangedHandler::PropertyChangedUnregister(epiMetaPropertyID propertyID, epiIPropertyChangedHandler& target)
{
    epiAssert(m_PropertyChangedListeners[&target].find(propertyID) != m_PropertyChangedListeners[&target].end());

    m_PropertyChangedListeners[&target].erase(propertyID);
}

void epiIPropertyChangedHandler::PropertyChangedRegister(epiMetaPropertyID propertyID, PropertyChangedCallback callback)
{
    PropertyChangedRegister(propertyID, callback, *this);
}

void epiIPropertyChangedHandler::PropertyChangedUnregister(epiMetaPropertyID propertyID)
{
    PropertyChangedUnregister(propertyID, *this);
}

void epiIPropertyChangedHandler::PropertyChangedTrigger(epiMetaPropertyID propertyID)
{
    for (auto& [listener, callbacks] : m_PropertyChangedListeners)
    {
        if (auto callbackIt = callbacks.find(propertyID); callbackIt != callbacks.end())
        {
            const auto callback = callbackIt->second;
            callback();
        }
    }
}

EPI_NAMESPACE_END()
