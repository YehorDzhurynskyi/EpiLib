#include "EpiGraphicsDriverVK/gfxShaderProgramImplVK.h"

#include <vulkan/vulkan.hpp>
#include <shaderc/shaderc.hpp>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxShaderImplVK::gfxShaderImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

gfxShaderImplVK::gfxShaderImplVK(gfxShaderImplVK&& rhs)
{
    m_VkShaderModule = rhs.m_VkShaderModule;
    m_Type = rhs.m_Type;

    rhs.m_VkShaderModule = nullptr;
    rhs.m_Type = gfxShaderType::None;
}

gfxShaderImplVK& gfxShaderImplVK::operator=(gfxShaderImplVK&& rhs)
{
    m_VkShaderModule = rhs.m_VkShaderModule;
    m_Type = rhs.m_Type;

    rhs.m_VkShaderModule = nullptr;
    rhs.m_Type = gfxShaderType::None;

    return *this;
}

epiBool gfxShaderImplVK::InitFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint)
{
    shaderc_shader_kind shaderKind;
    switch (type)
    {
    case gfxShaderType::Vertex: shaderKind = shaderc_vertex_shader; break;
    case gfxShaderType::Geometry: shaderKind = shaderc_geometry_shader; break;
    case gfxShaderType::Fragment: shaderKind = shaderc_fragment_shader; break;
    default: epiAssert(false, "Unhandled case"); return;
    }

    shaderc::CompileOptions options; // TODO: set compile options (optimization level etc)
    shaderc::Compiler compiler;
    const shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(source, shaderKind, "", entryPoint, options);
    if (result.GetCompilationStatus() != shaderc_compilation_status_success)
    {
        epiLogError("Vulkan shader compilation error: {}", result.GetErrorMessage());
        return false;
    }

    const std::vector<epiU32> byteCode{result.cbegin(), result.cend()};

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = byteCode.size();
    createInfo.pCode = byteCode.data();

    if (vkCreateShaderModule(m_VkDevice, &createInfo, nullptr, &m_VkShaderModule) != VK_SUCCESS)
    {
        return false;
    }

    m_Type = type;
    m_EntryPoint = entryPoint;

    return true;
}

gfxShaderImplVK::~gfxShaderImplVK()
{
    vkDestroyShaderModule(m_VkDevice, m_VkShaderModule, nullptr);
}

epiBool gfxShaderImplVK::GetIsCreated() const
{
    return m_Type != gfxShaderType::None && m_VkShaderModule != nullptr;
}

gfxShaderType gfxShaderImplVK::GetType() const
{
    return m_Type;
}

const epiString& gfxShaderImplVK::GetEntryPoint() const
{
    return m_EntryPoint;
}

VkShaderModule_T* gfxShaderImplVK::GetVkShaderModule() const
{
    return m_VkShaderModule;
}

epiBool gfxShaderProgramImplVK::Init(const gfxShaderProgramCreateInfo& info)
{
    m_ShaderProgramCreateInfo = info;
    return true;
}

epiBool gfxShaderProgramImplVK::GetIsCreated() const
{
    return !m_ShaderProgramCreateInfo.GetIsEmpty();
}

epiArray<gfxShaderImplVK*> gfxShaderProgramImplVK::GetCompiledModules() const
{
    epiArray<gfxShaderImplVK*> modules;

    if (m_ShaderVertexModule != nullptr)
    {
        modules.push_back(m_ShaderVertexModule.get());
    }

    if (m_ShaderGeometryModule != nullptr)
    {
        modules.push_back(m_ShaderGeometryModule.get());
    }

    if (m_ShaderFragmentModule != nullptr)
    {
        modules.push_back(m_ShaderFragmentModule.get());
    }

    return modules;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
