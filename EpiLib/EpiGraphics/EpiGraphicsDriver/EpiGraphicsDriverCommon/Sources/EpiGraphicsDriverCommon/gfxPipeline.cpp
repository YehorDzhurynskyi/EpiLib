EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxPipeline.h"
#include "EpiGraphicsDriverCommon/gfxPipeline.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

epiBool gfxPipelineViewport::IsValid() const
{
    return !GetRect().IsEmpty() && (GetMinDepth() <= GetMaxDepth());
}

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

epiBool gfxPipelineGraphics::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

epiBool gfxPipelineGraphics::IsDynamic(gfxPipelineDynamicState state) const
{
    return m_Impl->IsDynamic(state);
}

void gfxPipelineGraphics::DynamicClearViewports()
{
    // TODO: [epigen] add non-const GetViewports_Callback() instead of this method
    if (!IsDynamic(gfxPipelineDynamicState::Viewport))
    {
        epiLogWarn("Dynamic state update is discarded since `Viewport` isn't a dynamic state!");
        return;
    }

    m_Impl->GetViewports().Clear();
}

void gfxPipelineGraphics::DynamicClearScissors()
{
    // TODO: [epigen] add non-const GetScissors_Callback() instead of this method
    if (!IsDynamic(gfxPipelineDynamicState::Scissor))
    {
        epiLogWarn("Dynamic state update is discarded since `Scissor` isn't a dynamic state!");
        return;
    }

    m_Impl->GetScissors().Clear();
}

void gfxPipelineGraphics::DynamicAddViewport(const gfxPipelineViewport& viewport)
{
    if (!IsDynamic(gfxPipelineDynamicState::Viewport))
    {
        epiLogWarn("Dynamic state update is discarded since `Viewport` isn't a dynamic state!");
    }

    m_Impl->GetViewports().push_back(viewport);
}

void gfxPipelineGraphics::DynamicAddScissor(const epiRect2s& scissor)
{
    if (!IsDynamic(gfxPipelineDynamicState::Scissor))
    {
        epiLogWarn("Dynamic state update is discarded since `Scissor` isn't a dynamic state!");
        return;
    }

    m_Impl->GetScissors().push_back(scissor);
}

const epiArray<gfxPipelineViewport>& gfxPipelineGraphics::GetViewports_Callback() const
{
    return m_Impl->GetViewports();
}

const epiArray<epiRect2s>& gfxPipelineGraphics::GetScissors_Callback() const
{
    return m_Impl->GetScissors();
}

EPI_NAMESPACE_END()
