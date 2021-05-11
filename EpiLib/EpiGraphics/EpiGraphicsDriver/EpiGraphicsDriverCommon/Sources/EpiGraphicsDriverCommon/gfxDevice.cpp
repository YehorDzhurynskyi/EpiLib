EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDevice.h"
#include "EpiGraphicsDriverCommon/gfxDevice.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"
#include "EpiGraphicsDriverCommon/gfxSurface.h"

EPI_NAMESPACE_BEGIN()

gfxDevice::gfxDevice(const std::shared_ptr<internalgfx::gfxDeviceImpl>& impl)
    : m_Impl{impl}
{
    epiArray<gfxQueueFamily>& queueFamilies = GetQueueFamilies();
    queueFamilies.Reserve(impl->GetQueueFamilies().Size());

    // NOTE: filling gfxQueueFamily with their implementations (gfxDeviceImpl still owns these implementations)
    std::transform(impl->GetQueueFamilies().begin(),
                   impl->GetQueueFamilies().end(),
                   std::back_inserter(queueFamilies),
                   [](const std::shared_ptr<internalgfx::gfxQueueFamilyImpl>& queueFamilyImpl)
    {
        return gfxQueueFamily(queueFamilyImpl);
    });
}

epiBool gfxDevice::IsExtensionEnabled(gfxPhysicalDeviceExtension extension) const
{
    return m_Impl->IsExtensionEnabled(extension);
}

epiBool gfxDevice::IsFeatureEnabled(gfxPhysicalDeviceFeature feature) const
{
    return m_Impl->IsFeatureEnabled(feature);
}

std::optional<gfxSwapChain> gfxDevice::CreateSwapChain(const gfxSwapChainCreateInfo& info) const
{
    std::optional<gfxSwapChain> swapChain;

    const auto surfaceImpl = info.GetSurface().m_Impl;
    if (!surfaceImpl)
    {
        epiLogError("Failed to create SwapChain! Surface has no implementation!");
        return swapChain;
    }

    const auto queueFamilyImpl = info.GetQueueFamily().m_Impl;
    if (!queueFamilyImpl)
    {
        epiLogError("Failed to create SwapChain! QueueFamily has no implementation!");
        return swapChain;
    }

    const auto renderPassImpl = info.GetRenderPass().m_Impl;
    if (!renderPassImpl)
    {
        epiLogError("Failed to create SwapChain! RenderPass has no implementation!");
        return swapChain;
    }

    if (std::shared_ptr<internalgfx::gfxSwapChainImpl> impl = m_Impl->CreateSwapChain(info, *surfaceImpl, *queueFamilyImpl, *renderPassImpl))
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

std::optional<gfxRenderPass> gfxDevice::CreateRenderPassFromSchema(const gfxRenderPassSchema& schema) const
{
    std::optional<gfxRenderPass> renderPass;

    if (std::shared_ptr<internalgfx::gfxRenderPassImpl> impl = m_Impl->CreateRenderPassFromSchema(schema))
    {
        renderPass = gfxRenderPass(std::move(impl));
    }

    return renderPass;
}

std::optional<gfxPipelineGraphics> gfxDevice::CreatePipelineGraphics(const gfxPipelineGraphicsCreateInfo& info, const gfxRenderPass& renderPass) const
{
    std::optional<gfxPipelineGraphics> pipeline;

    const auto shaderProgramImpl = info.GetShaderProgram().m_Impl;
    if (!shaderProgramImpl)
    {
        epiLogError("Failed to create Pipeline! ShaderProgram has no implementation!");
        return pipeline;
    }

    const auto renderPassImpl = renderPass.m_Impl;
    if (!renderPassImpl)
    {
        epiLogError("Failed to create Pipeline! RenderPass has no implemetation!");
        return pipeline;
    }

    const epiArray<gfxPipelineViewport>& viewports = info.GetViewports();
    const epiBool hasInvalidViewport = std::any_of(viewports.begin(), viewports.end(), [](const gfxPipelineViewport& v)
    {
        return v.GetViewportRect().IsEmpty() || (v.GetViewportMinDepth() > v.GetViewportMaxDepth());
    });

    if (hasInvalidViewport)
    {
        epiLogError("Failed to create Pipeline! RenderPass has invalid viewport!");
        return pipeline;
    }

    const epiArray<epiRect2s>& scissors = info.GetScissors();
    const epiBool hasInvalidScissor = std::any_of(scissors.begin(), scissors.end(), [](const epiRect2s& s)
    {
        return s.IsEmpty();
    });

    if (hasInvalidScissor)
    {
        epiLogError("Failed to create Pipeline! RenderPass has invalid scissor!");
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
        if (infoImpl.Vertex = const_cast<internalgfx::gfxShaderImpl*>(vertex->m_Impl.Impl()); infoImpl.Vertex == nullptr)
        {
            return shaderProgram;
        }
    }

    if (const gfxShader* geometry = info.GetGeometry(); geometry != nullptr)
    {
        if (infoImpl.Geometry = const_cast<internalgfx::gfxShaderImpl*>(geometry->m_Impl.Impl()); infoImpl.Geometry == nullptr)
        {
            return shaderProgram;
        }
    }

    if (const gfxShader* fragment = info.GetFragment(); fragment != nullptr)
    {
        if (infoImpl.Fragment = const_cast<internalgfx::gfxShaderImpl*>(fragment->m_Impl.Impl()); infoImpl.Fragment == nullptr)
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
        epiLogError("Failed to create FrameBuffer! RenderPass has no implementation!");
        return frameBuffer;
    }

    if (std::shared_ptr<internalgfx::gfxFrameBufferImpl> impl = m_Impl->CreateFrameBuffer(info, *renderPassImpl))
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

    const gfxTexture* texture = info.GetTexture();
    if (texture == nullptr)
    {
        epiLogError("Failed to create TextureView! Texture hasn't provided!");
        return textureView;
    }

    const auto textureImpl = texture->m_Impl;
    if (!textureImpl)
    {
        epiLogError("Failed to create TextureView! Texture has no implementation!");
        return textureView;
    }

    if (std::shared_ptr<internalgfx::gfxTextureViewImpl> impl = m_Impl->CreateTextureView(info, *textureImpl))
    {
        textureView = gfxTextureView(std::move(impl));
    }

    return textureView;
}

std::optional<gfxCommandPool> gfxDevice::CreateCommandPool(const gfxCommandPoolCreateInfo& info) const
{
    std::optional<gfxCommandPool> commnadPool;

    const gfxQueueFamily& queueFamily = info.GetQueueFamily();

    const auto queueFamilyImpl = queueFamily.m_Impl;
    if (!queueFamilyImpl)
    {
        epiLogError("Failed to create CommandPool! QueueFamily has no implementation!");
        return commnadPool;
    }

    if (std::shared_ptr<internalgfx::gfxCommandPoolImpl> impl = m_Impl->CreateCommandPool(info, *queueFamilyImpl))
    {
        commnadPool = gfxCommandPool(std::move(impl));
    }

    return commnadPool;
}

EPI_NAMESPACE_END()
