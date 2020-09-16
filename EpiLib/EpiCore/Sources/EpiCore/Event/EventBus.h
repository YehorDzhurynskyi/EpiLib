#pragma once

EPI_NAMESPACE_BEGIN()

struct Event
{
public:
    explicit Event(void* sender, epiS32 eventTypeID)
        : m_Sender{sender}
        , m_EventTypeID{eventTypeID}
    {}

public:
    inline const void* GetSender() const { return m_Sender; }
    inline epiS32 GetEventTypeID() const { return m_EventTypeID; }

    inline const void* GetClientData() const { return m_ClientData; }
    inline void* GetClientData() { return m_ClientData; }
    inline void SetClientData(void* clientData) { m_ClientData = clientData; }

protected:
    void* m_Sender{nullptr};
    epiS32 m_EventTypeID{-1};
    void* m_ClientData{nullptr};
};

using EventFunc = std::function<void(Event&)>;

class EventBus final
{
protected:
    class EventHandler
    {
    public:
        void operator()(Event& event);

        epiS32 EventTypeID{-1};
        epiS32 HandlerID{-1};
        EventFunc Callback;
    };

public:
    static EventBus& GetEventBus(epiS32 busID);
    static epiS32 ReserveEventBus();

protected:
    static constexpr epiU32 MaxEventBusCount = 10;

    static std::atomic<epiS32> g_EventBusesCursor;
    static std::array<EventBus, MaxEventBusCount> g_EventBuses;

public:
    EventBus() = default;
    EventBus(const EventBus&) = delete;
    EventBus(EventBus&&) = delete;
    EventBus& operator=(const EventBus&) = delete;
    EventBus& operator=(EventBus&&) = delete;
    ~EventBus() = default;

public:
    epiS32 Connect(epiS32 eventTypeID, EventFunc&& func);
    void Disonnect(epiS32 handlerID);

    void EventEmit(Event& event);

protected:
    std::vector<EventHandler> m_EventHandlers;
};

EPI_NAMESPACE_END()
