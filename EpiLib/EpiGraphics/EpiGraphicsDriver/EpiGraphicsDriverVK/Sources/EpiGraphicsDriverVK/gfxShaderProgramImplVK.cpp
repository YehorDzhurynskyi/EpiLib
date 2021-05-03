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

gfxShaderBackend gfxShaderImplVK::GetBackend() const
{
    return m_Backend;
}

epiArray<epiU8> gfxShaderImplVK::GetCode() const
{
    return m_Code;
}

const epiString& gfxShaderImplVK::GetEntryPoint() const
{
    return m_EntryPoint;
}

VkShaderModule_T* gfxShaderImplVK::GetVkShaderModule() const
{
    return m_VkShaderModule;
}

epiBool gfxShaderImplVK::InitFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint)
{
    shaderc_shader_kind shaderKind;
    switch (type)
    {
    case gfxShaderType::Vertex: shaderKind = shaderc_vertex_shader; break;
    case gfxShaderType::Geometry: shaderKind = shaderc_geometry_shader; break;
    case gfxShaderType::Fragment: shaderKind = shaderc_fragment_shader; break;
    default: epiLogError("Unrecognized ShaderType value=`{}`", type); return false; // TODO: use str repr
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
    return InitFromBinary(reinterpret_cast<const epiU8*>(byteCode.data()), byteCode.size() * sizeof(epiU32), type, entryPoint);
}

epiBool gfxShaderImplVK::InitFromBinary(const epiU8* binary, epiSize_t size, gfxShaderType type, const epiChar* entryPoint)
{
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.pCode = reinterpret_cast<const epiU32*>(binary);
    createInfo.codeSize = size;

    if (vkCreateShaderModule(m_VkDevice, &createInfo, nullptr, &m_VkShaderModule) != VK_SUCCESS)
    {
        return false;
    }

    m_Type = type;
    m_EntryPoint = entryPoint;
    m_Backend = gfxShaderBackend::SPIRV;
    m_Code = epiArray<epiU8>(binary, binary + size); // TODO: save path to file instead of code

    return true;
}

epiBool gfxShaderProgramImplVK::Init(const gfxShaderProgramCreateInfoImpl& info)
{
    m_ShaderProgramCreateInfo = info;
    return true;
}

epiBool gfxShaderProgramImplVK::GetIsCreated() const
{
    static_assert(sizeof(m_ShaderProgramCreateInfo) == sizeof(void*) * 3, "Add shader type");
    return m_ShaderProgramCreateInfo.Vertex != nullptr ||
           m_ShaderProgramCreateInfo.Geometry != nullptr ||
           m_ShaderProgramCreateInfo.Fragment != nullptr;
}

epiArray<gfxShaderImplVK*> gfxShaderProgramImplVK::GetCompiledModules() const
{
    epiArray<gfxShaderImplVK*> modules;

    if (gfxShaderImpl* shader = m_ShaderProgramCreateInfo.Vertex; shader != nullptr)
    {
        modules.push_back(static_cast<gfxShaderImplVK*>(shader));
    }

    if (gfxShaderImpl* shader = m_ShaderProgramCreateInfo.Geometry; shader != nullptr)
    {
        modules.push_back(static_cast<gfxShaderImplVK*>(shader));
    }

    if (gfxShaderImpl* shader = m_ShaderProgramCreateInfo.Fragment; shader != nullptr)
    {
        modules.push_back(static_cast<gfxShaderImplVK*>(shader));
    }

    return modules;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
