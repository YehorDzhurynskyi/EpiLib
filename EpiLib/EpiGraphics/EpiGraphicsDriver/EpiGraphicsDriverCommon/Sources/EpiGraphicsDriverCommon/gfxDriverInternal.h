#pragma once

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.h"
#include "EpiGraphicsDriverCommon/gfxQueueFamily.h"
#include "EpiGraphicsDriverCommon/gfxWindow.h"
#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.h"
#include "EpiGraphicsDriverCommon/gfxDevice.h"
#include "EpiGraphicsDriverCommon/gfxSurface.h"
#include "EpiGraphicsDriverCommon/gfxQueue.h"
#include "EpiGraphicsDriverCommon/gfxSwapChain.h"
#include "EpiGraphicsDriverCommon/Synchronization/gfxSemaphore.h"

#include "EpiCore/common.h"
#include "EpiCore/types.h"
#include "EpiCore/Containers/Array.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

struct gfxShaderProgramCreateInfoImpl
{
    gfxShaderImpl* Vertex{nullptr};
    gfxShaderImpl* Geometry{nullptr};
    gfxShaderImpl* Fragment{nullptr};
};

class gfxDriverImpl
{
public:
    gfxDriverImpl() = default;
    gfxDriverImpl(const gfxDriverImpl& rhs) = delete;
    gfxDriverImpl& operator=(const gfxDriverImpl& rhs) = delete;
    gfxDriverImpl(gfxDriverImpl&& rhs) = default;
    gfxDriverImpl& operator=(gfxDriverImpl&& rhs) = default;
    virtual ~gfxDriverImpl() = default;

    virtual std::shared_ptr<gfxSurface::Impl> CreateSurface(const gfxWindow& window) const = 0;
    virtual std::shared_ptr<gfxDevice::Impl> CreateDevice(const gfxDeviceCreateInfo& info) const = 0;

    virtual epiBool IsExtensionSupported(gfxDriverExtension extension) const = 0;
    virtual epiBool IsExtensionEnabled(gfxDriverExtension extension) const = 0;

    const epiArray<std::shared_ptr<gfxPhysicalDevice::Impl>>& GetPhysicalDevices() const { return m_PhysicalDevices; }

protected:
    epiArray<std::shared_ptr<gfxPhysicalDevice::Impl>> m_PhysicalDevices;
};

class gfxVertexArrayImpl
{
public:
    gfxVertexArrayImpl() = default;
    gfxVertexArrayImpl(const gfxVertexArrayImpl& rhs) = delete;
    gfxVertexArrayImpl& operator=(const gfxVertexArrayImpl& rhs) = delete;
    gfxVertexArrayImpl(gfxVertexArrayImpl&& rhs) = default;
    gfxVertexArrayImpl& operator=(gfxVertexArrayImpl&& rhs) = default;
    virtual ~gfxVertexArrayImpl() = default;

    virtual void Create() = 0;
    virtual void Destroy() = 0;

    virtual epiBool GetIsCreated() const = 0;
    virtual epiU32 GetID() const = 0;

    virtual void Bind() = 0;
    virtual void UnBind() = 0;
};

class gfxDeviceMemoryImpl
{
public:
    gfxDeviceMemoryImpl() = default;
    gfxDeviceMemoryImpl(const gfxDeviceMemoryImpl& rhs) = delete;
    gfxDeviceMemoryImpl& operator=(const gfxDeviceMemoryImpl& rhs) = delete;
    gfxDeviceMemoryImpl(gfxDeviceMemoryImpl&& rhs) = default;
    gfxDeviceMemoryImpl& operator=(gfxDeviceMemoryImpl&& rhs) = default;
    virtual ~gfxDeviceMemoryImpl() = default;

    virtual epiByte* Map(epiSize_t size, epiSize_t offset) = 0;
    virtual void Unmap() = 0;
};

class gfxDescriptorSetLayoutImpl
{
public:
    static const gfxDescriptorSetLayoutImpl* ExtractImpl(const gfxDescriptorSetLayout& layout) { return layout.m_Impl.Ptr(); }

public:
    gfxDescriptorSetLayoutImpl() = default;
    gfxDescriptorSetLayoutImpl(const gfxDescriptorSetLayoutImpl& rhs) = delete;
    gfxDescriptorSetLayoutImpl& operator=(const gfxDescriptorSetLayoutImpl& rhs) = delete;
    gfxDescriptorSetLayoutImpl(gfxDescriptorSetLayoutImpl&& rhs) = default;
    gfxDescriptorSetLayoutImpl& operator=(gfxDescriptorSetLayoutImpl&& rhs) = default;
    virtual ~gfxDescriptorSetLayoutImpl() = default;
};

