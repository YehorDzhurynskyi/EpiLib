EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSwapChain.h"
#include "EpiGraphicsDriverCommon/gfxSwapChain.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxSwapChain::gfxSwapChain(const std::shared_ptr<internalgfx::gfxSwapChainImpl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxSwapChain::Recreate(const gfxSwapChainCreateInfo& info)
{
    const auto surfaceImpl = info.GetSurface().m_Impl;
    if (!surfaceImpl)
    {
        epiLogError("Failed to recreate SwapChain! Provided Surface has no implementation!");
        return false;
    }

    const auto queueFamilyImpl = info.GetQueueFamily().m_Impl;
    if (!queueFamilyImpl)
    {
        epiLogError("Failed to recreate SwapChain! Provided QueueFamily has no implementation!");
        return false;
    }

    const auto renderPassImpl = info.GetRenderPass().m_Impl;
    if (!renderPassImpl)
    {
        epiLogError("Failed to recreate SwapChain! Provided RenderPass has no implementation!");
        return false;
    }

    if (!m_Impl->Recreate(info, *surfaceImpl, *queueFamilyImpl, *renderPassImpl))
    {
        return false;
    }

    return true;
}

gfxCommandBufferRecord gfxSwapChain::ForBufferRecordCommands(epiU32 bufferIndex, gfxCommandBufferUsage usageMask)
{
    return m_Impl->ForBufferRecordCommands(bufferIndex, usageMask);
}

gfxRenderPassBeginInfo gfxSwapChain::ForBufferCreateRenderPassBeginInfo(epiU32 bufferIndex,
                                                            const gfxRenderPass& renderPass,
                                                            const epiArray<gfxRenderPassClearValue>& renderPassClearValues)
{
    return m_Impl->ForBufferCreateRenderPassBeginInfo(bufferIndex, renderPass, renderPassClearValues);
}

epiBool gfxSwapChain::Present(const gfxQueue& queue, std::function<void(epiU32)> callback)
{
    const auto queueImpl = queue.m_Impl;
    if (!queueImpl)
    {
        epiLogError("Failed to present SwapChain! Queue has no implementation!");
        return false;
    }

    return m_Impl->Present(*queueImpl, callback);
}

epiU32 gfxSwapChain::GetBufferCount_Callback() const
{
    return m_Impl->GetBufferCount();
}

epiSize2u gfxSwapChain::GetExtent_Callback() const
{
    return m_Impl->GetExtent();
}

EPI_NAMESPACE_END()
