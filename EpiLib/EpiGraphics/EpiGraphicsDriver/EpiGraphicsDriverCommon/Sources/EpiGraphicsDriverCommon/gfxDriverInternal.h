#pragma once

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.h"
#include "EpiGraphicsDriverCommon/gfxWindow.h"
#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.h"
#include "EpiGraphicsDriverCommon/gfxSurface.h"

#include "EpiCore/common.h"
#include "EpiCore/types.h"
#include "EpiCore/Containers/Array.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxQueueImpl
{
public:
    gfxQueueImpl() = default;
    gfxQueueImpl(const gfxQueueImpl& rhs) = delete;
    gfxQueueImpl& operator=(const gfxQueueImpl& rhs) = delete;
    gfxQueueImpl(gfxQueueImpl&& rhs) = default;
    gfxQueueImpl& operator=(gfxQueueImpl&& rhs) = default;
    virtual ~gfxQueueImpl() = default;

    virtual gfxQueueType GetType() const = 0;
    virtual epiFloat GetPriority() const = 0;
    virtual epiBool IsQueueTypeSupported(gfxQueueType mask) const = 0;
};

class gfxQueueFamilyDescriptorImpl
{
public:
    gfxQueueFamilyDescriptorImpl() = default;
    gfxQueueFamilyDescriptorImpl(const gfxQueueFamilyDescriptorImpl& rhs) = delete;
    gfxQueueFamilyDescriptorImpl& operator=(const gfxQueueFamilyDescriptorImpl& rhs) = delete;
    gfxQueueFamilyDescriptorImpl(gfxQueueFamilyDescriptorImpl&& rhs) = default;
    gfxQueueFamilyDescriptorImpl& operator=(gfxQueueFamilyDescriptorImpl&& rhs) = default;
    virtual ~gfxQueueFamilyDescriptorImpl() = default;

    virtual epiBool IsQueueTypeSupported(gfxQueueType mask) const = 0;
    virtual gfxQueueType GetQueueTypeSupportedMask() const = 0;
    virtual epiU32 GetQueueCount() const = 0;
};

class gfxQueueFamilyImpl
{
public:
    explicit gfxQueueFamilyImpl(const gfxQueueFamilyDescriptorImpl& queueFamilyDesc)
        : m_QueueTypeMask{queueFamilyDesc.GetQueueTypeSupportedMask()}
    {
    }

    gfxQueueFamilyImpl(const gfxQueueFamilyImpl& rhs) = delete;
    gfxQueueFamilyImpl& operator=(const gfxQueueFamilyImpl& rhs) = delete;
    gfxQueueFamilyImpl(gfxQueueFamilyImpl&& rhs) = default;
    gfxQueueFamilyImpl& operator=(gfxQueueFamilyImpl&& rhs) = default;
    virtual ~gfxQueueFamilyImpl() = default;

    virtual void Init(const gfxDeviceImpl& device, const gfxQueueDescriptor& queueDesc) = 0;

    gfxQueueType GetQueueTypeMask() const { return m_QueueTypeMask; }
    epiU32 GetQueueCount() const { return m_Queues.Size(); }

    const epiArray<std::shared_ptr<gfxQueueImpl>>& GetQueues() const { return m_Queues; }

protected:
    epiArray<std::shared_ptr<gfxQueueImpl>> m_Queues;
    gfxQueueType m_QueueTypeMask{0};
};

class gfxFrameBufferImpl
{
public:
    gfxFrameBufferImpl() = default;
    gfxFrameBufferImpl(const gfxFrameBufferImpl& rhs) = delete;
    gfxFrameBufferImpl& operator=(const gfxFrameBufferImpl& rhs) = delete;
    gfxFrameBufferImpl(gfxFrameBufferImpl&& rhs) = default;
    gfxFrameBufferImpl& operator=(gfxFrameBufferImpl&& rhs) = default;
    virtual ~gfxFrameBufferImpl() = default;
};

class gfxCommandPoolImpl
{
public:
    gfxCommandPoolImpl() = default;
    gfxCommandPoolImpl(const gfxCommandPoolImpl& rhs) = delete;
    gfxCommandPoolImpl& operator=(const gfxCommandPoolImpl& rhs) = delete;
    gfxCommandPoolImpl(gfxCommandPoolImpl&& rhs) = default;
    gfxCommandPoolImpl& operator=(gfxCommandPoolImpl&& rhs) = default;
    virtual ~gfxCommandPoolImpl() = default;

