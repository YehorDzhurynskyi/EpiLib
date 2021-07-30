EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxPipelineLayout.h"
#include "EpiGraphics/gfxPipelineLayout.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxPipelineLayoutCreateInfo& gfxPipelineLayoutCreateInfo::AddDescriptorSetLayout(const gfxDescriptorSetLayout& layout)
{
    GetDescriptorSetLayouts().push_back(layout);

    return *this;
}

gfxPipelineLayout::gfxPipelineLayout(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxPipelineLayout::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

EPI_NAMESPACE_END()
