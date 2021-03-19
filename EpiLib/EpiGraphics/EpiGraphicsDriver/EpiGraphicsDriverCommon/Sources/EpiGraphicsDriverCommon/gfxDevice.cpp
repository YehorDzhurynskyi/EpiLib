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

EPI_NAMESPACE_END()
