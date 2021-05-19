EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxPipeline.h"
#include "EpiGraphicsDriverCommon/gfxPipeline.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxPipelineVertexInputBindingDescription& gfxPipelineVertexInputBindingDescription::AddAttribute(epiU32 location, gfxFormat format, epiU32 offset)
{
    gfxPipelineVertexInputAttributeDescription attr{};
    attr.SetLocation(location);
    attr.SetFormat(format);
    attr.SetOffset(offset);

    GetAttributeDescriptions().push_back(attr);

    return *this;
}

gfxPipelineGraphicsCreateInfo& gfxPipelineGraphicsCreateInfo::AddScissor(const epiRect2s& scissor)
{
    GetScissors().push_back(scissor);

    return *this;
}

gfxPipelineGraphicsCreateInfo& gfxPipelineGraphicsCreateInfo::AddViewport(const gfxPipelineViewport& viewport)
{
    GetViewports().push_back(viewport);

    return *this;
}

gfxPipelineGraphicsCreateInfo& gfxPipelineGraphicsCreateInfo::AddColorBlendAttachment(const gfxPipelineColorBlendAttachment& attachment)
{
    GetColorBlendAttachments().push_back(attachment);

    return *this;
}

gfxPipelineGraphicsCreateInfo& gfxPipelineGraphicsCreateInfo::AddDynamicState(gfxPipelineDynamicState state)
{
    GetDynamicStates().push_back(state);

    return *this;
}

gfxPipelineGraphicsCreateInfo& gfxPipelineGraphicsCreateInfo::AddVertexInputBinding(const gfxPipelineVertexInputBindingDescription& vertexInputBinding)
{
    GetVertexInputBindingDescriptions().push_back(vertexInputBinding);

    return *this;
}

gfxPipelineGraphics::gfxPipelineGraphics(const std::shared_ptr<internalgfx::gfxPipelineGraphicsImpl>& impl)
    : m_Impl{impl}
{
}

EPI_NAMESPACE_END()
