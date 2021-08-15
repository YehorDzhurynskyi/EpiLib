#include "EpiGraphicsImplVK/gfxShaderModuleImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"

#include <vulkan/vulkan.h>
#include <shaderc/shaderc.hpp>

EPI_NAMESPACE_BEGIN()

gfxShaderModuleImplVK::gfxShaderModuleImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

gfxShaderModuleImplVK::~gfxShaderModuleImplVK()
{
    vkDestroyShaderModule(m_VkDevice, m_VkShaderModule, nullptr);
}

epiBool gfxShaderModuleImplVK::Init(const gfxShaderModuleCreateInfo& info)
{
    const epiU8* byteCode = nullptr;
    epiSize_t byteCodeSize = 0;

    shaderc::SpvCompilationResult result;
    if (info.GetCompileFromSource())
    {
        shaderc_shader_kind shaderKind;
        switch (info.GetStage())
        {
        case gfxShaderStage_Vertex: shaderKind = shaderc_vertex_shader; break;
        case gfxShaderStage_Geometry: shaderKind = shaderc_geometry_shader; break;
        case gfxShaderStage_Fragment: shaderKind = shaderc_fragment_shader; break;
        default: epiLogError("Unrecognized ShaderStage value=`{}`", info.GetStage()); return false; // TODO: use str repr
        }

        const epiChar* sourceCode = reinterpret_cast<const epiChar*>(info.GetCode().data());

        shaderc::CompileOptions options; // TODO: set compile options (optimization level etc)
        shaderc::Compiler compiler;
        result = compiler.CompileGlslToSpv(sourceCode,
                                          shaderKind,
                                          "filename" /* TODO: provide filename/shadername */,
                                          info.GetEntryPoint().c_str(),
                                          options);
        if (result.GetCompilationStatus() != shaderc_compilation_status_success)
        {
            epiLogError("Vulkan shader compilation error: {}", result.GetErrorMessage());
            return false;
        }

        byteCode = reinterpret_cast<const epiU8*>(result.begin());
        byteCodeSize = std::distance(result.begin(), result.end()) * sizeof(*result.begin());
    }
    else
    {
        byteCode = info.GetCode().data();
        byteCodeSize = info.GetCode().Size();
    }

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.pCode = reinterpret_cast<const epiU32*>(byteCode);
    createInfo.codeSize = byteCodeSize;

    if (const VkResult result = vkCreateShaderModule(m_VkDevice, &createInfo, nullptr, &m_VkShaderModule); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkCreateShaderModule!");
        return false;
    }

    m_Stage = info.GetStage();
    m_Code = epiArray<epiU8>(byteCode, byteCode + byteCodeSize); // TODO: save path to file instead of code
    m_Frontend = gfxShaderModuleFrontend::SPIRV; // TODO: set in a proper way
    m_EntryPoint = info.GetEntryPoint();

    return true;
}

gfxShaderStage gfxShaderModuleImplVK::GetStage() const
{
    return m_Stage;
}

const epiArray<epiU8>& gfxShaderModuleImplVK::GetCode() const
{
    return m_Code;
}

gfxShaderModuleFrontend gfxShaderModuleImplVK::GetFrontend() const
{
    return m_Frontend;
}

const epiString& gfxShaderModuleImplVK::GetEntryPoint() const
{
    return m_EntryPoint;
}

VkShaderModule_T* gfxShaderModuleImplVK::GetVkShaderModule() const
{
    return m_VkShaderModule;
}

EPI_NAMESPACE_END()
