EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDescriptorSet.h"
#include "EpiGraphics/gfxDescriptorSet.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxDescriptorSet::gfxDescriptorSet(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxDescriptorSet::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

gfxDescriptorSetWrite& gfxDescriptorSetWrite::AddBufferInfo(const gfxDescriptorBufferInfo& bufferInfo)
{
    GetBufferInfos().push_back(bufferInfo);

    return *this;
}

gfxDescriptorSetWrite& gfxDescriptorSetWrite::AddImageInfo(const gfxDescriptorImageInfo& imageInfo)
{
    GetImageInfos().push_back(imageInfo);

    return *this;
}

EPI_NAMESPACE_END()