class gfxDescriptorSetImpl
{
public:
    static const gfxDescriptorSetImpl* ExtractImpl(const gfxDescriptorSet& set) { return set.m_Impl.Ptr(); }

public:
    gfxDescriptorSetImpl() = default;
    gfxDescriptorSetImpl(const gfxDescriptorSetImpl& rhs) = delete;
    gfxDescriptorSetImpl& operator=(const gfxDescriptorSetImpl& rhs) = delete;
    gfxDescriptorSetImpl(gfxDescriptorSetImpl&& rhs) = default;
    gfxDescriptorSetImpl& operator=(gfxDescriptorSetImpl&& rhs) = default;
    virtual ~gfxDescriptorSetImpl() = default;
};

class gfxDescriptorPoolImpl
{
public:
    gfxDescriptorPoolImpl() = default;
    gfxDescriptorPoolImpl(const gfxDescriptorPoolImpl& rhs) = delete;
    gfxDescriptorPoolImpl& operator=(const gfxDescriptorPoolImpl& rhs) = delete;
    gfxDescriptorPoolImpl(gfxDescriptorPoolImpl&& rhs) = default;
    gfxDescriptorPoolImpl& operator=(gfxDescriptorPoolImpl&& rhs) = default;
    virtual ~gfxDescriptorPoolImpl() = default;

    const epiArray<std::shared_ptr<gfxDescriptorSetImpl>>& GetDescriptorSets() { return m_DescriptorSets; }

protected:
    epiArray<std::shared_ptr<gfxDescriptorSetImpl>> m_DescriptorSets;
};

class gfxTextureImpl
{
public:
    static const gfxTextureImpl* ExtractImpl(const gfxTexture& image) { return image.m_Impl.Ptr(); }

public:
    gfxTextureImpl() = default;
    gfxTextureImpl(const gfxTextureImpl& rhs) = delete;
    gfxTextureImpl& operator=(const gfxTextureImpl& rhs) = delete;
    gfxTextureImpl(gfxTextureImpl&& rhs) = default;
    gfxTextureImpl& operator=(gfxTextureImpl&& rhs) = default;
    virtual ~gfxTextureImpl() = default;
};

class gfxTextureViewImpl
{
public:
    static const gfxTextureViewImpl* ExtractImpl(const gfxTextureView& imageView) { return imageView.m_Impl.Ptr(); }

public:
    gfxTextureViewImpl() = default;
    gfxTextureViewImpl(const gfxTextureViewImpl& rhs) = delete;
    gfxTextureViewImpl& operator=(const gfxTextureViewImpl& rhs) = delete;
    gfxTextureViewImpl(gfxTextureViewImpl&& rhs) = default;
    gfxTextureViewImpl& operator=(gfxTextureViewImpl&& rhs) = default;
    virtual ~gfxTextureViewImpl() = default;
};

class gfxSamplerImpl
{
public:
    static const gfxSamplerImpl* ExtractImpl(const gfxSampler& sampler) { return sampler.m_Impl.Ptr(); }

public:
    gfxSamplerImpl() = default;
    gfxSamplerImpl(const gfxSamplerImpl& rhs) = delete;
    gfxSamplerImpl& operator=(const gfxSamplerImpl& rhs) = delete;
    gfxSamplerImpl(gfxSamplerImpl&& rhs) = default;
    gfxSamplerImpl& operator=(gfxSamplerImpl&& rhs) = default;
    virtual ~gfxSamplerImpl() = default;
};

class gfxShaderImpl
{
public:
    gfxShaderImpl() = default;
    gfxShaderImpl(const gfxShaderImpl& rhs) = delete;
    gfxShaderImpl& operator=(const gfxShaderImpl& rhs) = delete;
    gfxShaderImpl(gfxShaderImpl&& rhs) = default;
    gfxShaderImpl& operator=(gfxShaderImpl&& rhs) = default;
    virtual ~gfxShaderImpl() = default;

    virtual epiBool GetIsCreated() const = 0;
    virtual gfxShaderType GetType() const = 0;
    virtual gfxShaderBackend GetBackend() const = 0;
    virtual epiArray<epiU8> GetCode() const = 0;

