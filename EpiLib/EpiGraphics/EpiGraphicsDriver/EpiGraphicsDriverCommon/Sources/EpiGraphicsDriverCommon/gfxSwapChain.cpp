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

epiBool gfxSwapChain::AssignRenderPass(const gfxRenderPass& renderPass, const gfxPipelineGraphics& pipeline)
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

    return m_Impl->AssignRenderPass(*renderPassImpl, *pipelineImpl);
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
