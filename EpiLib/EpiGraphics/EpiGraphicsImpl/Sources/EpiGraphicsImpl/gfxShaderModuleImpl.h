#pragma once

#include "EpiGraphics/gfxShaderModule.h"

EPI_NAMESPACE_BEGIN()

class gfxShaderModule::Impl
{
public:
    static std::shared_ptr<gfxShaderModule::Impl> ExtractImpl(const gfxShaderModule& shaderModule) { return shaderModule.m_Impl; }

public:
    Impl() = default;
    Impl(const Impl& rhs) = delete;
    Impl& operator=(const Impl& rhs) = delete;
    Impl(Impl&& rhs) = default;
    Impl& operator=(Impl&& rhs) = default;
    virtual ~Impl() = default;

    virtual gfxShaderStage GetStage() const = 0;
    virtual const epiArray<epiU8>& GetCode() const = 0;
    virtual gfxShaderModuleFrontend GetFrontend() const = 0;
    virtual const epiString& GetEntryPoint() const = 0;
};

EPI_NAMESPACE_END()
