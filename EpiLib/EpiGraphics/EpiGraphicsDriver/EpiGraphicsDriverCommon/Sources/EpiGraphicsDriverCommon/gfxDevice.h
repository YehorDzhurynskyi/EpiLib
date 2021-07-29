#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDevice.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.h"
#include "EpiGraphicsDriverCommon/gfxQueue.h"
#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxSwapChain.h"
#include "EpiGraphicsDriverCommon/gfxRenderPass.h"
#include "EpiGraphicsDriverCommon/gfxPipelineLayout.h"
#include "EpiGraphicsDriverCommon/gfxPipeline.h"
#include "EpiGraphicsDriverCommon/gfxFrameBuffer.h"
#include "EpiGraphicsDriverCommon/gfxImage.h"
#include "EpiGraphicsDriverCommon/gfxImageView.h"
#include "EpiGraphicsDriverCommon/gfxCommandPool.h"
#include "EpiGraphicsDriverCommon/gfxBuffer.h"
#include "EpiGraphicsDriverCommon/gfxDeviceMemory.h"
#include "EpiGraphicsDriverCommon/gfxDescriptorPool.h"
#include "EpiGraphicsDriverCommon/gfxDescriptorSetLayout.h"
#include "EpiGraphicsDriverCommon/gfxDescriptorSet.h"
#include "EpiGraphicsDriverCommon/gfxSampler.h"
#include "EpiGraphicsDriverCommon/Synchronization/gfxSemaphore.h"
#include "EpiGraphicsDriverCommon/Synchronization/gfxFence.h"

EPI_NAMESPACE_BEGIN()

class gfxDeviceCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxDeviceCreateInfo)

EPI_GENHIDDEN_gfxDeviceCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x6b578813};

    enum gfxDeviceCreateInfo_PIDs
    {
        PID_PhysicalDevice = 0xdb69328a,
        PID_QueueDescriptorList = 0xf5d1762d,
        PID_ExtensionsRequired = 0x8d4676b0,
        PID_FeaturesRequired = 0x13fa62aa,
        PID_COUNT = 4
    };

protected:
    gfxPhysicalDevice m_PhysicalDevice{};
    gfxQueueDescriptorList m_QueueDescriptorList{};
    epiArray<gfxPhysicalDeviceExtension> m_ExtensionsRequired{};
    epiArray<gfxPhysicalDeviceFeature> m_FeaturesRequired{};

EPI_GENREGION_END(gfxDeviceCreateInfo)
};

class gfxDevice : public Object
{
EPI_GENREGION_BEGIN(gfxDevice)

EPI_GENHIDDEN_gfxDevice()

public:
    constexpr static epiMetaTypeID TypeID{0xa849dda8};

    enum gfxDevice_PIDs
    {
        PID_QueueFamilies = 0x459d6c2c,
        PID_COUNT = 1
    };

protected:
    epiArray<gfxQueueFamily> m_QueueFamilies{};

EPI_GENREGION_END(gfxDevice)

public:
    class Impl;

public:
    gfxDevice() = default;
    explicit gfxDevice(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    epiBool IsExtensionEnabled(gfxPhysicalDeviceExtension extension) const;
    epiBool IsFeatureEnabled(gfxPhysicalDeviceFeature feature) const;

    epiBool UpdateDescriptorSets(const epiArray<gfxDescriptorSetWrite>& writes, const epiArray<gfxDescriptorSetCopy>& copies) const;

    // TODO: add From suffix
    std::optional<gfxSwapChain> CreateSwapChain(const gfxSwapChainCreateInfo& info) const;
    std::optional<gfxRenderPass> CreateRenderPass(const gfxRenderPassCreateInfo& info) const;
    std::optional<gfxPipelineLayout> CreatePipelineLayout(const gfxPipelineLayoutCreateInfo& info) const;
    std::optional<gfxPipelineGraphics> CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info) const;
    std::optional<gfxShaderModule> CreateShaderModule(const gfxShaderModuleCreateInfo& info) const;
    std::optional<gfxFrameBuffer> CreateFrameBuffer(const gfxFrameBufferCreateInfo& info) const;
    std::optional<gfxImage> CreateImage(const gfxImageCreateInfo& info) const;
    std::optional<gfxImageView> CreateImageView(const gfxImageViewCreateInfo& info) const;
    std::optional<gfxSampler> CreateSampler(const gfxSamplerCreateInfo& info) const;
    std::optional<gfxCommandPool> CreateCommandPool(const gfxCommandPoolCreateInfo& info) const;
    std::optional<gfxBuffer> CreateBuffer(const gfxBufferCreateInfo& info) const;
    std::optional<gfxDeviceMemory> CreateDeviceMemory(const gfxDeviceMemoryBufferCreateInfo& info) const;
    std::optional<gfxDeviceMemory> CreateDeviceMemory(const gfxDeviceMemoryImageCreateInfo& info) const;
    std::optional<gfxDescriptorSetLayout> CreateDescriptorSetLayout(const gfxDescriptorSetLayoutCreateInfo& info) const;
    std::optional<gfxDescriptorPool> CreateDescriptorPool(const gfxDescriptorPoolCreateInfo& info) const;
    std::optional<gfxSemaphore> CreateSemaphoreFrom(const gfxSemaphoreCreateInfo& info) const;
    std::optional<gfxFence> CreateFence(const gfxFenceCreateInfo& info) const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
