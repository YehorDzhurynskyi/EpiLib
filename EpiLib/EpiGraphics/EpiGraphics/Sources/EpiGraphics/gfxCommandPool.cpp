EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxCommandPool.h"
#include "EpiGraphics/gfxCommandPool.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImpl/gfxCommandPoolImpl.h"

EPI_NAMESPACE_BEGIN()

gfxCommandPool::gfxCommandPool(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
    {
        epiArray<gfxCommandBuffer>& commandBuffers = GetPrimaryCommandBuffers();
        commandBuffers.Clear();
        commandBuffers.Reserve(m_Impl->GetPrimaryCommandBuffers().Size());

        std::transform(m_Impl->GetPrimaryCommandBuffers().begin(),
                       m_Impl->GetPrimaryCommandBuffers().end(),
                       std::back_inserter(commandBuffers),
                       [](const std::shared_ptr<gfxCommandBuffer::Impl>& commandBufferImpl)
        {
            return gfxCommandBuffer(commandBufferImpl);
        });
    }

    {
        epiArray<gfxCommandBuffer>& commandBuffers = GetSecondaryCommandBuffers();
        commandBuffers.Clear();
        commandBuffers.Reserve(m_Impl->GetSecondaryCommandBuffers().Size());

        std::transform(m_Impl->GetSecondaryCommandBuffers().begin(),
                       m_Impl->GetSecondaryCommandBuffers().end(),
                       std::back_inserter(commandBuffers),
                       [](const std::shared_ptr<gfxCommandBuffer::Impl>& commandBufferImpl)
        {
            return gfxCommandBuffer(commandBufferImpl);
        });
    }
}

epiBool gfxCommandPool::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

EPI_NAMESPACE_END()
