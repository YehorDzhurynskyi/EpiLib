EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxSwapChain.h"
#include "EpiGraphicsDriverCommon/gfxSwapChain.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxSwapChain::gfxSwapChain(const std::shared_ptr<internalgfx::gfxSwapChainImpl>& impl)
    : m_Impl{impl}
{
    RebindImpl();
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

    RebindImpl();

    return true;
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

void gfxSwapChain::RebindImpl()
{
    {
        epiArray<gfxCommandBuffer>& commandBuffers = GetCommandBuffers();
        commandBuffers.Clear();
        commandBuffers.Reserve(m_Impl->GetCommandBuffers().Size());

        std::transform(m_Impl->GetCommandBuffers().begin(),
                       m_Impl->GetCommandBuffers().end(),
                       std::back_inserter(commandBuffers),
                       [](const std::shared_ptr<internalgfx::gfxCommandBufferImpl>& commandBufferImpl)
        {
            return gfxCommandBuffer(commandBufferImpl);
        });
    }

    {
        epiArray<gfxFrameBuffer>& frameBuffers = GetFrameBuffers();
        frameBuffers.Clear();
        frameBuffers.Reserve(m_Impl->GetFrameBuffers().Size());

        std::transform(m_Impl->GetFrameBuffers().begin(),
                       m_Impl->GetFrameBuffers().end(),
                       std::back_inserter(frameBuffers),
                       [](const std::shared_ptr<internalgfx::gfxFrameBufferImpl>& frameBufferImpl)
        {
            return gfxFrameBuffer(frameBufferImpl);
        });
    }
}

epiSize2u gfxSwapChain::GetExtent_Callback() const
{
    return m_Impl->GetExtent();
}

EPI_NAMESPACE_END()
