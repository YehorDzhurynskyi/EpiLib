#pragma once

#include "EpiGraphicsImpl/gfxDeviceImpl.h"

#include "EpiGraphicsImplVK/gfxPhysicalDeviceImplVK.h"

struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

class gfxDeviceImplVK : public gfxDevice::Impl
{
public:
    explicit gfxDeviceImplVK(const gfxPhysicalDevice& physicalDevice);
    gfxDeviceImplVK(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK& operator=(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK(gfxDeviceImplVK&& rhs) = default;
    gfxDeviceImplVK& operator=(gfxDeviceImplVK&& rhs) = default;
    ~gfxDeviceImplVK() override;

    epiBool Init(const gfxDeviceCreateInfo& info);

    epiBool IsExtensionEnabled(gfxPhysicalDeviceExtension extension) const override;
    epiBool IsFeatureEnabled(gfxPhysicalDeviceFeature feature) const override;

    epiBool UpdateDescriptorSets(const epiArray<gfxDescriptorSetWrite>& writes, const epiArray<gfxDescriptorSetCopy>& copies) const override;

    std::optional<gfxMemoryRequirements> MemoryRequirementsOf(const gfxBuffer& buffer) const override;
    std::optional<gfxMemoryRequirements> MemoryRequirementsOf(const gfxImage& image) const override;

    std::shared_ptr<gfxSwapChain::Impl> CreateSwapChain(const gfxSwapChainCreateInfo& info) override;
    std::shared_ptr<gfxRenderPass::Impl> CreateRenderPass(const gfxRenderPassCreateInfo& info) override;
    std::shared_ptr<gfxPipelineLayout::Impl> CreatePipelineLayout(const gfxPipelineLayoutCreateInfo& info) override;
    std::shared_ptr<gfxPipelineGraphics::Impl> CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info) override;
    std::shared_ptr<gfxShaderModule::Impl> CreateShaderModule(const gfxShaderModuleCreateInfo& info) override;
    std::shared_ptr<gfxFrameBuffer::Impl> CreateFrameBuffer(const gfxFrameBufferCreateInfo& info) override;
    std::shared_ptr<gfxImage::Impl> CreateImage(const gfxImageCreateInfo& info) override;
    std::shared_ptr<gfxImageView::Impl> CreateImageView(const gfxImageViewCreateInfo& info) override;
    std::shared_ptr<gfxSampler::Impl> CreateSampler(const gfxSamplerCreateInfo& info) override;
    std::shared_ptr<gfxCommandPool::Impl> CreateCommandPool(const gfxCommandPoolCreateInfo& info) override;
    std::shared_ptr<gfxBuffer::Impl> CreateBuffer(const gfxBufferCreateInfo& info) override;
    std::shared_ptr<gfxDeviceMemory::Impl> CreateDeviceMemory(const gfxDeviceMemoryCreateInfo& info) override;
    std::shared_ptr<gfxDeviceMemoryAllocator::Impl> CreateDeviceMemoryAllocator(const gfxDeviceMemoryAllocatorCreateInfo& info) override;
    std::shared_ptr<gfxDescriptorSetLayout::Impl> CreateDescriptorSetLayout(const gfxDescriptorSetLayoutCreateInfo& info) override;
    std::shared_ptr<gfxDescriptorPool::Impl> CreateDescriptorPool(const gfxDescriptorPoolCreateInfo& info) override;
    std::shared_ptr<gfxSemaphore::Impl> CreateSemaphoreFrom(const gfxSemaphoreCreateInfo& info) override;
    std::shared_ptr<gfxFence::Impl> CreateFence(const gfxFenceCreateInfo& info) override;

    VkDevice_T* GetVkDevice() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};

    epiBool m_ExtensionEnabled[static_cast<epiU32>(gfxPhysicalDeviceExtension::COUNT)]{};
    epiBool m_FeatureEnabled[static_cast<epiU32>(gfxPhysicalDeviceFeature::COUNT)]{};
};

EPI_NAMESPACE_END()