    const epiArray<std::shared_ptr<gfxCommandBufferImpl>>& GetPrimaryCommandBuffers() { return m_PrimaryCommandBuffers; }
    const epiArray<std::shared_ptr<gfxCommandBufferImpl>>& GetSecondaryCommandBuffers() { return m_SecondaryCommandBuffers; }

protected:
    epiArray<std::shared_ptr<gfxCommandBufferImpl>> m_PrimaryCommandBuffers;
    epiArray<std::shared_ptr<gfxCommandBufferImpl>> m_SecondaryCommandBuffers;
};

class gfxCommandBufferImpl
{
public:
    gfxCommandBufferImpl() = default;
    gfxCommandBufferImpl(const gfxCommandBufferImpl& rhs) = delete;
    gfxCommandBufferImpl& operator=(const gfxCommandBufferImpl& rhs) = delete;
    gfxCommandBufferImpl(gfxCommandBufferImpl&& rhs) = default;
    gfxCommandBufferImpl& operator=(gfxCommandBufferImpl&& rhs) = default;
    virtual ~gfxCommandBufferImpl() = default;

    virtual epiBool GetIsPrimary() const = 0;

    virtual epiBool RenderPassBegin(const gfxRenderPassBeginInfo& info, const gfxRenderPassImpl& renderPassImpl, const gfxFrameBufferImpl& frameBufferImpl) const = 0;
    virtual epiBool RenderPassEnd() const = 0;
};

struct gfxShaderProgramCreateInfoImpl
{
    gfxShaderImpl* Vertex{nullptr};
    gfxShaderImpl* Geometry{nullptr};
    gfxShaderImpl* Fragment{nullptr};
};

class gfxDeviceImpl
{
public:
    gfxDeviceImpl() = default;
    gfxDeviceImpl(const gfxDeviceImpl& rhs) = delete;
    gfxDeviceImpl& operator=(const gfxDeviceImpl& rhs) = delete;
    gfxDeviceImpl(gfxDeviceImpl&& rhs) = default;
    gfxDeviceImpl& operator=(gfxDeviceImpl&& rhs) = default;
    virtual ~gfxDeviceImpl() = default;

    virtual epiBool IsExtensionEnabled(gfxPhysicalDeviceExtension extension) const = 0;
    virtual epiBool IsFeatureEnabled(gfxPhysicalDeviceFeature feature) const = 0;

    virtual std::shared_ptr<gfxSwapChainImpl> CreateSwapChain(const gfxSwapChainCreateInfo& info, const gfxSurfaceImpl& surfaceImpl, const gfxQueueFamilyImpl& queueFamilyImpl, const gfxRenderPassImpl& renderPassImpl) const = 0;
    virtual std::shared_ptr<gfxRenderPassImpl> CreateRenderPass(const gfxRenderPassCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxRenderPassImpl> CreateRenderPassFromSchema(const gfxRenderPassSchema& schema) const = 0;
    virtual std::shared_ptr<gfxPipelineGraphicsImpl> CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info, const gfxShaderProgramImpl& shaderProgramImpl, const gfxRenderPassImpl& renderPassImpl) const = 0;
    virtual std::shared_ptr<gfxShaderImpl> CreateShaderFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint = "main") const = 0;
    virtual std::shared_ptr<gfxShaderImpl> CreateShaderFromBinary(const epiU8* binary, epiSize_t size, gfxShaderType type, const epiChar* entryPoint = "main") const = 0;
    virtual std::shared_ptr<gfxShaderProgramImpl> CreateShaderProgram(const gfxShaderProgramCreateInfoImpl& info) const = 0;
    virtual std::shared_ptr<gfxFrameBufferImpl> CreateFrameBuffer(const gfxFrameBufferCreateInfo& info, const gfxRenderPassImpl& renderPassImpl, const epiPtrArray<const gfxTextureViewImpl>& textureViewImpls) const = 0;
    virtual std::shared_ptr<gfxTextureImpl> CreateTexture(const gfxTextureCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxTextureViewImpl> CreateTextureView(const gfxTextureViewCreateInfo& info, const gfxTextureImpl& textureImpl) const = 0;
    virtual std::shared_ptr<gfxCommandPoolImpl> CreateCommandPool(const gfxCommandPoolCreateInfo& info, const gfxQueueFamilyImpl& queueFamilyImpl) const = 0;

    const epiArray<std::shared_ptr<gfxQueueFamilyImpl>>& GetQueueFamilies() const { return m_QueueFamilies; }

protected:
    epiArray<std::shared_ptr<gfxQueueFamilyImpl>> m_QueueFamilies;
};

