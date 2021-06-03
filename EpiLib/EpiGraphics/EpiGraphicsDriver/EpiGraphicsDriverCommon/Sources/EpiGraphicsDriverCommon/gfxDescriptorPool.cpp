EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDescriptorPool.h"
#include "EpiGraphicsDriverCommon/gfxDescriptorPool.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxDescriptorPoolCreateInfo& gfxDescriptorPoolCreateInfo::AddDescriptorPoolSize(const gfxDescriptorPoolSize& poolSize)
{
    GetPoolSizes().push_back(poolSize);

    return *this;
}

gfxDescriptorPoolCreateInfo& gfxDescriptorPoolCreateInfo::AddDescriptorSetLayout(const gfxDescriptorSetLayout& layout)
{
    GetDescriptorSetLayouts().push_back(layout);

    return *this;
}

gfxDescriptorPool::gfxDescriptorPool(const std::shared_ptr<internalgfx::gfxDescriptorPoolImpl>& impl)
    : m_Impl{impl}
{
    {
        epiArray<gfxDescriptorSet>& descriptorSets = GetDescriptorSets();
        descriptorSets.Clear();
        descriptorSets.Reserve(m_Impl->GetDescriptorSets().Size());

        std::transform(m_Impl->GetDescriptorSets().begin(),
                       m_Impl->GetDescriptorSets().end(),
                       std::back_inserter(descriptorSets),
                       [](const std::shared_ptr<internalgfx::gfxDescriptorSetImpl>& descriptorSetImpl)
        {
            return gfxDescriptorSet(descriptorSetImpl);
        });
    }
}

EPI_NAMESPACE_END()
