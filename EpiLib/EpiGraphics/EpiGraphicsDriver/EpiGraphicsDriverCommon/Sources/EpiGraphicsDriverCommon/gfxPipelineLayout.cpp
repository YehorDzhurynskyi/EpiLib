EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxPipelineLayout.h"
#include "EpiGraphicsDriverCommon/gfxPipelineLayout.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxPipelineLayoutCreateInfo& gfxPipelineLayoutCreateInfo::AddDescriptorSetLayout(const gfxDescriptorSetLayout& layout)
{
    GetDescriptorSetLayouts().push_back(layout);

    return *this;
}

gfxPipelineLayout::gfxPipelineLayout(const std::shared_ptr<internalgfx::gfxPipelineLayoutImpl>& impl)
    : m_Impl{impl}
{
}

EPI_NAMESPACE_END()
