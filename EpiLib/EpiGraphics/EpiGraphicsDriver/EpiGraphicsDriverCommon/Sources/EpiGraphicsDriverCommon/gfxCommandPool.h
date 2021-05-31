#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxCommandPool.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxQueueFamily.h"
#include "EpiGraphicsDriverCommon/gfxCommandBuffer.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxCommandPoolImpl;

} // internalgfx

class gfxCommandPoolCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxCommandPoolCreateInfo)

EPI_GENHIDDEN_gfxCommandPoolCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xd83ebde9};

    enum gfxCommandPoolCreateInfo_PIDs
    {
        PID_QueueFamily = 0xfa954047,
        PID_Usage = 0x112a7174,
        PID_PrimaryCommandBufferCount = 0x180011ae,
        PID_SecondaryCommandBufferCount = 0x62333abe,
        PID_COUNT = 4
    };

protected:
    gfxQueueFamily m_QueueFamily{};
    gfxCommandPoolUsage m_Usage{};
    epiU32 m_PrimaryCommandBufferCount{0};
    epiU32 m_SecondaryCommandBufferCount{0};

EPI_GENREGION_END(gfxCommandPoolCreateInfo)
};

class gfxCommandPool : public Object
{
EPI_GENREGION_BEGIN(gfxCommandPool)

EPI_GENHIDDEN_gfxCommandPool()

public:
    constexpr static epiMetaTypeID TypeID{0x60157c7f};

    enum gfxCommandPool_PIDs
    {
        PID_PrimaryCommandBuffers = 0x5b976004,
        PID_SecondaryCommandBuffers = 0x50aeeab7,
        PID_COUNT = 2
    };

protected:
    epiArray<gfxCommandBuffer> m_PrimaryCommandBuffers{};
    epiArray<gfxCommandBuffer> m_SecondaryCommandBuffers{};

EPI_GENREGION_END(gfxCommandPool)

public:
    gfxCommandPool() = default;
    explicit gfxCommandPool(const std::shared_ptr<internalgfx::gfxCommandPoolImpl>& impl);

protected:
    epiPimpl<internalgfx::gfxCommandPoolImpl> m_Impl;
};

EPI_NAMESPACE_END()
