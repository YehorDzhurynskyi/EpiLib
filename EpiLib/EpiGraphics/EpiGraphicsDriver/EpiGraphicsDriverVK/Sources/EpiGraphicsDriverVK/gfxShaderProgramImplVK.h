#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkDevice_T;
struct VkShaderModule_T;
struct VkPipelineShaderStageCreateInfo_T;

EPI_NAMESPACE_BEGIN()

class gfxShaderModuleImplVK : public gfxShaderModule::Impl
{
public:
    explicit gfxShaderModuleImplVK(VkDevice_T* device);
    gfxShaderModuleImplVK(const gfxShaderModuleImplVK& rhs) = delete;
    gfxShaderModuleImplVK& operator=(const gfxShaderModuleImplVK& rhs) = delete;
    gfxShaderModuleImplVK(gfxShaderModuleImplVK&& rhs) = default;
    gfxShaderModuleImplVK& operator=(gfxShaderModuleImplVK&& rhs) = default;
    ~gfxShaderModuleImplVK() override;

    epiBool Init(const gfxShaderModuleCreateInfo& info);

    gfxShaderStage GetStage() const override;
    const epiArray<epiU8>& GetCode() const override;
    gfxShaderModuleFrontend GetFrontend() const override;
    const epiString& GetEntryPoint() const override;

    VkShaderModule_T* GetVkShaderModule() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkShaderModule_T* m_VkShaderModule{nullptr};

    gfxShaderStage m_Stage{};
    epiArray<epiU8> m_Code;
    gfxShaderModuleFrontend m_Frontend{gfxShaderModuleFrontend::Unknown};
    epiString m_EntryPoint;
};

EPI_NAMESPACE_END()