    virtual epiBool InitFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint = "main") = 0;
    virtual epiBool InitFromBinary(const epiU8* binary, epiSize_t size, gfxShaderType type, const epiChar* entryPoint = "main") = 0;
};

class gfxShaderProgramImpl
{
public:
    gfxShaderProgramImpl() = default;
    gfxShaderProgramImpl(const gfxShaderProgramImpl& rhs) = delete;
    gfxShaderProgramImpl& operator=(const gfxShaderProgramImpl& rhs) = delete;
    gfxShaderProgramImpl(gfxShaderProgramImpl&& rhs) = default;
    gfxShaderProgramImpl& operator=(gfxShaderProgramImpl&& rhs) = default;
    virtual ~gfxShaderProgramImpl() = default;

    virtual epiBool GetIsCreated() const = 0;

#if 0 // TODO: handle
    virtual void Texture(const epiChar* name, epiU32 value) = 0;

    virtual void UniformFloat(const epiChar* name, epiFloat value) = 0;
    virtual void UniformVec2f(const epiChar* name, const epiVec2f& value) = 0;
    virtual void UniformVec3f(const epiChar* name, const epiVec3f& value) = 0;
    virtual void UniformVec4f(const epiChar* name, const epiVec4f& value) = 0;
    virtual void UniformMat4x4f(const epiChar* name, const epiMat4x4f& value, epiBool transpose) = 0;

    virtual void UniformS32(const epiChar* name, epiS32 value) = 0;
    virtual void UniformVec2s(const epiChar* name, const epiVec2s& value) = 0;
    virtual void UniformVec3s(const epiChar* name, const epiVec3s& value) = 0;
    virtual void UniformVec4s(const epiChar* name, const epiVec4s& value) = 0;

    virtual void UniformU32(const epiChar* name, epiU32 value) = 0;
    virtual void UniformVec2u(const epiChar* name, const epiVec2u& value) = 0;
    virtual void UniformVec3u(const epiChar* name, const epiVec3u& value) = 0;
    virtual void UniformVec4u(const epiChar* name, const epiVec4u& value) = 0;
#endif
};

class gfxPipelineLayoutImpl
{
public:
    static const gfxPipelineLayoutImpl* ExtractImpl(const gfxPipelineLayout& layout) { return layout.m_Impl.Ptr(); }

public:
    gfxPipelineLayoutImpl() = default;
    gfxPipelineLayoutImpl(const gfxPipelineLayoutImpl& rhs) = delete;
    gfxPipelineLayoutImpl& operator=(const gfxPipelineLayoutImpl& rhs) = delete;
    gfxPipelineLayoutImpl(gfxPipelineLayoutImpl&& rhs) = default;
    gfxPipelineLayoutImpl& operator=(gfxPipelineLayoutImpl&& rhs) = default;
    virtual ~gfxPipelineLayoutImpl() = default;
};

class gfxPipelineGraphicsImpl
{
public:
    static const gfxPipelineGraphicsImpl* ExtractImpl(const gfxPipelineGraphics& pipeline) { return pipeline.m_Impl.Ptr(); }

public:
    gfxPipelineGraphicsImpl() = default;
    gfxPipelineGraphicsImpl(const gfxPipelineGraphicsImpl& rhs) = delete;
    gfxPipelineGraphicsImpl& operator=(const gfxPipelineGraphicsImpl& rhs) = delete;
    gfxPipelineGraphicsImpl(gfxPipelineGraphicsImpl&& rhs) = default;
    gfxPipelineGraphicsImpl& operator=(gfxPipelineGraphicsImpl&& rhs) = default;
    virtual ~gfxPipelineGraphicsImpl() = default;

    epiBool IsDynamic(gfxPipelineDynamicState state) const { return m_DynamicStates[static_cast<epiU32>(state)]; }

    const epiArray<gfxPipelineViewport>& GetViewports() const { return m_Viewports; }
    epiArray<gfxPipelineViewport>& GetViewports() { return m_Viewports; }
    const epiArray<epiRect2s>& GetScissors() const { return m_Scissors; }
    epiArray<epiRect2s>& GetScissors() { return m_Scissors; }

protected:
    epiBool m_DynamicStates[static_cast<epiU32>(gfxPipelineDynamicState::COUNT)]{};
    epiArray<gfxPipelineViewport> m_Viewports{};
    epiArray<epiRect2s> m_Scissors{};
};

