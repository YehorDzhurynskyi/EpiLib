EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDescriptorSet.h"
#include "EpiGraphicsDriverCommon/gfxDescriptorSet.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxDescriptorSet::gfxDescriptorSet(const std::shared_ptr<internalgfx::gfxDescriptorSetImpl>& impl)
    : m_Impl{impl}
{
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
