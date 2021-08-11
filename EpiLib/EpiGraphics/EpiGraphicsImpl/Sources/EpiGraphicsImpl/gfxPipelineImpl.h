#pragma once

#include "EpiGraphics/gfxPipeline.h"

EPI_NAMESPACE_BEGIN()

class gfxPipelineGraphics::Impl
{
public:
    static const gfxPipelineGraphics::Impl* ExtractImpl(const gfxPipelineGraphics& pipeline) { return pipeline.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    epiBool IsDynamic(gfxPipelineDynamicState state) const { return m_DynamicStates[static_cast<epiU32>(state)]; }

    const epiArray<gfxPipelineViewport>& GetViewports() const { return m_Viewports; }
    epiArray<gfxPipelineViewport>& GetViewports() { return m_Viewports; }
    const epiArray<epiRect2s>& GetScissors() const { return m_Scissors; }
    epiArray<epiRect2s>& GetScissors() { return m_Scissors; }

protected:
    epiBool m_DynamicStates[static_cast<epiU32>(gfxPipelineDynamicState::COUNT)]{};
    epiArray<gfxPipelineViewport> m_Viewports{};
    epiArray<epiRect2s> m_Scissors{};
};

EPI_NAMESPACE_END()
