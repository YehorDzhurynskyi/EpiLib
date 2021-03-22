EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDevice.h"
#include "EpiGraphicsDriverCommon/gfxDevice.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"
#include "EpiGraphicsDriverCommon/gfxSurface.h"

EPI_NAMESPACE_BEGIN()

gfxDevice::gfxDevice(internalgfx::gfxDeviceImpl* impl)
    : m_Impl{impl}
{
}

gfxDevice::gfxDevice(gfxDevice&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;
}

gfxDevice& gfxDevice::operator=(gfxDevice&& rhs)
{
    m_Impl = rhs.m_Impl;
    rhs.m_Impl = nullptr;

    return *this;
}

gfxDevice::~gfxDevice()
{
    delete m_Impl;
}

std::optional<gfxSwapChain> gfxDevice::CreateSwapChain(const gfxSwapChainCreateInfo& info) const
{
    std::optional<gfxSwapChain> swapChain;

    const gfxSurface* surface = info.GetSurface();
    if (surface == nullptr)
    {
        epiLogError("Failed to create SwapChain! Surface isn't provided!");
        return swapChain;
    }
    const internalgfx::gfxSurfaceImpl* surfaceImpl = surface->m_Impl;
    if (surfaceImpl == nullptr)
    {
        epiLogError("Failed to create SwapChain! Surface has no implementation!");
        return swapChain;
    }

    const gfxRenderPass* renderPass = info.GetRenderPass();
    if (renderPass == nullptr)
    {
        epiLogError("Failed to create SwapChain! RenderPass isn't provided!");
        return swapChain;
    }
    const internalgfx::gfxRenderPassImpl* renderPassImpl = renderPass->m_Impl;
    if (renderPassImpl == nullptr)
    {
        epiLogError("Failed to create SwapChain! RenderPass has no implementation!");
        return swapChain;
    }

    if (std::unique_ptr<internalgfx::gfxSwapChainImpl> impl = m_Impl->CreateSwapChain(info, *surfaceImpl, *renderPassImpl))
    {
        swapChain = gfxSwapChain(impl.release());
    }

    return swapChain;
}

std::optional<gfxRenderPass> gfxDevice::CreateRenderPass(const gfxRenderPassCreateInfo& info) const
{
    std::optional<gfxRenderPass> renderPass;

    if (std::unique_ptr<internalgfx::gfxRenderPassImpl> impl = m_Impl->CreateRenderPass(info))
    {
        renderPass = gfxRenderPass(impl.release());
    }

    return renderPass;
}

std::optional<gfxPipeline> gfxDevice::CreatePipeline(const gfxPipelineCreateInfo& info) const
{
    std::optional<gfxPipeline> pipeline;

    const internalgfx::gfxShaderProgramImpl* shaderProgramImpl = info.GetShaderProgram().m_Impl;
    const internalgfx::gfxRenderPassImpl* renderPassImpl = info.GetRenderPass().m_Impl;
    if (std::unique_ptr<internalgfx::gfxPipelineImpl> impl = m_Impl->CreatePipeline(info, shaderProgramImpl, renderPassImpl))
    {
        pipeline = gfxPipeline(impl.release());
    }

    return pipeline;
}

std::optional<gfxShader> gfxDevice::CreateShaderFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint) const
{
    std::optional<gfxShader> shader;

    if (std::unique_ptr<internalgfx::gfxShaderImpl> impl = m_Impl->CreateShaderFromSource(source, type, entryPoint))
    {
        shader = gfxShader(impl.release());
    }

    return shader;
}

std::optional<gfxShaderProgram> gfxDevice::CreateShaderProgram(const gfxShaderProgramCreateInfo& info) const
{
    std::optional<gfxShaderProgram> shaderProgram;

    if (std::unique_ptr<internalgfx::gfxShaderProgramImpl> impl = m_Impl->CreateShaderProgram(info))
    {
        shaderProgram = gfxShaderProgram(impl.release());
    }

    return shaderProgram;
}

std::optional<gfxFrameBuffer> gfxDevice::CreateFrameBuffer(const gfxFrameBufferCreateInfo& info) const
{
    std::optional<gfxFrameBuffer> frameBuffer;

    const internalgfx::gfxRenderPassImpl* renderPassImpl = info.GetRenderPass().m_Impl;
    if (std::unique_ptr<internalgfx::gfxFrameBufferImpl> impl = m_Impl->CreateFrameBuffer(info, renderPassImpl))
    {
        frameBuffer = gfxFrameBuffer(impl.release());
    }

    return frameBuffer;
}

std::optional<gfxTexture> gfxDevice::CreateTexture(const gfxTextureCreateInfo& info) const
{
    std::optional<gfxTexture> texture;

    if (std::unique_ptr<internalgfx::gfxTextureImpl> impl = m_Impl->CreateTexture(info))
    {
        texture = gfxTexture(impl.release());
    }

    return texture;
}

std::optional<gfxTextureView> gfxDevice::CreateTextureView(const gfxTextureViewCreateInfo& info) const
{
    std::optional<gfxTextureView> textureView;

    const internalgfx::gfxTextureImpl* textureImpl = info.GetTexture().m_Impl;
    if (std::unique_ptr<internalgfx::gfxTextureViewImpl> impl = m_Impl->CreateTextureView(info, textureImpl))
    {
        textureView = gfxTextureView(impl.release());
    }

    return textureView;
}

std::optional<gfxCommandPool> gfxDevice::CreateCommandPool(const gfxCommandPoolCreateInfo& info) const
{
    std::optional<gfxCommandPool> commnadPool;

    const internalgfx::gfxQueueFamilyImpl* queueFamilyImpl = nullptr;
    if (const gfxQueueFamily* queueFamily = info.GetQueueFamily())
    {
        queueFamilyImpl = queueFamily->m_Impl;
    }
    else
    {
        epiLogError("gfxCommandPoolCreateInfo QueueFamily has no implementation!");
        return commnadPool;
    }

    if (std::unique_ptr<internalgfx::gfxCommandPoolImpl> impl = m_Impl->CreateCommandPool(info, queueFamilyImpl))
    {
        commnadPool = gfxCommandPool(impl.release());
    }

    return commnadPool;
}

EPI_NAMESPACE_END()