class gfxRenderPassImpl
{
public:
    static const gfxRenderPassImpl* ExtractImpl(const gfxRenderPass& renderPass) { return renderPass.m_Impl.Ptr(); }

public:
    gfxRenderPassImpl() = default;
    gfxRenderPassImpl(const gfxRenderPassImpl& rhs) = delete;
    gfxRenderPassImpl& operator=(const gfxRenderPassImpl& rhs) = delete;
    gfxRenderPassImpl(gfxRenderPassImpl&& rhs) = default;
    gfxRenderPassImpl& operator=(gfxRenderPassImpl&& rhs) = default;
    virtual ~gfxRenderPassImpl() = default;
};

class gfxAttachmentImpl
{
public:
    gfxAttachmentImpl() = default;
    gfxAttachmentImpl(const gfxAttachmentImpl& rhs) = delete;
    gfxAttachmentImpl& operator=(const gfxAttachmentImpl& rhs) = delete;
    gfxAttachmentImpl(gfxAttachmentImpl&& rhs) = default;
    gfxAttachmentImpl& operator=(gfxAttachmentImpl&& rhs) = default;
    virtual ~gfxAttachmentImpl() = default;
};

} // namespace internalgfx

class gfxSemaphore::Impl
{
public:
    static const gfxSemaphore::Impl* ExtractImpl(const gfxSemaphore& semaphore) { return semaphore.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool Wait(const gfxSemaphoreWaitInfo& info, epiU64 timeout) = 0;
};

class gfxFence::Impl
{
public:
    static const gfxFence::Impl* ExtractImpl(const gfxFence& fence) { return fence.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool Reset() = 0;
    virtual epiBool Wait(epiU64 timeout) = 0;
};

class gfxSurface::Impl
{
public:
    static const gfxSurface::Impl* ExtractImpl(const gfxSurface& surface) { return surface.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamily& queueFamily) const = 0;
    virtual epiBool IsPresentSupportedFor(const gfxPhysicalDevice& device, const gfxQueueFamilyDescriptor& queueFamilyDesc) const = 0;
    virtual gfxSurfaceCapabilities GetCapabilitiesFor(const gfxPhysicalDevice& device) const = 0;
    virtual epiArray<gfxSurfaceFormat> GetSupportedFormatsFor(const gfxPhysicalDevice& device) const = 0;
    virtual epiArray<gfxSurfacePresentMode> GetSupportedPresentModesFor(const gfxPhysicalDevice& device) const = 0;
};

class gfxSwapChain::Impl
{
public:
    static const gfxSwapChain::Impl* ExtractImpl(const gfxSwapChain& swapChain) { return swapChain.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool Recreate(const gfxSwapChainCreateInfo& info) = 0;

    virtual epiS32 AcquireNextImage(const gfxSemaphore* signalSemaphore, const gfxFence* signalFence, epiU64 timeout) = 0;

    epiU32 GetBufferCount() const { return m_ImageViews.Size(); }
    virtual epiSize2u GetExtent() const = 0;

    const epiArray<std::shared_ptr<internalgfx::gfxTextureViewImpl>>& GetImageViews() const { return m_ImageViews; }

protected:
    epiArray<std::shared_ptr<internalgfx::gfxTextureViewImpl>> m_ImageViews;
};

class gfxPhysicalDevice::Impl
{
public:
    static std::shared_ptr<gfxPhysicalDevice::Impl> ExtractImpl(const gfxPhysicalDevice& device) { return device.m_Impl; }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiFloat GetMaxSamplerAnisotropy() const = 0;
    virtual epiString GetName() const = 0;
    virtual gfxPhysicalDeviceType GetType() const = 0;

    virtual gfxFormatProperties FormatPropertiesFor(gfxFormat format) const = 0;

    virtual epiBool IsExtensionSupported(gfxPhysicalDeviceExtension extension) const = 0;
    virtual epiBool IsFeatureSupported(gfxPhysicalDeviceFeature feature) const = 0;
    virtual epiBool IsQueueTypeSupported(gfxQueueType mask) const = 0;

    const epiArray<std::shared_ptr<gfxQueueFamilyDescriptor::Impl>>& GetQueueFamilyDescriptors() const { return m_QueueFamilyDescriptors; }

protected:
    epiArray<std::shared_ptr<gfxQueueFamilyDescriptor::Impl>> m_QueueFamilyDescriptors;
};

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

