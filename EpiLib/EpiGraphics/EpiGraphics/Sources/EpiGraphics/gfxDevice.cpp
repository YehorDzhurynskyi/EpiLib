EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxDevice.h"
#include "EpiGraphics/gfxDevice.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsImpl/gfxDeviceImpl.h"

EPI_NAMESPACE_BEGIN()

gfxDevice::gfxDevice(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
    epiArray<gfxQueueFamily>& queueFamilies = GetQueueFamilies();
    queueFamilies.Reserve(m_Impl->GetQueueFamilies().Size());

    // NOTE: filling gfxQueueFamily with their implementations (gfxDeviceImpl still owns these implementations)
    std::transform(m_Impl->GetQueueFamilies().begin(),
                   m_Impl->GetQueueFamilies().end(),
                   std::back_inserter(queueFamilies),
                   [](const std::shared_ptr<gfxQueueFamily::Impl>& queueFamilyImpl)
    {
        return gfxQueueFamily(queueFamilyImpl);
    });
}

epiBool gfxDevice::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

epiBool gfxDevice::IsExtensionEnabled(gfxPhysicalDeviceExtension extension) const
{
    return m_Impl->IsExtensionEnabled(extension);
}

epiBool gfxDevice::IsFeatureEnabled(gfxPhysicalDeviceFeature feature) const
{
    return m_Impl->IsFeatureEnabled(feature);
}

epiBool gfxDevice::UpdateDescriptorSets(const epiArray<gfxDescriptorSetWrite>& writes, const epiArray<gfxDescriptorSetCopy>& copies) const
{
    return m_Impl->UpdateDescriptorSets(writes, copies);
}

std::optional<gfxMemoryRequirements> gfxDevice::MemoryRequirementsOf(const gfxBuffer& buffer) const
{
    if (!HasImpl())
    {
        epiLogError("Failed to get Buffer MemoryRequirements! Calling object has no implementation!");
        return std::nullopt;
    }

    if (!buffer.HasImpl())
    {
        epiLogError("Failed to get Buffer MemoryRequirements! The provided Buffer has no implementation!");
        return std::nullopt;
    }

    return m_Impl->MemoryRequirementsOf(buffer);
}

std::optional<gfxMemoryRequirements> gfxDevice::MemoryRequirementsOf(const gfxImage& image) const
{
    if (!HasImpl())
    {
        epiLogError("Failed to get Image MemoryRequirements! Calling object has no implementation!");
        return std::nullopt;
    }

    if (!image.HasImpl())
    {
        epiLogError("Failed to get Image MemoryRequirements! The provided Image has no implementation!");
        return std::nullopt;
    }

    return m_Impl->MemoryRequirementsOf(image);
}

std::optional<gfxSwapChain> gfxDevice::CreateSwapChain(const gfxSwapChainCreateInfo& info)
{
    std::optional<gfxSwapChain> swapChain;

    if (std::shared_ptr<gfxSwapChain::Impl> impl = m_Impl->CreateSwapChain(info))
    {
        swapChain = gfxSwapChain(std::move(impl));
    }

    return swapChain;
}

std::optional<gfxRenderPass> gfxDevice::CreateRenderPass(const gfxRenderPassCreateInfo& info)
{
    std::optional<gfxRenderPass> renderPass;

    if (std::shared_ptr<gfxRenderPass::Impl> impl = m_Impl->CreateRenderPass(info))
    {
        renderPass = gfxRenderPass(std::move(impl));
    }

    return renderPass;
}

std::optional<gfxPipelineLayout> gfxDevice::CreatePipelineLayout(const gfxPipelineLayoutCreateInfo& info)
{
    std::optional<gfxPipelineLayout> pipelineLayout;

    if (std::shared_ptr<gfxPipelineLayout::Impl> impl = m_Impl->CreatePipelineLayout(info))
    {
        pipelineLayout = gfxPipelineLayout(std::move(impl));
    }

    return pipelineLayout;
}

std::optional<gfxPipelineGraphics> gfxDevice::CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info)
{
    std::optional<gfxPipelineGraphics> pipeline;

    if (!info.GetRenderPass().HasImpl())
    {
        epiLogError("Failed to create Pipeline! The provided RenderPass has no implemetation!");
        return pipeline;
    }

    const epiArray<gfxPipelineViewport>& viewports = info.GetViewports();
    const epiBool hasInvalidViewport = std::any_of(viewports.begin(), viewports.end(), [](const gfxPipelineViewport& v)
    {
        return !v.IsValid();
    });

    if (hasInvalidViewport)
    {
        epiLogError("Failed to create Pipeline! Some of the provided Viewports is invalid!");
        return pipeline;
    }

    const epiArray<epiRect2s>& scissors = info.GetScissors();
    const epiBool hasInvalidScissor = std::any_of(scissors.begin(), scissors.end(), [](const epiRect2s& s)
    {
        return s.IsEmpty();
    });

    if (hasInvalidScissor)
    {
        epiLogError("Failed to create Pipeline! Provided RenderPass has invalid scissor!");
        return pipeline;
    }

    if (std::shared_ptr<gfxPipelineGraphics::Impl> impl = m_Impl->CreatePipelineGraphics(info))
    {
        pipeline = gfxPipelineGraphics(std::move(impl));
    }

    return pipeline;
}

std::optional<gfxShaderModule> gfxDevice::CreateShaderModule(const gfxShaderModuleCreateInfo& info)
{
    std::optional<gfxShaderModule> shaderModule;

    if (std::shared_ptr<gfxShaderModule::Impl> impl = m_Impl->CreateShaderModule(info))
    {
        shaderModule = gfxShaderModule(std::move(impl));
    }

    return shaderModule;
}

