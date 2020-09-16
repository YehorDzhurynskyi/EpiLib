#include "EpiCore/Event/EventBus.h"

EPI_NAMESPACE_BEGIN()

void EventBus::EventHandler::operator()(Event& event)
{
    Callback(event);
}

EventBus& EventBus::GetEventBus(epiS32 busID)
{
    epiAssert(busID >= 0 && busID < g_EventBuses.size());
    return g_EventBuses[busID];
}

std::atomic<epiS32> EventBus::g_EventBusesCursor = 0;
std::array<EventBus, EventBus::MaxEventBusCount> EventBus::g_EventBuses;

epiS32 EventBus::ReserveEventBus()
{
    epiAssert(g_EventBusesCursor.load() < g_EventBuses.size(), "The number of EventBuses has been exceeded, increase the `MaxEventBusCount`");
    const epiS32 busID = g_EventBusesCursor.fetch_add(1);

    return busID;
}

epiS32 EventBus::Connect(epiS32 eventTypeID, EventFunc&& func)
{
    // TODO: make it thread-safe
    const epiS32 handlerID = m_EventHandlers.size();

    EventHandler handler;
    handler.EventTypeID = eventTypeID;
    handler.HandlerID = handlerID;
    handler.Callback = std::move(func);

    m_EventHandlers.push_back(std::move(handler));

    return handlerID;
}

void EventBus::Disonnect(epiS32 handlerID)
{
    // TODO: make it thread-safe
    auto it = std::find_if(m_EventHandlers.begin(), m_EventHandlers.end(), [handlerID](const EventHandler& handler)
    {
        return handlerID == handler.HandlerID;
    });

    epiAssert(it != m_EventHandlers.end());
    if (it != m_EventHandlers.end())
    {
        m_EventHandlers.erase(it);
    }
}

void EventBus::EventEmit(Event& event)
{
    for (auto& handler : m_EventHandlers)
    {
        if (handler.EventTypeID == event.GetEventTypeID())
        {
            handler(event);
        }
    }
}

EPI_NAMESPACE_END()