class gfxPhysicalDeviceImpl
{
public:
    gfxPhysicalDeviceImpl() = default;
    gfxPhysicalDeviceImpl(const gfxPhysicalDeviceImpl& rhs) = delete;
    gfxPhysicalDeviceImpl& operator=(const gfxPhysicalDeviceImpl& rhs) = delete;
    gfxPhysicalDeviceImpl(gfxPhysicalDeviceImpl&& rhs) = default;
    gfxPhysicalDeviceImpl& operator=(gfxPhysicalDeviceImpl&& rhs) = default;
    virtual ~gfxPhysicalDeviceImpl() = default;

    virtual epiString GetName() const = 0;
    virtual gfxPhysicalDeviceType GetType() const = 0;

    virtual std::unique_ptr<gfxDeviceImpl> CreateDevice(gfxQueueDescriptorList& queueDescriptorList,
                                                        const epiArray<gfxPhysicalDeviceExtension>& extensionsRequired,
                                                        const epiArray<gfxPhysicalDeviceFeature>& featuresRequired) const = 0;

    virtual epiBool IsExtensionSupported(gfxPhysicalDeviceExtension extension) const = 0;
    virtual epiBool IsFeatureSupported(gfxPhysicalDeviceFeature feature) const = 0;
    virtual epiBool IsQueueTypeSupported(gfxQueueType mask) const = 0;
};

class gfxSurfaceImpl
{
public:
    gfxSurfaceImpl() = default;
    gfxSurfaceImpl(const gfxSurfaceImpl& rhs) = delete;
    gfxSurfaceImpl& operator=(const gfxSurfaceImpl& rhs) = delete;
    gfxSurfaceImpl(gfxSurfaceImpl&& rhs) = default;
    gfxSurfaceImpl& operator=(gfxSurfaceImpl&& rhs) = default;
    virtual ~gfxSurfaceImpl() = default;

    virtual epiBool IsPresentSupportedFor(const gfxPhysicalDeviceImpl& device) const = 0;
    virtual epiBool IsPresentSupportedFor(const gfxPhysicalDeviceImpl& device, const gfxQueueFamilyImpl& queueFamily) const = 0;
    virtual epiBool IsPresentSupportedFor(const gfxPhysicalDeviceImpl& device, const gfxQueueFamilyDescriptorImpl& queueFamilyDesc) const = 0;
    virtual gfxSurfaceCapabilities GetCapabilitiesFor(const gfxPhysicalDeviceImpl& device) const = 0;
    virtual epiArray<gfxSurfaceFormat> GetSupportedFormatsFor(const gfxPhysicalDeviceImpl& device) const = 0;
    virtual epiArray<gfxSurfacePresentMode> GetSupportedPresentModesFor(const gfxPhysicalDeviceImpl& device) const = 0;
};

class gfxSwapChainImpl
{
public:
    gfxSwapChainImpl() = default;
    gfxSwapChainImpl(const gfxSwapChainImpl& rhs) = delete;
    gfxSwapChainImpl& operator=(const gfxSwapChainImpl& rhs) = delete;
    gfxSwapChainImpl(gfxSwapChainImpl&& rhs) = default;
    gfxSwapChainImpl& operator=(gfxSwapChainImpl&& rhs) = default;
    virtual ~gfxSwapChainImpl() = default;

    virtual epiBool AssignRenderPass(const gfxRenderPassImpl& renderPass, const gfxPipelineGraphicsImpl& pipeline) = 0;

    virtual epiBool Present(const gfxQueueImpl& queue) = 0;

    virtual epiSize2u GetExtent() const = 0;
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

    virtual std::shared_ptr<gfxSurfaceImpl> CreateSurface(const gfxWindow& window) = 0;

