#pragma once

#include "EpiGraphics/gfxCommandPool.h"

EPI_NAMESPACE_BEGIN()

class gfxCommandPool::Impl
{
public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    const epiArray<std::shared_ptr<gfxCommandBuffer::Impl>>& GetPrimaryCommandBuffers() { return m_PrimaryCommandBuffers; }
    const epiArray<std::shared_ptr<gfxCommandBuffer::Impl>>& GetSecondaryCommandBuffers() { return m_SecondaryCommandBuffers; }

protected:
    epiArray<std::shared_ptr<gfxCommandBuffer::Impl>> m_PrimaryCommandBuffers;
    epiArray<std::shared_ptr<gfxCommandBuffer::Impl>> m_SecondaryCommandBuffers;
};

EPI_NAMESPACE_END()
