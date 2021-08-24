#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxQueueFamily.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxEnum.h"
#include "EpiGraphics/gfxQueue.h"

EPI_NAMESPACE_BEGIN()

class gfxQueueFamilyDescriptor : public Object
{
EPI_GENREGION_BEGIN(gfxQueueFamilyDescriptor)

EPI_GENHIDDEN_gfxQueueFamilyDescriptor()

public:
    constexpr static epiMetaTypeID TypeID{0xfa02338a};

    enum gfxQueueFamilyDescriptor_PIDs
    {
        PID_QueueTypeSupportedMask = 0xb25513f0,
        PID_QueueCount = 0xf330505b,
        PID_COUNT = 2
    };

protected:
    gfxQueueType GetQueueTypeSupportedMask_Callback() const;
    epiU32 GetQueueCount_Callback() const;

EPI_GENREGION_END(gfxQueueFamilyDescriptor)

public:
    class Impl;

public:
    gfxQueueFamilyDescriptor() = default;
    explicit gfxQueueFamilyDescriptor(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    epiBool IsQueueTypeSupported(gfxQueueType mask) const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

class gfxQueueFamily : public Object
{
EPI_GENREGION_BEGIN(gfxQueueFamily)

EPI_GENHIDDEN_gfxQueueFamily()

public:
    constexpr static epiMetaTypeID TypeID{0x25e95f0c};

    enum gfxQueueFamily_PIDs
    {
        PID_Queues = 0xc86607a0,
        PID_QueueTypeSupportedMask = 0xb25513f0,
        PID_QueueCount = 0xf330505b,
        PID_COUNT = 3
    };

protected:
    gfxQueueType GetQueueTypeSupportedMask_Callback() const;
    epiU32 GetQueueCount_Callback() const;

protected:
    epiArray<gfxQueue> m_Queues{};

EPI_GENREGION_END(gfxQueueFamily)

public:
    class Impl;

public:
    gfxQueueFamily() = default;
    explicit gfxQueueFamily(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    const gfxQueue& At(epiU32 index) const;
    gfxQueue& At(epiU32 index);

    const gfxQueue& operator[](epiU32 index) const;
    gfxQueue& operator[](epiU32 index);

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()