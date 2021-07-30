EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxShaderModule.h"
#include "EpiGraphics/gfxShaderModule.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

gfxShaderModuleCreateInfo gfxShaderModuleCreateInfo::FromSource(const epiChar* source, epiSize_t size, gfxShaderStage stage)
{
    epiAssert(source[size] == '\0');

    gfxShaderModuleCreateInfo info{};
    info.SetStage(stage);
    info.SetCompileFromSource(true);
    info.SetCode(epiArray<epiU8>(source, source + size + 1));

    return info;
}

gfxShaderModuleCreateInfo gfxShaderModuleCreateInfo::FromSource(const epiString& source, gfxShaderStage stage)
{
    return FromSource(source.c_str(), source.size(), stage);
}

gfxShaderModule::gfxShaderModule(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxShaderModule::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
}

gfxShaderStage gfxShaderModule::GetStage_Callback() const
{
    return m_Impl->GetStage();
}

const epiArray<epiU8>& gfxShaderModule::GetCode_Callback() const
{
    return m_Impl->GetCode();
}

gfxShaderModuleFrontend gfxShaderModule::GetFrontend_Callback() const
{
    return m_Impl->GetFrontend();
}

const epiString& gfxShaderModule::GetEntryPoint_Callback() const
{
    return m_Impl->GetEntryPoint();
}

EPI_NAMESPACE_END()
