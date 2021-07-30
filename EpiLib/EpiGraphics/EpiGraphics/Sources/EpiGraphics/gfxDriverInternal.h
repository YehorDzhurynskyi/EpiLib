#pragma once

#include "EpiGraphics/gfxEnum.h"
#include "EpiGraphics/gfxInstance.h"
#include "EpiGraphics/gfxQueueDescriptor.h"
#include "EpiGraphics/gfxQueueFamily.h"
#include "EpiGraphics/gfxWindow.h"
#include "EpiGraphics/gfxPhysicalDevice.h"
#include "EpiGraphics/gfxDevice.h"
#include "EpiGraphics/gfxSurface.h"
#include "EpiGraphics/gfxCommandPool.h"
#include "EpiGraphics/gfxDescriptorPool.h"
#include "EpiGraphics/gfxQueue.h"
#include "EpiGraphics/gfxSwapChain.h"
#include "EpiGraphics/Synchronization/gfxSemaphore.h"

#include "EpiCore/common.h"
#include "EpiCore/types.h"
#include "EpiCore/Containers/Array.h"

EPI_NAMESPACE_BEGIN()

class gfxInstance::Impl
{
public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual std::shared_ptr<gfxSurface::Impl> CreateSurface(const gfxWindow& window) const = 0;
    virtual std::shared_ptr<gfxDevice::Impl> CreateDevice(const gfxDeviceCreateInfo& info) const = 0;

    virtual epiBool IsExtensionSupported(gfxInstanceExtension extension) const = 0;
    virtual epiBool IsExtensionEnabled(gfxInstanceExtension extension) const = 0;

    const epiArray<std::shared_ptr<gfxPhysicalDevice::Impl>>& GetPhysicalDevices() const { return m_PhysicalDevices; }

protected:
    epiArray<std::shared_ptr<gfxPhysicalDevice::Impl>> m_PhysicalDevices;
};

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

    const epiArray<std::shared_ptr<gfxImageView::Impl>>& GetImageViews() const { return m_ImageViews; }

protected:
    epiArray<std::shared_ptr<gfxImageView::Impl>> m_ImageViews;
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
    virtual std::shared_ptr<gfxDeviceMemory::Impl> CreateDeviceMemory(const gfxDeviceMemoryBufferCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxDeviceMemory::Impl> CreateDeviceMemory(const gfxDeviceMemoryImageCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxDescriptorSetLayout::Impl> CreateDescriptorSetLayout(const gfxDescriptorSetLayoutCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxDescriptorPool::Impl> CreateDescriptorPool(const gfxDescriptorPoolCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxSemaphore::Impl> CreateSemaphoreFrom(const gfxSemaphoreCreateInfo& info) const = 0;
    virtual std::shared_ptr<gfxFence::Impl> CreateFence(const gfxFenceCreateInfo& info) const = 0;

    const epiArray<std::shared_ptr<gfxQueueFamily::Impl>>& GetQueueFamilies() const { return m_QueueFamilies; }

protected:
    epiArray<std::shared_ptr<gfxQueueFamily::Impl>> m_QueueFamilies;
};

class gfxDeviceMemory::Impl
{
public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual epiByte* Map(epiSize_t size, epiSize_t offset) = 0;
    virtual void Unmap() = 0;
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

class gfxImage::Impl
{
public:
    static const gfxImage::Impl* ExtractImpl(const gfxImage& image) { return image.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

class gfxImageView::Impl
{
public:
    static const gfxImageView::Impl* ExtractImpl(const gfxImageView& imageView) { return imageView.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

class gfxSampler::Impl
{
public:
    static const gfxSampler::Impl* ExtractImpl(const gfxSampler& sampler) { return sampler.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

class gfxShaderModule::Impl
{
public:
    static const gfxShaderModule::Impl* ExtractImpl(const gfxShaderModule& shaderModule) { return shaderModule.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual gfxShaderStage GetStage() const = 0;
    virtual const epiArray<epiU8>& GetCode() const = 0;
    virtual gfxShaderModuleFrontend GetFrontend() const = 0;
    virtual const epiString& GetEntryPoint() const = 0;
};

class gfxDescriptorSetLayout::Impl
{
public:
    static const gfxDescriptorSetLayout::Impl* ExtractImpl(const gfxDescriptorSetLayout& layout) { return layout.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

class gfxDescriptorSet::Impl
{
public:
    static const gfxDescriptorSet::Impl* ExtractImpl(const gfxDescriptorSet& set) { return set.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

class gfxDescriptorPool::Impl
{
public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    const epiArray<std::shared_ptr<gfxDescriptorSet::Impl>>& GetDescriptorSets() { return m_DescriptorSets; }

protected:
    epiArray<std::shared_ptr<gfxDescriptorSet::Impl>> m_DescriptorSets;
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

class gfxPipelineLayout::Impl
{
public:
    static const gfxPipelineLayout::Impl* ExtractImpl(const gfxPipelineLayout& layout) { return layout.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;
};

class gfxPipelineGraphics::Impl
{
public:
    static const gfxPipelineGraphics::Impl* ExtractImpl(const gfxPipelineGraphics& pipeline) { return pipeline.m_Impl.get(); }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

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

class gfxRenderPass::Impl
{
public:
    static const gfxRenderPass::Impl* ExtractImpl(const gfxRenderPass& renderPass) { return renderPass.m_Impl.get(); }

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
    virtual void Copy(const gfxBuffer& src, const gfxImage& dst, gfxImageLayout dstLayout, const epiArray<gfxCommandBufferRecordCopyBufferToImage>& copyRegions) = 0;
};

EPI_NAMESPACE_END()