    virtual epiBool IsExtensionSupported(gfxDriverExtension extension) const = 0;
    virtual epiBool IsExtensionEnabled(gfxDriverExtension extension) const = 0;

    const epiArray<std::shared_ptr<gfxPhysicalDeviceImpl>>& GetPhysicalDevices() const { return m_PhysicalDevices; }

protected:
    epiArray<std::shared_ptr<gfxPhysicalDeviceImpl>> m_PhysicalDevices;
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

class gfxVertexBufferLayoutAttributeImpl
{
public:
    gfxVertexBufferLayoutAttributeImpl() = default;
    gfxVertexBufferLayoutAttributeImpl(const gfxVertexBufferLayoutAttributeImpl& rhs) = delete;
    gfxVertexBufferLayoutAttributeImpl& operator=(const gfxVertexBufferLayoutAttributeImpl& rhs) = delete;
    gfxVertexBufferLayoutAttributeImpl(gfxVertexBufferLayoutAttributeImpl&& rhs) = default;
    gfxVertexBufferLayoutAttributeImpl& operator=(gfxVertexBufferLayoutAttributeImpl&& rhs) = default;
    virtual ~gfxVertexBufferLayoutAttributeImpl() = default;

    virtual epiU32 GetLocation() const = 0;
    virtual void SetLocation(epiU32 value) = 0;
    virtual epiSize_t GetOffset() const = 0;
    virtual void SetOffset(epiSize_t value) = 0;
    virtual gfxFormat GetFormat() const = 0;
    virtual void SetFormat(gfxFormat value) = 0;

    virtual void Apply() const = 0;
};

class gfxVertexBufferLayoutImpl
{
public:
    gfxVertexBufferLayoutImpl() = default;
    gfxVertexBufferLayoutImpl(const gfxVertexBufferLayoutImpl& rhs) = delete;
    gfxVertexBufferLayoutImpl& operator=(const gfxVertexBufferLayoutImpl& rhs) = delete;
    gfxVertexBufferLayoutImpl(gfxVertexBufferLayoutImpl&& rhs) = default;
    gfxVertexBufferLayoutImpl& operator=(gfxVertexBufferLayoutImpl&& rhs) = default;
    virtual ~gfxVertexBufferLayoutImpl() = default;

    virtual epiU32 GetStride() const = 0;
    virtual void SetStride(epiU32 value) = 0;

    virtual void Apply() const = 0;

    virtual void Add(gfxVertexBufferLayoutAttributeImpl&& attr) = 0;
};

class gfxVertexBufferImpl
{
public:
    gfxVertexBufferImpl() = default;
    gfxVertexBufferImpl(const gfxVertexBufferImpl& rhs) = delete;
    gfxVertexBufferImpl& operator=(const gfxVertexBufferImpl& rhs) = delete;
    gfxVertexBufferImpl(gfxVertexBufferImpl&& rhs) = default;
    gfxVertexBufferImpl& operator=(gfxVertexBufferImpl&& rhs) = default;
    virtual ~gfxVertexBufferImpl() = default;
};

class gfxTextureImpl
{
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
    gfxTextureViewImpl() = default;
    gfxTextureViewImpl(const gfxTextureViewImpl& rhs) = delete;
    gfxTextureViewImpl& operator=(const gfxTextureViewImpl& rhs) = delete;
    gfxTextureViewImpl(gfxTextureViewImpl&& rhs) = default;
    gfxTextureViewImpl& operator=(gfxTextureViewImpl&& rhs) = default;
    virtual ~gfxTextureViewImpl() = default;
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

class gfxPipelineGraphicsImpl
{
public:
    gfxPipelineGraphicsImpl() = default;
    gfxPipelineGraphicsImpl(const gfxPipelineGraphicsImpl& rhs) = delete;
    gfxPipelineGraphicsImpl& operator=(const gfxPipelineGraphicsImpl& rhs) = delete;
    gfxPipelineGraphicsImpl(gfxPipelineGraphicsImpl&& rhs) = default;
    gfxPipelineGraphicsImpl& operator=(gfxPipelineGraphicsImpl&& rhs) = default;
    virtual ~gfxPipelineGraphicsImpl() = default;
};

class gfxRenderPassImpl
{
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

EPI_NAMESPACE_END()