std::optional<gfxFrameBuffer> gfxDevice::CreateFrameBuffer(const gfxFrameBufferCreateInfo& info)
{
    std::optional<gfxFrameBuffer> frameBuffer;

    if (!info.GetRenderPass().HasImpl())
    {
        epiLogError("Failed to create FrameBuffer! Provided RenderPass has no implementation!");
        return frameBuffer;
    }

    if (std::shared_ptr<gfxFrameBuffer::Impl> impl = m_Impl->CreateFrameBuffer(info))
    {
        frameBuffer = gfxFrameBuffer(std::move(impl));
    }

    return frameBuffer;
}

std::optional<gfxImage> gfxDevice::CreateImage(const gfxImageCreateInfo& info)
{
    std::optional<gfxImage> image;

    if (std::shared_ptr<gfxImage::Impl> impl = m_Impl->CreateImage(info))
    {
        image = gfxImage(std::move(impl));
    }

    return image;
}

std::optional<gfxImageView> gfxDevice::CreateImageView(const gfxImageViewCreateInfo& info)
{
    std::optional<gfxImageView> imageView;

    if (!info.GetImage().HasImpl())
    {
        epiLogError("Failed to create ImageView! The provided Image has no implementation!");
        return imageView;
    }

    if (std::shared_ptr<gfxImageView::Impl> impl = m_Impl->CreateImageView(info))
    {
        imageView = gfxImageView(std::move(impl));
    }

    return imageView;
}

std::optional<gfxSampler> gfxDevice::CreateSampler(const gfxSamplerCreateInfo& info)
{
    std::optional<gfxSampler> sampler;

    if (std::shared_ptr<gfxSampler::Impl> impl = m_Impl->CreateSampler(info))
    {
        sampler = gfxSampler(std::move(impl));
    }

    return sampler;
}

std::optional<gfxCommandPool> gfxDevice::CreateCommandPool(const gfxCommandPoolCreateInfo& info)
{
    std::optional<gfxCommandPool> commnadPool;

    if (!info.GetQueueFamily().HasImpl())
    {
        epiLogError("Failed to create CommandPool! The provided QueueFamily has no implementation!");
        return commnadPool;
    }

    if (std::shared_ptr<gfxCommandPool::Impl> impl = m_Impl->CreateCommandPool(info))
    {
        commnadPool = gfxCommandPool(std::move(impl));
    }

    return commnadPool;
}

std::optional<gfxBuffer> gfxDevice::CreateBuffer(const gfxBufferCreateInfo& info)
{
    std::optional<gfxBuffer> buffer;

    if (std::shared_ptr<gfxBuffer::Impl> impl = m_Impl->CreateBuffer(info))
    {
        buffer = gfxBuffer(std::move(impl));
    }

    return buffer;
}

std::optional<gfxDeviceMemory> gfxDevice::CreateDeviceMemory(const gfxDeviceMemoryCreateInfo& info)
{
    std::optional<gfxDeviceMemory> deviceMemory;

    if (std::shared_ptr<gfxDeviceMemory::Impl> impl = m_Impl->CreateDeviceMemory(info))
    {
        deviceMemory = gfxDeviceMemory(std::move(impl));
    }

    return deviceMemory;
}

std::optional<gfxDeviceMemoryAllocator> gfxDevice::CreateDeviceMemoryAllocator(const gfxDeviceMemoryAllocatorCreateInfo& info)
{
    std::optional<gfxDeviceMemoryAllocator> deviceMemoryAllocator;

    if (std::shared_ptr<gfxDeviceMemoryAllocator::Impl> impl = m_Impl->CreateDeviceMemoryAllocator(info))
    {
        deviceMemoryAllocator = gfxDeviceMemoryAllocator(std::move(impl));
    }

    return deviceMemoryAllocator;
}

std::optional<gfxDescriptorSetLayout> gfxDevice::CreateDescriptorSetLayout(const gfxDescriptorSetLayoutCreateInfo& info)
{
    std::optional<gfxDescriptorSetLayout> descriptorSetLayout;

    if (std::shared_ptr<gfxDescriptorSetLayout::Impl> impl = m_Impl->CreateDescriptorSetLayout(info))
    {
        descriptorSetLayout = gfxDescriptorSetLayout(std::move(impl));
    }

    return descriptorSetLayout;
}

std::optional<gfxDescriptorPool> gfxDevice::CreateDescriptorPool(const gfxDescriptorPoolCreateInfo& info)
{
    std::optional<gfxDescriptorPool> descriptorPool;

    if (std::shared_ptr<gfxDescriptorPool::Impl> impl = m_Impl->CreateDescriptorPool(info))
    {
        descriptorPool = gfxDescriptorPool(std::move(impl));
    }

    return descriptorPool;
}

std::optional<gfxSemaphore> gfxDevice::CreateSemaphoreFrom(const gfxSemaphoreCreateInfo& info)
{
    std::optional<gfxSemaphore> semaphore;

    if (std::shared_ptr<gfxSemaphore::Impl> impl = m_Impl->CreateSemaphoreFrom(info))
    {
        semaphore = gfxSemaphore(std::move(impl));
    }

    return semaphore;
}

std::optional<gfxFence> gfxDevice::CreateFence(const gfxFenceCreateInfo& info)
{
    std::optional<gfxFence> fence;

    if (std::shared_ptr<gfxFence::Impl> impl = m_Impl->CreateFence(info))
    {
        fence = gfxFence(std::move(impl));
    }

    return fence;

}

const gfxPhysicalDevice& gfxDevice::GetPhysicalDevice_Callback() const
{
    epiAssert(HasImpl());

    return m_Impl->GetPhysicalDevice();
}

EPI_NAMESPACE_END()