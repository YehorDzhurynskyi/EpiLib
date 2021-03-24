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
    gfxDeviceImplVK() = default;
    gfxDeviceImplVK(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK& operator=(const gfxDeviceImplVK& rhs) = delete;
    gfxDeviceImplVK(gfxDeviceImplVK&& rhs) = default;
    gfxDeviceImplVK& operator=(gfxDeviceImplVK&& rhs) = default;
    ~gfxDeviceImplVK() override;

    epiBool Init(const gfxPhysicalDeviceImplVK& physicalDevice,
                 gfxQueueDescriptorList& queueDescriptorList,
                 gfxPhysicalDeviceExtension extensionMask);

    std::unique_ptr<gfxSwapChainImpl> CreateSwapChain(const gfxSwapChainCreateInfo& info, const gfxSurfaceImpl& surfaceImpl, const gfxRenderPassImpl& renderPassImpl) const override;
    std::unique_ptr<gfxRenderPassImpl> CreateRenderPass(const gfxRenderPassCreateInfo& info) const override;
    std::unique_ptr<gfxPipelineImpl> CreatePipeline(const gfxPipelineCreateInfo& info, const gfxShaderProgramImpl& shaderProgramImpl, const gfxRenderPassImpl& renderPassImpl) const override;
    std::unique_ptr<gfxShaderImpl> CreateShaderFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint = "main") const override;
    std::unique_ptr<gfxShaderProgramImpl> CreateShaderProgram(const gfxShaderProgramCreateInfo& info) const override;
    std::unique_ptr<gfxFrameBufferImpl> CreateFrameBuffer(const gfxFrameBufferCreateInfo& info, const gfxRenderPassImpl& renderPassImpl) const override;
    std::unique_ptr<gfxTextureImpl> CreateTexture(const gfxTextureCreateInfo& info) const override;
    std::unique_ptr<gfxTextureViewImpl> CreateTextureView(const gfxTextureViewCreateInfo& info, const gfxTextureImpl& textureImpl) const override;
    std::unique_ptr<gfxCommandPoolImpl> CreateCommandPool(const gfxCommandPoolCreateInfo& info, const gfxQueueFamilyImpl& queueFamilyImpl) const override;

    VkDevice_T* GetVkDevice() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};

    gfxPhysicalDeviceExtension m_ExtensionMaskEnabled{0};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
