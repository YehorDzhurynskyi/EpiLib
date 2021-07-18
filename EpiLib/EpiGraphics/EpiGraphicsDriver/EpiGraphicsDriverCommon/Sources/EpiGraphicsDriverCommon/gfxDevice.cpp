EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDevice.h"
#include "EpiGraphicsDriverCommon/gfxDevice.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"
#include "EpiGraphicsDriverCommon/gfxSurface.h"

EPI_NAMESPACE_BEGIN()

gfxDevice::gfxDevice(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
    epiArray<gfxQueueFamily>& queueFamilies = GetQueueFamilies();
    queueFamilies.Reserve(impl->GetQueueFamilies().Size());

    // NOTE: filling gfxQueueFamily with their implementations (gfxDeviceImpl still owns these implementations)
    std::transform(impl->GetQueueFamilies().begin(),
                   impl->GetQueueFamilies().end(),
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

std::optional<gfxSwapChain> gfxDevice::CreateSwapChain(const gfxSwapChainCreateInfo& info) const
{
    std::optional<gfxSwapChain> swapChain;

    if (std::shared_ptr<gfxSwapChain::Impl> impl = m_Impl->CreateSwapChain(info))
    {
        swapChain = gfxSwapChain(std::move(impl));
    }

    return swapChain;
}

std::optional<gfxRenderPass> gfxDevice::CreateRenderPass(const gfxRenderPassCreateInfo& info) const
{
    std::optional<gfxRenderPass> renderPass;

    if (std::shared_ptr<internalgfx::gfxRenderPassImpl> impl = m_Impl->CreateRenderPass(info))
    {
        renderPass = gfxRenderPass(std::move(impl));
    }

    return renderPass;
}

std::optional<gfxPipelineLayout> gfxDevice::CreatePipelineLayout(const gfxPipelineLayoutCreateInfo& info) const
{
    std::optional<gfxPipelineLayout> pipelineLayout;

    if (std::shared_ptr<internalgfx::gfxPipelineLayoutImpl> impl = m_Impl->CreatePipelineLayout(info))
    {
        pipelineLayout = gfxPipelineLayout(std::move(impl));
    }

    return pipelineLayout;
}

std::optional<gfxPipelineGraphics> gfxDevice::CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info, const gfxRenderPass& renderPass) const
{
    std::optional<gfxPipelineGraphics> pipeline;

    const auto shaderProgramImpl = info.GetShaderProgram().m_Impl;
    if (!shaderProgramImpl)
    {
        epiLogError("Failed to create Pipeline! Provided ShaderProgram has no implementation!");
        return pipeline;
    }

    const auto renderPassImpl = renderPass.m_Impl;
    if (!renderPassImpl)
    {
        epiLogError("Failed to create Pipeline! Provided RenderPass has no implemetation!");
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

    if (std::shared_ptr<internalgfx::gfxPipelineGraphicsImpl> impl = m_Impl->CreatePipelineGraphics(info, *shaderProgramImpl, *renderPassImpl))
    {
        pipeline = gfxPipelineGraphics(std::move(impl));
    }

    return pipeline;
}

std::optional<gfxShader> gfxDevice::CreateShaderFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint) const
{
    std::optional<gfxShader> shader;

    if (std::shared_ptr<internalgfx::gfxShaderImpl> impl = m_Impl->CreateShaderFromSource(source, type, entryPoint))
    {
        shader = gfxShader(std::move(impl));
    }

    return shader;
}

std::optional<gfxShader> gfxDevice::CreateShaderFromBinary(const epiU8* binary, epiSize_t size, gfxShaderType type, const epiChar* entryPoint) const
{
    std::optional<gfxShader> shader;

    if (std::shared_ptr<internalgfx::gfxShaderImpl> impl = m_Impl->CreateShaderFromBinary(binary, size, type, entryPoint))
    {
        shader = gfxShader(std::move(impl));
    }

    return shader;
}

std::optional<gfxShaderProgram> gfxDevice::CreateShaderProgram(const gfxShaderProgramCreateInfo& info) const
{
    // TODO: handle const_cast via epigen

    std::optional<gfxShaderProgram> shaderProgram;

    internalgfx::gfxShaderProgramCreateInfoImpl infoImpl;
    if (const gfxShader* vertex = info.GetVertex(); vertex != nullptr)
    {
        if (infoImpl.Vertex = const_cast<internalgfx::gfxShaderImpl*>(vertex->m_Impl.Ptr()); infoImpl.Vertex == nullptr)
        {
            return shaderProgram;
        }
    }

    if (const gfxShader* geometry = info.GetGeometry(); geometry != nullptr)
    {
        if (infoImpl.Geometry = const_cast<internalgfx::gfxShaderImpl*>(geometry->m_Impl.Ptr()); infoImpl.Geometry == nullptr)
        {
            return shaderProgram;
        }
    }

    if (const gfxShader* fragment = info.GetFragment(); fragment != nullptr)
    {
        if (infoImpl.Fragment = const_cast<internalgfx::gfxShaderImpl*>(fragment->m_Impl.Ptr()); infoImpl.Fragment == nullptr)
        {
            return shaderProgram;
        }
    }

    if (std::shared_ptr<internalgfx::gfxShaderProgramImpl> impl = m_Impl->CreateShaderProgram(infoImpl))
    {
        shaderProgram = gfxShaderProgram(std::move(impl));
    }

    return shaderProgram;
}

std::optional<gfxFrameBuffer> gfxDevice::CreateFrameBuffer(const gfxFrameBufferCreateInfo& info) const
{
    std::optional<gfxFrameBuffer> frameBuffer;

    const gfxRenderPass& renderPass = info.GetRenderPass();

    const auto renderPassImpl = renderPass.m_Impl;
    if (!renderPassImpl)
    {
        epiLogError("Failed to create FrameBuffer! Provided RenderPass has no implementation!");
        return frameBuffer;
    }

    epiPtrArray<const internalgfx::gfxTextureViewImpl> textureViewImpls;
    textureViewImpls.Reserve(info.GetAttachments().Size());
    std::transform(info.GetAttachments().begin(), info.GetAttachments().end(), std::back_inserter(textureViewImpls), [](const gfxTextureView& view)
    {
        return &*view.m_Impl;
    });

    if (std::shared_ptr<gfxFrameBuffer::Impl> impl = m_Impl->CreateFrameBuffer(info, *renderPassImpl, textureViewImpls))
    {
        frameBuffer = gfxFrameBuffer(std::move(impl));
    }

    return frameBuffer;
}

std::optional<gfxTexture> gfxDevice::CreateTexture(const gfxTextureCreateInfo& info) const
{
    std::optional<gfxTexture> texture;

    if (std::shared_ptr<internalgfx::gfxTextureImpl> impl = m_Impl->CreateTexture(info))
    {
        texture = gfxTexture(std::move(impl));
    }

    return texture;
}

std::optional<gfxTextureView> gfxDevice::CreateTextureView(const gfxTextureViewCreateInfo& info) const
{
    std::optional<gfxTextureView> textureView;

    const auto textureImpl = info.GetImage().m_Impl;
    if (!textureImpl)
    {
        epiLogError("Failed to create TextureView! Provided Texture has no implementation!");
        return textureView;
    }

    if (std::shared_ptr<internalgfx::gfxTextureViewImpl> impl = m_Impl->CreateTextureView(info, *textureImpl))
    {
        textureView = gfxTextureView(std::move(impl));
    }

    return textureView;
}

std::optional<gfxSampler> gfxDevice::CreateSampler(const gfxSamplerCreateInfo& info) const
{
    std::optional<gfxSampler> sampler;

    if (std::shared_ptr<internalgfx::gfxSamplerImpl> impl = m_Impl->CreateSampler(info))
    {
        sampler = gfxSampler(std::move(impl));
    }

    return sampler;
}

std::optional<gfxCommandPool> gfxDevice::CreateCommandPool(const gfxCommandPoolCreateInfo& info) const
{
    std::optional<gfxCommandPool> commnadPool;

    if (!info.GetQueueFamily().HasImpl())
    {
        epiLogError("Failed to create CommandPool! The provided QueueFamily has no implementation!");
        return commnadPool;
    }

    if (std::shared_ptr<internalgfx::gfxCommandPoolImpl> impl = m_Impl->CreateCommandPool(info))
    {
        commnadPool = gfxCommandPool(std::move(impl));
    }

    return commnadPool;
}

std::optional<gfxBuffer> gfxDevice::CreateBuffer(const gfxBufferCreateInfo& info) const
{
    std::optional<gfxBuffer> buffer;

    if (std::shared_ptr<gfxBuffer::Impl> impl = m_Impl->CreateBuffer(info))
    {
        buffer = gfxBuffer(std::move(impl));
    }

    return buffer;
}

std::optional<gfxDeviceMemory> gfxDevice::CreateDeviceMemory(const gfxDeviceMemoryBufferCreateInfo& info) const
{
    std::optional<gfxDeviceMemory> deviceMemory;

    if (!info.GetBuffer().HasImpl())
    {
        epiLogError("Failed to create DeviceMemory! Provided Buffer has no implementation!");
        return deviceMemory;
    }

    if (std::shared_ptr<internalgfx::gfxDeviceMemoryImpl> impl = m_Impl->CreateDeviceMemory(info))
    {
        deviceMemory = gfxDeviceMemory(std::move(impl));
    }

    return deviceMemory;
}

std::optional<gfxDeviceMemory> gfxDevice::CreateDeviceMemory(const gfxDeviceMemoryImageCreateInfo& info) const
{
    std::optional<gfxDeviceMemory> deviceMemory;

    const auto imageImpl = info.GetImage().m_Impl;
    if (!imageImpl)
    {
        epiLogError("Failed to create DeviceMemory! Provided Image has no implementation!");
        return deviceMemory;
    }

    if (std::shared_ptr<internalgfx::gfxDeviceMemoryImpl> impl = m_Impl->CreateDeviceMemory(info))
    {
        deviceMemory = gfxDeviceMemory(std::move(impl));
    }

    return deviceMemory;
}

std::optional<gfxDescriptorSetLayout> gfxDevice::CreateDescriptorSetLayout(const gfxDescriptorSetLayoutCreateInfo& info) const
{
    std::optional<gfxDescriptorSetLayout> descriptorSetLayout;

    if (std::shared_ptr<internalgfx::gfxDescriptorSetLayoutImpl> impl = m_Impl->CreateDescriptorSetLayout(info))
    {
        descriptorSetLayout = gfxDescriptorSetLayout(std::move(impl));
    }

    return descriptorSetLayout;
}

std::optional<gfxDescriptorPool> gfxDevice::CreateDescriptorPool(const gfxDescriptorPoolCreateInfo& info) const
{
    std::optional<gfxDescriptorPool> descriptorPool;

    epiPtrArray<const internalgfx::gfxDescriptorSetLayoutImpl> layoutImpls;
    layoutImpls.Reserve(info.GetDescriptorSetLayouts().Size());

    std::transform(info.GetDescriptorSetLayouts().begin(),
                   info.GetDescriptorSetLayouts().end(),
                   std::back_inserter(layoutImpls),
                   [](const gfxDescriptorSetLayout& layout)
    {
        return layout.m_Impl.Ptr();
    });

    const epiBool hasInvalidLayout = std::any_of(layoutImpls.begin(),
                                                 layoutImpls.end(),
                                                 [](const internalgfx::gfxDescriptorSetLayoutImpl* impl)
    {
        return impl == nullptr;
    });

    if (hasInvalidLayout)
    {
        epiLogError("Failed to create DescriptorPool! Some DescriptorSetLayout has no implementation!");
        return descriptorPool;
    }

    if (std::shared_ptr<internalgfx::gfxDescriptorPoolImpl> impl = m_Impl->CreateDescriptorPool(info, layoutImpls))
    {
        descriptorPool = gfxDescriptorPool(std::move(impl));
    }

    return descriptorPool;
}

std::optional<gfxSemaphore> gfxDevice::CreateSemaphoreFrom(const gfxSemaphoreCreateInfo& info) const
{
    std::optional<gfxSemaphore> semaphore;

    if (std::shared_ptr<gfxSemaphore::Impl> impl = m_Impl->CreateSemaphoreFrom(info))
    {
        semaphore = gfxSemaphore(std::move(impl));
    }

    return semaphore;
}

std::optional<gfxFence> gfxDevice::CreateFence(const gfxFenceCreateInfo& info) const
{
    std::optional<gfxFence> fence;

    if (std::shared_ptr<gfxFence::Impl> impl = m_Impl->CreateFence(info))
    {
        fence = gfxFence(std::move(impl));
    }

    return fence;

}

EPI_NAMESPACE_END()
