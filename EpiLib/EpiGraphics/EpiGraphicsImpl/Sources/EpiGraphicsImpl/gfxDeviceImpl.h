#pragma once

#include "EpiGraphics/gfxDevice.h"

EPI_NAMESPACE_BEGIN()

class gfxDevice::Impl
{
public:
    static std::shared_ptr<gfxDevice::Impl> ExtractImpl(const gfxDevice& device) { return device.m_Impl; }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool IsExtensionEnabled(gfxPhysicalDeviceExtension extension) const = 0;
    virtual epiBool IsFeatureEnabled(gfxPhysicalDeviceFeature feature) const = 0;

    virtual epiBool UpdateDescriptorSets(const epiArray<gfxDescriptorSetWrite>& writes, const epiArray<gfxDescriptorSetCopy>& copies) const = 0;

    virtual std::optional<gfxMemoryRequirements> MemoryRequirementsOf(const gfxBuffer& buffer) const = 0;
    virtual std::optional<gfxMemoryRequirements> MemoryRequirementsOf(const gfxImage& image) const = 0;

    virtual std::shared_ptr<gfxSwapChain::Impl> CreateSwapChain(const gfxSwapChainCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxRenderPass::Impl> CreateRenderPass(const gfxRenderPassCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxPipelineLayout::Impl> CreatePipelineLayout(const gfxPipelineLayoutCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxPipelineGraphics::Impl> CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxShaderModule::Impl> CreateShaderModule(const gfxShaderModuleCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxFrameBuffer::Impl> CreateFrameBuffer(const gfxFrameBufferCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxImage::Impl> CreateImage(const gfxImageCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxImageView::Impl> CreateImageView(const gfxImageViewCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxSampler::Impl> CreateSampler(const gfxSamplerCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxCommandPool::Impl> CreateCommandPool(const gfxCommandPoolCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxBuffer::Impl> CreateBuffer(const gfxBufferCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxDeviceMemory::Impl> CreateDeviceMemory(const gfxDeviceMemoryCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxDescriptorSetLayout::Impl> CreateDescriptorSetLayout(const gfxDescriptorSetLayoutCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxDescriptorPool::Impl> CreateDescriptorPool(const gfxDescriptorPoolCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxSemaphore::Impl> CreateSemaphoreFrom(const gfxSemaphoreCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxFence::Impl> CreateFence(const gfxFenceCreateInfo& info) const = 0;

    const epiArray<std::shared_ptr<gfxQueueFamily::Impl>>& GetQueueFamilies() const { return m_QueueFamilies; }

protected:
    epiArray<std::shared_ptr<gfxQueueFamily::Impl>> m_QueueFamilies;
};

EPI_NAMESPACE_END()
