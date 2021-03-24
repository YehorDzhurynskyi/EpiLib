EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxPipeline.h"
#include "EpiGraphicsDriverCommon/gfxPipeline.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxPipelineCreateInfo& gfxPipelineCreateInfo::AddScissor(const epiRect2s& scissor)
{
    GetScissors().push_back(scissor);

    return *this;
}

gfxPipelineCreateInfo& gfxPipelineCreateInfo::AddViewport(const gfxPipelineViewport& viewport)
{
    GetViewports().push_back(viewport);

    return *this;
}

gfxPipelineCreateInfo& gfxPipelineCreateInfo::AddColorBlendAttachment(const gfxPipelineColorBlendAttachment& attachment)
{
    GetColorBlendAttachments().push_back(attachment);

    return *this;
}

gfxPipeline::gfxPipeline(internalgfx::gfxPipelineImpl* impl)
    : m_Impl{impl}
{
}

gfxPipeline::gfxPipeline(gfxPipeline&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;
}

gfxPipeline& gfxPipeline::operator=(gfxPipeline&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;

    return *this;
}

gfxPipeline::~gfxPipeline()
{
    delete m_Impl;
}

EPI_NAMESPACE_END()
