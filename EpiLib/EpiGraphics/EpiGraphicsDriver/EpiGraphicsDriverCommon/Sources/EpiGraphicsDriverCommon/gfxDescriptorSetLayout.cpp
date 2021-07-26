EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDescriptorSetLayout.h"
#include "EpiGraphicsDriverCommon/gfxDescriptorSetLayout.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxDescriptorSetLayoutCreateInfo& gfxDescriptorSetLayoutCreateInfo::AddBinding(epiU32 binding, gfxDescriptorType descriptorType, epiU32 descriptorCount, gfxShaderStage shaderStageMask)
{
    gfxDescriptorSetLayoutBinding layoutBinding;
    layoutBinding.SetBinding(binding);
    layoutBinding.SetDescriptorType(descriptorType);
    layoutBinding.SetDescriptorCount(descriptorCount);
    layoutBinding.SetShaderStageMask(shaderStageMask);

    GetBindings().push_back(layoutBinding);

    return *this;
}

gfxDescriptorSetLayout::gfxDescriptorSetLayout(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxDescriptorSetLayout::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

EPI_NAMESPACE_END()
