#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDescriptorSetLayout.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

class gfxDescriptorSetLayoutBinding : public Object
{
EPI_GENREGION_BEGIN(gfxDescriptorSetLayoutBinding)

EPI_GENHIDDEN_gfxDescriptorSetLayoutBinding()

public:
    constexpr static epiMetaTypeID TypeID{0x9243d9e4};

    enum gfxDescriptorSetLayoutBinding_PIDs
    {
        PID_Binding = 0x9ceb0eb9,
        PID_DescriptorType = 0xc183e584,
        PID_DescriptorCount = 0x2df3c685,
        PID_ShaderStageMask = 0x2883f685,
        PID_COUNT = 4
    };

protected:
    epiU32 m_Binding{0};
    gfxDescriptorType m_DescriptorType{};
    epiU32 m_DescriptorCount{0};
    gfxShaderStage m_ShaderStageMask{};

EPI_GENREGION_END(gfxDescriptorSetLayoutBinding)
};

class gfxDescriptorSetLayoutCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxDescriptorSetLayoutCreateInfo)

EPI_GENHIDDEN_gfxDescriptorSetLayoutCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x416e578};

    enum gfxDescriptorSetLayoutCreateInfo_PIDs
    {
        PID_UsageMask = 0x6be8b578,
        PID_Bindings = 0xa92f2f2d,
        PID_COUNT = 2
    };

protected:
    gfxDescriptorSetLayoutUsage m_UsageMask{};
    epiArray<gfxDescriptorSetLayoutBinding> m_Bindings{};

EPI_GENREGION_END(gfxDescriptorSetLayoutCreateInfo)

public:
    gfxDescriptorSetLayoutCreateInfo& AddBinding(epiU32 binding, gfxDescriptorType descriptorType, epiU32 descriptorCount, gfxShaderStage shaderStageMask);
};

class gfxDescriptorSetLayout : public Object
{
EPI_GENREGION_BEGIN(gfxDescriptorSetLayout)

EPI_GENHIDDEN_gfxDescriptorSetLayout()

public:
    constexpr static epiMetaTypeID TypeID{0xaf04381d};

    enum gfxDescriptorSetLayout_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxDescriptorSetLayout)

public:
    class Impl;

public:
    gfxDescriptorSetLayout() = default;
    explicit gfxDescriptorSetLayout(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
