#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxPipelineLayout.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxDescriptorSetLayout.h"

EPI_NAMESPACE_BEGIN()

class gfxPipelineLayoutCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxPipelineLayoutCreateInfo)

EPI_GENHIDDEN_gfxPipelineLayoutCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x55b863a1};

    enum gfxPipelineLayoutCreateInfo_PIDs
    {
        PID_DescriptorSetLayouts = 0x495b0d12,
        PID_COUNT = 1
    };

protected:
    epiArray<gfxDescriptorSetLayout> m_DescriptorSetLayouts{};

EPI_GENREGION_END(gfxPipelineLayoutCreateInfo)

public:
    gfxPipelineLayoutCreateInfo& AddDescriptorSetLayout(const gfxDescriptorSetLayout& layout);
};

class gfxPipelineLayout : public Object
{
EPI_GENREGION_BEGIN(gfxPipelineLayout)

EPI_GENHIDDEN_gfxPipelineLayout()

public:
    constexpr static epiMetaTypeID TypeID{0x399945a8};

    enum gfxPipelineLayout_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxPipelineLayout)

public:
    class Impl;

public:
    gfxPipelineLayout() = default;
    explicit gfxPipelineLayout(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
