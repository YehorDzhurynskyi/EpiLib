#include "EpiCore/ObjectModel/epiIPropertyChangedHandler.h"

EPI_NAMESPACE_BEGIN()

void epiIPropertyChangedHandler::Register(epiIPropertyChangedHandler& self, epiMetaPropertyID propertyID, PropertyChangedCallback callback)
{
    epiAssert(m_PropertyChangedListeners[&self].find(propertyID) == m_PropertyChangedListeners[&self].end());

    m_PropertyChangedListeners[&self][propertyID] = callback;
}

void epiIPropertyChangedHandler::Unregister(epiIPropertyChangedHandler& self, epiMetaPropertyID propertyID)
{
    epiAssert(m_PropertyChangedListeners[&self].find(propertyID) != m_PropertyChangedListeners[&self].end());

    m_PropertyChangedListeners[&self].erase(propertyID);
}

void epiIPropertyChangedHandler::PropertyChangedTrigger(epiMetaPropertyID propertyID)
{
    for (auto& [listener, callbacks] : m_PropertyChangedListeners)
    {
        if (auto callbackIt = callbacks.find(propertyID); callbackIt != callbacks.end())
        {
            auto callback = callbackIt->second;
            (listener->*callback)();
        }
    }
}

EPI_NAMESPACE_END()
