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

    return m_Impl->Recreate(info, *surfaceImpl, *queueFamilyImpl, *renderPassImpl);
}

epiBool gfxSwapChain::AssignRenderPass(const gfxRenderPass& renderPass, const gfxPipelineGraphics& pipeline, const gfxBuffer& buffer)
{
    const auto renderPassImpl = renderPass.m_Impl;
    if (!renderPassImpl)
    {
        epiLogError("Failed to assign RenderPass to the SwapChain! RenderPass has no implementation!");
        return false;
    }

    const auto pipelineImpl = pipeline.m_Impl;
    if (!pipelineImpl)
    {
        epiLogError("Failed to assign Pipeline to the SwapChain! Pipeline has no implementation!");
        return false;
    }

    const auto bufferImpl = buffer.m_Impl;
    if (!bufferImpl)
    {
        epiLogError("Failed to assign Buffer to the SwapChain! Buffer has no implementation!");
        return false;
    }

    return m_Impl->AssignRenderPass(*renderPassImpl, *pipelineImpl, *bufferImpl);
}

epiBool gfxSwapChain::Present(const gfxQueue& queue)
{
    const auto queueImpl = queue.m_Impl;
    if (!queueImpl)
    {
        epiLogError("Failed to present SwapChain! Queue has no implementation!");
        return false;
    }

    return m_Impl->Present(*queueImpl);
}

epiSize2u gfxSwapChain::GetExtent_Callback() const
{
    return m_Impl->GetExtent();
}

EPI_NAMESPACE_END()
