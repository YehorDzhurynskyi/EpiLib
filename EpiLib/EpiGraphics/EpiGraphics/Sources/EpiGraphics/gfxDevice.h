#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDevice.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxPhysicalDevice.h"
#include "EpiGraphics/gfxQueue.h"
#include "EpiGraphics/gfxEnum.h"
#include "EpiGraphics/gfxSwapChain.h"
#include "EpiGraphics/gfxRenderPass.h"
#include "EpiGraphics/gfxPipelineLayout.h"
#include "EpiGraphics/gfxPipeline.h"
#include "EpiGraphics/gfxFrameBuffer.h"
#include "EpiGraphics/gfxImage.h"
#include "EpiGraphics/gfxImageView.h"
#include "EpiGraphics/gfxCommandPool.h"
#include "EpiGraphics/gfxBuffer.h"
#include "EpiGraphics/gfxDeviceMemory.h"
#include "EpiGraphics/gfxDescriptorPool.h"
#include "EpiGraphics/gfxDescriptorSetLayout.h"
#include "EpiGraphics/gfxDescriptorSet.h"
#include "EpiGraphics/gfxSampler.h"
#include "EpiGraphics/Synchronization/gfxSemaphore.h"
#include "EpiGraphics/Synchronization/gfxFence.h"

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
