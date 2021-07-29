#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxShaderModule.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

enum class gfxShaderModuleFrontend : epiS32
{
EPI_GENREGION_BEGIN(gfxShaderModuleFrontend)
    Unknown = 0,
    SPIRV = 1
EPI_GENREGION_END(gfxShaderModuleFrontend)
};

class gfxShaderModuleCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxShaderModuleCreateInfo)

EPI_GENHIDDEN_gfxShaderModuleCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xbf14012a};

    enum gfxShaderModuleCreateInfo_PIDs
    {
        PID_Stage = 0x3bdbc6d,
        PID_CompileFromSource = 0xe6c5b2ff,
        PID_Code = 0xd7279fa6,
        PID_EntryPoint = 0xc03ed7f8,
        PID_COUNT = 4
    };

protected:
    gfxShaderStage m_Stage{};
    epiBool m_CompileFromSource{false};
    epiArray<epiU8> m_Code{};
    epiString m_EntryPoint{"main"};

EPI_GENREGION_END(gfxShaderModuleCreateInfo)

public:
    static gfxShaderModuleCreateInfo FromSource(const epiChar* source, epiSize_t size, gfxShaderStage stage);
    static gfxShaderModuleCreateInfo FromSource(const epiString& source, gfxShaderStage stage);
};

class gfxShaderModule : public Object
{
EPI_GENREGION_BEGIN(gfxShaderModule)

EPI_GENHIDDEN_gfxShaderModule()

public:
    constexpr static epiMetaTypeID TypeID{0x5dea8f6f};

    enum gfxShaderModule_PIDs
    {
        PID_Stage = 0x3bdbc6d,
        PID_Code = 0xd7279fa6,
        PID_Frontend = 0x35677cca,
        PID_EntryPoint = 0xc03ed7f8,
        PID_COUNT = 4
    };

protected:
    gfxShaderStage GetStage_Callback() const;
    const epiArray<epiU8>& GetCode_Callback() const;
    gfxShaderModuleFrontend GetFrontend_Callback() const;
    const epiString& GetEntryPoint_Callback() const;

EPI_GENREGION_END(gfxShaderModule)

public:
    class Impl;

public:
    gfxShaderModule() = default;
    explicit gfxShaderModule(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
