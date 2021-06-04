#pragma once

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.h"
#include "EpiGraphicsDriverCommon/gfxWindow.h"
#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.h"
#include "EpiGraphicsDriverCommon/gfxSurface.h"
#include "EpiGraphicsDriverCommon/Synchronization/gfxSemaphore.h"

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

    // TODO: implement full interface
    virtual epiBool Submit(const gfxQueueSubmitInfo& info, const epiPtrArray<const gfxCommandBufferImpl>& commandBuffers) = 0;

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

    virtual epiBool RecordBegin(gfxCommandBufferUsage usage) = 0;
    virtual epiBool RecordEnd() = 0;

    virtual void RenderPassBegin(const gfxRenderPassBeginInfo& info, const gfxRenderPassImpl& renderPassImpl, const gfxFrameBufferImpl& frameBufferImpl) = 0;
    virtual void RenderPassEnd() = 0;

    virtual void PipelineBind(const gfxPipelineGraphicsImpl& pipeline) = 0;

    virtual void VertexBuffersBind(const epiPtrArray<const gfxBufferImpl>& buffers, const epiArray<epiU32>& offsets = {}) = 0;
    virtual void IndexBufferBind(const gfxBufferImpl& bufferImpl, gfxIndexBufferType type, epiU32 offset = 0) = 0;
    virtual void DescriptorSetsBind(gfxPipelineBindPoint bindPoint,
                                    const gfxPipelineLayout& pipelineLayout,
                                    const epiArray<gfxDescriptorSet>& sets,
                                    const epiArray<epiU32>& offsets,
                                    epiU32 firstSet) = 0;

    virtual void Draw(epiU32 vertexCount, epiU32 instanceCount, epiU32 firstVertex, epiU32 firstInstance) = 0;
    virtual void DrawIndexed(epiU32 indexCount, epiU32 instanceCount, epiU32 firstIndex, epiU32 vertexOffset, epiU32 firstInstance) = 0;
    virtual void Copy(const gfxBufferImpl& src, const gfxBufferImpl& dst, const epiArray<gfxCommandBufferRecordCopyRegion>& copyRegions) = 0;
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

    virtual epiBool UpdateDescriptorSets(const epiArray<gfxDescriptorSetWrite>& writes, const epiArray<gfxDescriptorSetCopy>& copies) const = 0;

    virtual std::shared_ptr<gfxSwapChainImpl> CreateSwapChain(const gfxSwapChainCreateInfo& info, const gfxSurfaceImpl& surfaceImpl, const gfxQueueFamilyImpl& queueFamilyImpl, const gfxRenderPassImpl& renderPassImpl) const = 0;
    virtual std::shared_ptr<gfxRenderPassImpl> CreateRenderPass(const gfxRenderPassCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxRenderPassImpl> CreateRenderPassFromSchema(const gfxRenderPassSchema& schema) const = 0;
    virtual std::shared_ptr<gfxPipelineLayoutImpl> CreatePipelineLayout(const gfxPipelineLayoutCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxPipelineGraphicsImpl> CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info, const gfxShaderProgramImpl& shaderProgramImpl, const gfxRenderPassImpl& renderPassImpl) const = 0;
    virtual std::shared_ptr<gfxShaderImpl> CreateShaderFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint = "main") const = 0;
    virtual std::shared_ptr<gfxShaderImpl> CreateShaderFromBinary(const epiU8* binary, epiSize_t size, gfxShaderType type, const epiChar* entryPoint = "main") const = 0;
    virtual std::shared_ptr<gfxShaderProgramImpl> CreateShaderProgram(const gfxShaderProgramCreateInfoImpl& info) const = 0;
    virtual std::shared_ptr<gfxFrameBufferImpl> CreateFrameBuffer(const gfxFrameBufferCreateInfo& info, const gfxRenderPassImpl& renderPassImpl, const epiPtrArray<const gfxTextureViewImpl>& textureViewImpls) const = 0;
    virtual std::shared_ptr<gfxTextureImpl> CreateTexture(const gfxTextureCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxTextureViewImpl> CreateTextureView(const gfxTextureViewCreateInfo& info, const gfxTextureImpl& textureImpl) const = 0;
    virtual std::shared_ptr<gfxCommandPoolImpl> CreateCommandPool(const gfxCommandPoolCreateInfo& info, const gfxQueueFamilyImpl& queueFamilyImpl) const = 0;
    virtual std::shared_ptr<gfxBufferImpl> CreateBuffer(const gfxBufferCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxDeviceMemoryImpl> CreateDeviceMemory(const gfxDeviceMemoryCreateInfo& info, const gfxBufferImpl& bufferImpl) const = 0;
    virtual std::shared_ptr<gfxDescriptorSetLayoutImpl> CreateDescriptorSetLayout(const gfxDescriptorSetLayoutCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxDescriptorPoolImpl> CreateDescriptorPool(const gfxDescriptorPoolCreateInfo& info, const epiPtrArray<const gfxDescriptorSetLayoutImpl>& layoutsImpls) const = 0;

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

    virtual epiBool Recreate(const gfxSwapChainCreateInfo& info,
                             const gfxSurfaceImpl& surfaceImpl,
                             const gfxQueueFamilyImpl& queueFamilyImpl,
                             const gfxRenderPassImpl& renderPassImpl) = 0;

    virtual gfxCommandBufferRecord ForBufferRecordCommands(epiU32 bufferIndex, gfxCommandBufferUsage usageMask = gfxCommandBufferUsage{0}) = 0;
    virtual gfxRenderPassBeginInfo ForBufferCreateRenderPassBeginInfo(epiU32 bufferIndex,
                                                                      const gfxRenderPass& renderPass,
                                                                      const epiArray<gfxRenderPassClearValue>& renderPassClearValues) = 0;

    virtual epiBool Present(const gfxQueueImpl& queue, std::function<void(epiU32)> callback) = 0;

    virtual epiU32 GetBufferCount() const = 0;
    virtual epiSize2u GetExtent() const = 0;
};

class gfxFenceImpl
{
public:
    gfxFenceImpl() = default;
    gfxFenceImpl(const gfxFenceImpl& rhs) = delete;
    gfxFenceImpl& operator=(const gfxFenceImpl& rhs) = delete;
    gfxFenceImpl(gfxFenceImpl&& rhs) = default;
    gfxFenceImpl& operator=(gfxFenceImpl&& rhs) = default;
    virtual ~gfxFenceImpl() = default;

    virtual epiBool Reset() = 0;
    virtual epiBool Wait(epiU64 timeout) = 0;
};

class gfxSemaphoreImpl
{
public:
    static const gfxSemaphoreImpl* ExtractImpl(const gfxSemaphore& semaphore) { return semaphore.m_Impl.Ptr(); }

public:
    gfxSemaphoreImpl() = default;
    gfxSemaphoreImpl(const gfxSemaphoreImpl& rhs) = delete;
    gfxSemaphoreImpl& operator=(const gfxSemaphoreImpl& rhs) = delete;
    gfxSemaphoreImpl(gfxSemaphoreImpl&& rhs) = default;
    gfxSemaphoreImpl& operator=(gfxSemaphoreImpl&& rhs) = default;
    virtual ~gfxSemaphoreImpl() = default;

    virtual epiBool Wait(const gfxSemaphoreWaitInfo& info, epiU64 timeout) = 0;
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

class gfxBufferImpl
{
public:
    static const gfxBufferImpl* ExtractImpl(const gfxBuffer& buffer) { return buffer.m_Impl.Ptr(); }

public:
    gfxBufferImpl() = default;
    gfxBufferImpl(const gfxBufferImpl& rhs) = delete;
    gfxBufferImpl& operator=(const gfxBufferImpl& rhs) = delete;
    gfxBufferImpl(gfxBufferImpl&& rhs) = default;
    gfxBufferImpl& operator=(gfxBufferImpl&& rhs) = default;
    virtual ~gfxBufferImpl() = default;
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

EPI_NAMESPACE_END()
