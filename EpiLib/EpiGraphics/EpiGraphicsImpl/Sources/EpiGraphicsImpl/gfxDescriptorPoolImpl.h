#pragma once

#include "EpiGraphics/gfxDescriptorPool.h"

EPI_NAMESPACE_BEGIN()

class gfxDescriptorPool::Impl
{
public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    const epiArray<std::shared_ptr<gfxDescriptorSet::Impl>>& GetDescriptorSets() { return m_DescriptorSets; }

protected:
    epiArray<std::shared_ptr<gfxDescriptorSet::Impl>> m_DescriptorSets;
};

EPI_NAMESPACE_END()
