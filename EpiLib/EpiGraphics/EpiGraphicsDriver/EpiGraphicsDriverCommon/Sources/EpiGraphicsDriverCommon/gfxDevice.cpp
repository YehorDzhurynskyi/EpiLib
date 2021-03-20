EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDevice.h"
#include "EpiGraphicsDriverCommon/gfxDevice.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

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

EPI_NAMESPACE_END()
