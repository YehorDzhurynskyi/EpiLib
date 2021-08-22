#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDevice.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxQueue.h"
#include "EpiGraphics/gfxQueueDescriptor.h"
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
#include "EpiGraphics/gfxDeviceMemoryAllocator.h"
#include "EpiGraphics/gfxDescriptorPool.h"
#include "EpiGraphics/gfxDescriptorSetLayout.h"
#include "EpiGraphics/gfxDescriptorSet.h"
#include "EpiGraphics/gfxSampler.h"
#include "EpiGraphics/Synchronization/gfxSemaphore.h"
#include "EpiGraphics/Synchronization/gfxFence.h"

EPI_NAMESPACE_BEGIN()

class gfxMemoryRequirements : public Object
{
EPI_GENREGION_BEGIN(gfxMemoryRequirements)

EPI_GENHIDDEN_gfxMemoryRequirements()

public:
    constexpr static epiMetaTypeID TypeID{0x5c680a91};

    enum gfxMemoryRequirements_PIDs
    {
        PID_Size = 0x57f28b54,
        PID_Alignment = 0xae3f9cff,
        PID_COUNT = 2
    };

protected:
    epiSize_t m_Size{0};
    epiSize_t m_Alignment{0};

EPI_GENREGION_END(gfxMemoryRequirements)
};

class gfxDeviceCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxDeviceCreateInfo)

EPI_GENHIDDEN_gfxDeviceCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x6b578813};

    enum gfxDeviceCreateInfo_PIDs
    {
        PID_QueueDescriptorList = 0xf5d1762d,
        PID_ExtensionsRequired = 0x8d4676b0,
        PID_FeaturesRequired = 0x13fa62aa,
        PID_COUNT = 3
    };

protected:
    gfxQueueDescriptorList m_QueueDescriptorList{};
    epiArray<gfxPhysicalDeviceExtension> m_ExtensionsRequired{};
    epiArray<gfxPhysicalDeviceFeature> m_FeaturesRequired{};

EPI_GENREGION_END(gfxDeviceCreateInfo)
};

class gfxPhysicalDevice;
class gfxDevice : public Object
{
EPI_GENREGION_BEGIN(gfxDevice)

EPI_GENHIDDEN_gfxDevice()

public:
    constexpr static epiMetaTypeID TypeID{0xa849dda8};

    enum gfxDevice_PIDs
    {
        PID_PhysicalDevice = 0xdb69328a,
        PID_QueueFamilies = 0x459d6c2c,
        PID_COUNT = 2
    };

protected:
    const gfxPhysicalDevice& GetPhysicalDevice_Callback() const;

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

    std::optional<gfxMemoryRequirements> MemoryRequirementsOf(const gfxBuffer& buffer) const;
    std::optional<gfxMemoryRequirements> MemoryRequirementsOf(const gfxImage& image) const;

    // TODO: add From suffix
    std::optional<gfxSwapChain> CreateSwapChain(const gfxSwapChainCreateInfo& info);
    std::optional<gfxRenderPass> CreateRenderPass(const gfxRenderPassCreateInfo& info);
    std::optional<gfxPipelineLayout> CreatePipelineLayout(const gfxPipelineLayoutCreateInfo& info);
    std::optional<gfxPipelineGraphics> CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info);
    std::optional<gfxShaderModule> CreateShaderModule(const gfxShaderModuleCreateInfo& info);
    std::optional<gfxFrameBuffer> CreateFrameBuffer(const gfxFrameBufferCreateInfo& info);
    std::optional<gfxImage> CreateImage(const gfxImageCreateInfo& info);
    std::optional<gfxImageView> CreateImageView(const gfxImageViewCreateInfo& info);
    std::optional<gfxSampler> CreateSampler(const gfxSamplerCreateInfo& info);
    std::optional<gfxCommandPool> CreateCommandPool(const gfxCommandPoolCreateInfo& info);
    std::optional<gfxBuffer> CreateBuffer(const gfxBufferCreateInfo& info);
    std::optional<gfxDeviceMemory> CreateDeviceMemory(const gfxDeviceMemoryCreateInfo& info);
    std::optional<gfxDeviceMemoryAllocator> CreateDeviceMemoryAllocator(const gfxDeviceMemoryAllocatorCreateInfo& info);
    std::optional<gfxDescriptorSetLayout> CreateDescriptorSetLayout(const gfxDescriptorSetLayoutCreateInfo& info);
    std::optional<gfxDescriptorPool> CreateDescriptorPool(const gfxDescriptorPoolCreateInfo& info);
    std::optional<gfxSemaphore> CreateSemaphoreFrom(const gfxSemaphoreCreateInfo& info);
    std::optional<gfxFence> CreateFence(const gfxFenceCreateInfo& info);

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
