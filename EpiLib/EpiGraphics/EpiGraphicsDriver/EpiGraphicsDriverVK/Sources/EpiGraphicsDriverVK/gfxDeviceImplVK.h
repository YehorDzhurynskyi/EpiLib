#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

#include "EpiGraphicsDriverVK/gfxQueueImplVK.h"

struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxPhysicalDeviceImplVK;
class gfxDeviceImplVK : public gfxDeviceImpl
{
public:
    explicit gfxDeviceImplVK(const gfxPhysicalDeviceImplVK& physicalDevice);
    gfxDeviceImplVK(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK& operator=(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK(gfxDeviceImplVK&& rhs) = default;
    gfxDeviceImplVK& operator=(gfxDeviceImplVK&& rhs) = default;
    ~gfxDeviceImplVK() override;

    epiBool Init(gfxQueueDescriptorList& queueDescriptorList,
                 const epiArray<gfxPhysicalDeviceExtension>& extensionsRequired,
                 const epiArray<gfxPhysicalDeviceFeature>& featuresRequired);

    epiBool IsExtensionEnabled(gfxPhysicalDeviceExtension extension) const override;
    epiBool IsFeatureEnabled(gfxPhysicalDeviceFeature feature) const override;

    epiBool UpdateDescriptorSets(const epiArray<gfxDescriptorSetWrite>& writes, const epiArray<gfxDescriptorSetCopy>& copies) const override;

    std::shared_ptr<gfxSwapChainImpl> CreateSwapChain(const gfxSwapChainCreateInfo& info, const gfxSurfaceImpl& surfaceImpl, const gfxQueueFamilyImpl& queueFamilyImpl, const gfxRenderPassImpl& renderPassImpl) const override;
    std::shared_ptr<gfxRenderPassImpl> CreateRenderPass(const gfxRenderPassCreateInfo& info) const override;
    std::shared_ptr<gfxRenderPassImpl> CreateRenderPassFromSchema(const gfxRenderPassSchema& schema) const override;
    std::shared_ptr<gfxPipelineLayoutImpl> CreatePipelineLayout(const gfxPipelineLayoutCreateInfo& info) const override;
    std::shared_ptr<gfxPipelineGraphicsImpl> CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info, const gfxShaderProgramImpl& shaderProgramImpl, const gfxRenderPassImpl& renderPassImpl) const override;
    std::shared_ptr<gfxShaderImpl> CreateShaderFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint = "main") const override;
    std::shared_ptr<gfxShaderImpl> CreateShaderFromBinary(const epiU8* binary, epiSize_t size, gfxShaderType type, const epiChar* entryPoint = "main") const override;
    std::shared_ptr<gfxShaderProgramImpl> CreateShaderProgram(const gfxShaderProgramCreateInfoImpl& info) const override;
    std::shared_ptr<gfxFrameBufferImpl> CreateFrameBuffer(const gfxFrameBufferCreateInfo& info, const gfxRenderPassImpl& renderPassImpl, const epiPtrArray<const gfxTextureViewImpl>& textureViewImpls) const override;
    std::shared_ptr<gfxTextureImpl> CreateTexture(const gfxTextureCreateInfo& info) const override;
    std::shared_ptr<gfxTextureViewImpl> CreateTextureView(const gfxTextureViewCreateInfo& info, const gfxTextureImpl& textureImpl) const override;
    std::shared_ptr<gfxCommandPoolImpl> CreateCommandPool(const gfxCommandPoolCreateInfo& info, const gfxQueueFamilyImpl& queueFamilyImpl) const override;
    std::shared_ptr<gfxBufferImpl> CreateBuffer(const gfxBufferCreateInfo& info) const override;
    std::shared_ptr<gfxDeviceMemoryImpl> CreateDeviceMemory(const gfxDeviceMemoryBufferCreateInfo& info, const gfxBufferImpl& bufferImpl) const override;
    std::shared_ptr<gfxDeviceMemoryImpl> CreateDeviceMemory(const gfxDeviceMemoryImageCreateInfo& info) const override;
    std::shared_ptr<gfxDescriptorSetLayoutImpl> CreateDescriptorSetLayout(const gfxDescriptorSetLayoutCreateInfo& info) const override;
    std::shared_ptr<gfxDescriptorPoolImpl> CreateDescriptorPool(const gfxDescriptorPoolCreateInfo& info, const epiPtrArray<const gfxDescriptorSetLayoutImpl>& layoutsImpls) const override;
    std::shared_ptr<gfxSemaphoreImpl> CreateSemaphoreFrom(const gfxSemaphoreCreateInfo& info) const override;
    std::shared_ptr<gfxFenceImpl> CreateFence(const gfxFenceCreateInfo& info) const override;

    VkDevice_T* GetVkDevice() const;

protected:
    const gfxPhysicalDeviceImplVK& m_PhysicalDevice;
    VkDevice_T* m_VkDevice{nullptr};

    epiBool m_ExtensionEnabled[static_cast<epiU32>(gfxPhysicalDeviceExtension::COUNT)]{};
    epiBool m_FeatureEnabled[static_cast<epiU32>(gfxPhysicalDeviceFeature::COUNT)]{};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
