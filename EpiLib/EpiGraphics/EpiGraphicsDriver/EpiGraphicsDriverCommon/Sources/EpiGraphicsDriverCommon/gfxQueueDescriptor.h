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
        PID_TypeMask = 0x6957f143,
        PID_Priorities = 0x96844307,
        PID_QueueCount = 0xf330505b,
        PID_COUNT = 3
    };

protected:
    epiU32 GetQueueCount_Callback() const;

protected:
    gfxQueueType m_TypeMask{};
    epiArray<epiFloat> m_Priorities{};

EPI_GENREGION_END(gfxQueueDescriptor)

public:
    gfxQueueDescriptor(gfxQueueType typeMask, const epiArray<epiFloat>& priorities, const epiPtrArray<gfxSurface>& surfaceTargets = {});

    const epiPtrArray<internalgfx::gfxSurfaceImpl>& GetSurfaceTargets() const;

protected:
    epiPtrArray<internalgfx::gfxSurfaceImpl> m_SurfaceTargets{};
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
