#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxQueue.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxSurfaceImpl;

} // internalgfx

class gfxSurface;
class gfxQueueDescriptor : public Object
{
EPI_GENREGION_BEGIN(gfxQueueDescriptor)

EPI_GENHIDDEN_gfxQueueDescriptor()

public:
    constexpr static epiMetaTypeID TypeID{0x61079bac};

    enum gfxQueueDescriptor_PIDs
    {
        PID_Type = 0x2cecf817,
        PID_Priorities = 0x96844307,
        PID_DesiredQueueCount = 0xbfd2ceb,
        PID_COUNT = 3
    };

protected:
    epiU32 GetDesiredQueueCount_Callback() const;

protected:
    gfxQueueType m_Type{};
    epiArray<epiFloat> m_Priorities{};

EPI_GENREGION_END(gfxQueueDescriptor)

public:
    epiBool IsResolved() const;
    epiBool TryResolveQueue(gfxQueue&& queue);

    epiBool IsPresentRequired() const;

    void AddDesiredQueue(epiFloat priority);

    void AcquireQueues(std::vector<gfxQueue>& queues);

    const internalgfx::gfxSurfaceImpl* GetPresentSurface() const;
    void SetPresentSurface(const internalgfx::gfxSurfaceImpl* surfaceImpl);

protected:
    std::vector<gfxQueue> m_Queues;
    const internalgfx::gfxSurfaceImpl* m_PresentSurface{nullptr};
};

class gfxQueueDescriptorList : public Object
{
EPI_GENREGION_BEGIN(gfxQueueDescriptorList)

EPI_GENHIDDEN_gfxQueueDescriptorList()

public:
    constexpr static epiMetaTypeID TypeID{0x67f56183};

    enum gfxQueueDescriptorList_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxQueueDescriptorList)

public:
    using iterator = std::vector<gfxQueueDescriptor>::iterator;
    using const_iterator = std::vector<gfxQueueDescriptor>::const_iterator;

public:
    void Add(gfxQueueType type, const epiArray<epiFloat>& priorities);
    void Add(gfxQueueDescriptor&& desc);

    iterator begin() { return m_QueueDescriptors.begin(); }
    iterator end() { return m_QueueDescriptors.end(); }
    const_iterator begin() const { return m_QueueDescriptors.begin(); }
    const_iterator end() const { return m_QueueDescriptors.end(); }

protected:
    std::vector<gfxQueueDescriptor> m_QueueDescriptors;
};

EPI_NAMESPACE_END()
