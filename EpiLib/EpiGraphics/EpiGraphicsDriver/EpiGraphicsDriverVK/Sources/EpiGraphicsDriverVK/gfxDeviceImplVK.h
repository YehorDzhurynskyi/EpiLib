#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

#include "EpiGraphicsDriverVK/gfxPhysicalDeviceImplVK.h"

struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

class gfxDeviceImplVK : public gfxDevice::Impl
{
public:
    gfxDeviceImplVK() = default;
    gfxDeviceImplVK(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK& operator=(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK(gfxDeviceImplVK&& rhs) = default;
    gfxDeviceImplVK& operator=(gfxDeviceImplVK&& rhs) = default;
    ~gfxDeviceImplVK() override;

    epiBool Init(const gfxDeviceCreateInfo& info);

    epiBool IsExtensionEnabled(gfxPhysicalDeviceExtension extension) const override;
    epiBool IsFeatureEnabled(gfxPhysicalDeviceFeature feature) const override;

    epiBool UpdateDescriptorSets(const epiArray<gfxDescriptorSetWrite>& writes, const epiArray<gfxDescriptorSetCopy>& copies) const override;

    std::shared_ptr<gfxSwapChain::Impl> CreateSwapChain(const gfxSwapChainCreateInfo& info) const override;
    std::shared_ptr<internalgfx::gfxRenderPassImpl> CreateRenderPass(const gfxRenderPassCreateInfo& info) const override;
    std::shared_ptr<internalgfx::gfxPipelineLayoutImpl> CreatePipelineLayout(const gfxPipelineLayoutCreateInfo& info) const override;
    std::shared_ptr<internalgfx::gfxPipelineGraphicsImpl> CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info) const override;
    std::shared_ptr<gfxShaderModule::Impl> CreateShaderModule(const gfxShaderModuleCreateInfo& info) const override;
    std::shared_ptr<gfxFrameBuffer::Impl> CreateFrameBuffer(const gfxFrameBufferCreateInfo& info, const internalgfx::gfxRenderPassImpl& renderPassImpl, const epiPtrArray<const internalgfx::gfxTextureViewImpl>& textureViewImpls) const override;
    std::shared_ptr<internalgfx::gfxTextureImpl> CreateTexture(const gfxTextureCreateInfo& info) const override;
    std::shared_ptr<internalgfx::gfxTextureViewImpl> CreateTextureView(const gfxTextureViewCreateInfo& info, const internalgfx::gfxTextureImpl& textureImpl) const override;
    std::shared_ptr<internalgfx::gfxSamplerImpl> CreateSampler(const gfxSamplerCreateInfo& info) const override;
    std::shared_ptr<gfxCommandPool::Impl> CreateCommandPool(const gfxCommandPoolCreateInfo& info) const override;
    std::shared_ptr<gfxBuffer::Impl> CreateBuffer(const gfxBufferCreateInfo& info) const override;
    std::shared_ptr<internalgfx::gfxDeviceMemoryImpl> CreateDeviceMemory(const gfxDeviceMemoryBufferCreateInfo& info) const override;
    std::shared_ptr<internalgfx::gfxDeviceMemoryImpl> CreateDeviceMemory(const gfxDeviceMemoryImageCreateInfo& info) const override;
    std::shared_ptr<internalgfx::gfxDescriptorSetLayoutImpl> CreateDescriptorSetLayout(const gfxDescriptorSetLayoutCreateInfo& info) const override;
    std::shared_ptr<internalgfx::gfxDescriptorPoolImpl> CreateDescriptorPool(const gfxDescriptorPoolCreateInfo& info, const epiPtrArray<const internalgfx::gfxDescriptorSetLayoutImpl>& layoutsImpls) const override;
    std::shared_ptr<gfxSemaphore::Impl> CreateSemaphoreFrom(const gfxSemaphoreCreateInfo& info) const override;
    std::shared_ptr<gfxFence::Impl> CreateFence(const gfxFenceCreateInfo& info) const override;

    VkDevice_T* GetVkDevice() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};

    std::weak_ptr<gfxPhysicalDeviceImplVK> m_PhysicalDevice;
    epiBool m_ExtensionEnabled[static_cast<epiU32>(gfxPhysicalDeviceExtension::COUNT)]{};
    epiBool m_FeatureEnabled[static_cast<epiU32>(gfxPhysicalDeviceFeature::COUNT)]{};
};

EPI_NAMESPACE_END()
