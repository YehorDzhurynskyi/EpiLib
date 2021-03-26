#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkDevice_T;
struct VkShaderModule_T;
struct VkPipelineShaderStageCreateInfo_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxShaderImplVK : public gfxShaderImpl
{
public:
    gfxShaderImplVK(VkDevice_T* device);
    gfxShaderImplVK(const gfxShaderImplVK& rhs) = delete;
    gfxShaderImplVK& operator=(const gfxShaderImplVK& rhs) = delete;
    gfxShaderImplVK(gfxShaderImplVK&& rhs);
    gfxShaderImplVK& operator=(gfxShaderImplVK&& rhs);
    ~gfxShaderImplVK() override;

    epiBool GetIsCreated() const override;
    gfxShaderType GetType() const override;

    epiBool InitFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint = "main") override;

    const epiString& GetEntryPoint() const;
    VkShaderModule_T* GetVkShaderModule() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkShaderModule_T* m_VkShaderModule{nullptr};
    gfxShaderType m_Type{gfxShaderType::None};
    epiString m_EntryPoint;
};

class gfxShaderProgramImplVK : public gfxShaderProgramImpl
{
public:
    gfxShaderProgramImplVK() = default;
    gfxShaderProgramImplVK(const gfxShaderProgramImplVK& rhs) = delete;
    gfxShaderProgramImplVK& operator=(const gfxShaderProgramImplVK& rhs) = delete;
    gfxShaderProgramImplVK(gfxShaderProgramImplVK&& rhs) = default;
    gfxShaderProgramImplVK& operator=(gfxShaderProgramImplVK&& rhs) = default;
    ~gfxShaderProgramImplVK() override = default;

    epiBool GetIsCreated() const override;

    epiBool Init(const gfxShaderProgramCreateInfoImpl& info);

    epiArray<gfxShaderImplVK*> GetCompiledModules() const;

protected:
    gfxShaderProgramCreateInfoImpl m_ShaderProgramCreateInfo;
};

} // namespace internalgfx

EPI_NAMESPACE_END()