    virtual std::shared_ptr<gfxSwapChain::Impl> CreateSwapChain(const gfxSwapChainCreateInfo& info) const = 0;
    virtual std::shared_ptr<internalgfx::gfxRenderPassImpl> CreateRenderPass(const gfxRenderPassCreateInfo& info) const = 0;
    virtual std::shared_ptr<internalgfx::gfxPipelineLayoutImpl> CreatePipelineLayout(const gfxPipelineLayoutCreateInfo& info) const = 0;
    virtual std::shared_ptr<internalgfx::gfxPipelineGraphicsImpl> CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info, const internalgfx::gfxShaderProgramImpl& shaderProgramImpl, const internalgfx::gfxRenderPassImpl& renderPassImpl) const = 0;
    virtual std::shared_ptr<internalgfx::gfxShaderImpl> CreateShaderFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint = "main") const = 0;
    virtual std::shared_ptr<internalgfx::gfxShaderImpl> CreateShaderFromBinary(const epiU8* binary, epiSize_t size, gfxShaderType type, const epiChar* entryPoint = "main") const = 0;
    virtual std::shared_ptr<internalgfx::gfxShaderProgramImpl> CreateShaderProgram(const internalgfx::gfxShaderProgramCreateInfoImpl& info) const = 0;
    virtual std::shared_ptr<gfxFrameBuffer::Impl> CreateFrameBuffer(const gfxFrameBufferCreateInfo& info, const internalgfx::gfxRenderPassImpl& renderPassImpl, const epiPtrArray<const internalgfx::gfxTextureViewImpl>& textureViewImpls) const = 0;
    virtual std::shared_ptr<internalgfx::gfxTextureImpl> CreateTexture(const gfxTextureCreateInfo& info) const = 0;
    virtual std::shared_ptr<internalgfx::gfxTextureViewImpl> CreateTextureView(const gfxTextureViewCreateInfo& info, const internalgfx::gfxTextureImpl& textureImpl) const = 0;
    virtual std::shared_ptr<internalgfx::gfxSamplerImpl> CreateSampler(const gfxSamplerCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxCommandPool::Impl> CreateCommandPool(const gfxCommandPoolCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxBuffer::Impl> CreateBuffer(const gfxBufferCreateInfo& info) const = 0;
    virtual std::shared_ptr<internalgfx::gfxDeviceMemoryImpl> CreateDeviceMemory(const gfxDeviceMemoryBufferCreateInfo& info) const = 0;
    virtual std::shared_ptr<internalgfx::gfxDeviceMemoryImpl> CreateDeviceMemory(const gfxDeviceMemoryImageCreateInfo& info) const = 0;
    virtual std::shared_ptr<internalgfx::gfxDescriptorSetLayoutImpl> CreateDescriptorSetLayout(const gfxDescriptorSetLayoutCreateInfo& info) const = 0;
    virtual std::shared_ptr<internalgfx::gfxDescriptorPoolImpl> CreateDescriptorPool(const gfxDescriptorPoolCreateInfo& info, const epiPtrArray<const internalgfx::gfxDescriptorSetLayoutImpl>& layoutsImpls) const = 0;
    virtual std::shared_ptr<gfxSemaphore::Impl> CreateSemaphoreFrom(const gfxSemaphoreCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxFence::Impl> CreateFence(const gfxFenceCreateInfo& info) const = 0;

    const epiArray<std::shared_ptr<gfxQueueFamily::Impl>>& GetQueueFamilies() const { return m_QueueFamilies; }

protected:
    epiArray<std::shared_ptr<gfxQueueFamily::Impl>> m_QueueFamilies;
};

class gfxQueue::Impl
{
public:
    static const gfxQueue::Impl* ExtractImpl(const gfxQueue& queue) { return queue.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool Submit(const epiArray<gfxQueueSubmitInfo>& infos) = 0;
    virtual epiBool Submit(const epiArray<gfxQueueSubmitInfo>& infos, const gfxFence& signalFence) = 0;

    virtual epiBool Present(const gfxQueuePresentInfo& info) = 0;

    virtual epiBool Wait() = 0;

    virtual gfxQueueType GetType() const = 0;
    virtual epiFloat GetPriority() const = 0;
    virtual epiBool IsQueueTypeSupported(gfxQueueType mask) const = 0;
};

class gfxQueueFamilyDescriptor::Impl
{
public:
    static const gfxQueueFamilyDescriptor::Impl* ExtractImpl(const gfxQueueFamilyDescriptor& queueFamilyDescriptor) { return queueFamilyDescriptor.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool IsQueueTypeSupported(gfxQueueType mask) const = 0;
    virtual gfxQueueType GetQueueTypeSupportedMask() const = 0;
    virtual epiU32 GetQueueCount() const = 0;
};

class gfxQueueFamily::Impl
{
public:
    static const gfxQueueFamily::Impl* ExtractImpl(const gfxQueueFamily& queueFamily) { return queueFamily.m_Impl.get(); }

public:
    explicit Impl(const gfxQueueFamilyDescriptor::Impl& queueFamilyDesc)
        : m_QueueTypeMask{queueFamilyDesc.GetQueueTypeSupportedMask()}
    {
    }

    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual void Init(const gfxDevice::Impl& device, const gfxQueueDescriptor& queueDesc) = 0;

    gfxQueueType GetQueueTypeMask() const { return m_QueueTypeMask; }
    epiU32 GetQueueCount() const { return m_Queues.Size(); }

    const epiArray<std::shared_ptr<gfxQueue::Impl>>& GetQueues() const { return m_Queues; }

protected:
    epiArray<std::shared_ptr<gfxQueue::Impl>> m_Queues;
    gfxQueueType m_QueueTypeMask{0};
};

class gfxBuffer::Impl
{
public:
    static const gfxBuffer::Impl* ExtractImpl(const gfxBuffer& buffer) { return buffer.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

class gfxFrameBuffer::Impl
{
public:
    static const gfxFrameBuffer::Impl* ExtractImpl(const gfxFrameBuffer& frameBuffer) { return frameBuffer.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

class gfxCommandPool::Impl
{
public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    const epiArray<std::shared_ptr<gfxCommandBuffer::Impl>>& GetPrimaryCommandBuffers() { return m_PrimaryCommandBuffers; }
    const epiArray<std::shared_ptr<gfxCommandBuffer::Impl>>& GetSecondaryCommandBuffers() { return m_SecondaryCommandBuffers; }

protected:
    epiArray<std::shared_ptr<gfxCommandBuffer::Impl>> m_PrimaryCommandBuffers;
    epiArray<std::shared_ptr<gfxCommandBuffer::Impl>> m_SecondaryCommandBuffers;
};

class gfxCommandBuffer::Impl
{
public:
    static const gfxCommandBuffer::Impl* ExtractImpl(const gfxCommandBuffer& commandBuffer) { return commandBuffer.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiBool GetIsPrimary() const = 0;

    virtual epiBool RecordBegin(gfxCommandBufferUsage usage) = 0;
    virtual epiBool RecordEnd() = 0;

    virtual void RenderPassBegin(const gfxRenderPassBeginInfo& info) = 0;
    virtual void RenderPassEnd() = 0;

    virtual void PipelineBind(const gfxPipelineGraphics& pipeline) = 0;
    virtual void PipelineBarrier(const gfxCommandBufferRecordPipelineBarier& pipelineBarrier) = 0;

    virtual void VertexBuffersBind(const epiArray<gfxBuffer>& buffers, const epiArray<epiU32>& offsets = {}) = 0;
    virtual void IndexBufferBind(const gfxBuffer& buffer, gfxIndexBufferType type, epiU32 offset = 0) = 0;
    virtual void DescriptorSetsBind(gfxPipelineBindPoint bindPoint,
                                    const gfxPipelineLayout& pipelineLayout,
                                    const epiArray<gfxDescriptorSet>& sets,
                                    const epiArray<epiU32>& offsets,
                                    epiU32 firstSet) = 0;

    virtual void Draw(epiU32 vertexCount, epiU32 instanceCount, epiU32 firstVertex, epiU32 firstInstance) = 0;
    virtual void DrawIndexed(epiU32 indexCount, epiU32 instanceCount, epiU32 firstIndex, epiU32 vertexOffset, epiU32 firstInstance) = 0;
    virtual void Copy(const gfxBuffer& src, const gfxBuffer& dst, const epiArray<gfxCommandBufferRecordCopyRegion>& copyRegions) = 0;
    virtual void Copy(const gfxBuffer& src, const gfxTexture& dst, gfxImageLayout dstLayout, const epiArray<gfxCommandBufferRecordCopyBufferToImage>& copyRegions) = 0;
};


EPI_NAMESPACE_END()
