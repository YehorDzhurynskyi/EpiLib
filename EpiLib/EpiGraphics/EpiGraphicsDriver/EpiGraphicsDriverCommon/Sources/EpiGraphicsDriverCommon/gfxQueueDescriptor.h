#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxQueue.h"
#include "EpiGraphicsDriverCommon/gfxQueueFamily.h"

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
        PID_QueueFamily = 0xfa954047,
        PID_Priorities = 0x96844307,
        PID_DesiredQueueCount = 0xbfd2ceb,
        PID_COUNT = 4
    };

protected:
    epiU32 GetDesiredQueueCount_Callback() const;

protected:
    gfxQueueType m_Type{};
    gfxQueueFamily* m_QueueFamily{nullptr};
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
    std::vector<gfxQueue> m_Queues; // TODO: epiArray can't be used with move only types. should be fixed
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
        PID_Size = 0x57f28b54,
        PID_COUNT = 1
    };

protected:
    epiSize_t GetSize_Callback() const;

EPI_GENREGION_END(gfxQueueDescriptorList)

public:
    using iterator = std::vector<gfxQueueDescriptor>::iterator;
    using const_iterator = std::vector<gfxQueueDescriptor>::const_iterator;

public:
    void Add(gfxQueueType type, const epiArray<epiFloat>& priorities);
    void Add(gfxQueueDescriptor&& desc);

    gfxQueueDescriptor& At(epiU32 index);
    const gfxQueueDescriptor& At(epiU32 index) const;

    gfxQueueDescriptor& operator[](epiU32 index);
    const gfxQueueDescriptor& operator[](epiU32 index) const;

    iterator begin() { return m_QueueDescriptors.begin(); }
    iterator end() { return m_QueueDescriptors.end(); }
    const_iterator begin() const { return m_QueueDescriptors.begin(); }
    const_iterator end() const { return m_QueueDescriptors.end(); }

protected:
    std::vector<gfxQueueDescriptor> m_QueueDescriptors;
};

EPI_NAMESPACE_END()
