#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDescriptorPool.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxDescriptorSet.h"
#include "EpiGraphicsDriverCommon/gfxDescriptorSetLayout.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDescriptorPoolImpl;

} // namespace internalgfx

class gfxDescriptorPoolSize : public Object
{
EPI_GENREGION_BEGIN(gfxDescriptorPoolSize)

EPI_GENHIDDEN_gfxDescriptorPoolSize()

public:
    constexpr static epiMetaTypeID TypeID{0xef60c120};

    enum gfxDescriptorPoolSize_PIDs
    {
        PID_DescriptorType = 0xc183e584,
        PID_DescriptorCount = 0x2df3c685,
        PID_COUNT = 2
    };

protected:
    gfxDescriptorType m_DescriptorType{};
    epiU32 m_DescriptorCount{0};

EPI_GENREGION_END(gfxDescriptorPoolSize)
};

class gfxDescriptorPoolCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxDescriptorPoolCreateInfo)

EPI_GENHIDDEN_gfxDescriptorPoolCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x28f2a92f};

    enum gfxDescriptorPoolCreateInfo_PIDs
    {
        PID_UsageMask = 0x6be8b578,
        PID_MaxSets = 0xa74189c5,
        PID_PoolSizes = 0x2e254b92,
        PID_DescriptorSetLayouts = 0x495b0d12,
        PID_COUNT = 4
    };

protected:
    gfxDescriptorPoolUsage m_UsageMask{};
    epiU32 m_MaxSets{0};
    epiArray<gfxDescriptorPoolSize> m_PoolSizes{};
    epiArray<gfxDescriptorSetLayout> m_DescriptorSetLayouts{};

EPI_GENREGION_END(gfxDescriptorPoolCreateInfo)

public:
    gfxDescriptorPoolCreateInfo& AddDescriptorPoolSize(const gfxDescriptorPoolSize& poolSize);
    gfxDescriptorPoolCreateInfo& AddDescriptorSetLayout(const gfxDescriptorSetLayout& layout);
};

class gfxDescriptorPool : public Object
{
EPI_GENREGION_BEGIN(gfxDescriptorPool)

EPI_GENHIDDEN_gfxDescriptorPool()

public:
    constexpr static epiMetaTypeID TypeID{0xaea4a5c};

    enum gfxDescriptorPool_PIDs
    {
        PID_DescriptorSets = 0xd9d0f77c,
        PID_COUNT = 1
    };

protected:
    epiArray<gfxDescriptorSet> m_DescriptorSets{};

EPI_GENREGION_END(gfxDescriptorPool)

public:
    gfxDescriptorPool() = default;
    explicit gfxDescriptorPool(const std::shared_ptr<internalgfx::gfxDescriptorPoolImpl>& impl);

protected:
    epiPimpl<internalgfx::gfxDescriptorPoolImpl> m_Impl;
};

EPI_NAMESPACE_END()
