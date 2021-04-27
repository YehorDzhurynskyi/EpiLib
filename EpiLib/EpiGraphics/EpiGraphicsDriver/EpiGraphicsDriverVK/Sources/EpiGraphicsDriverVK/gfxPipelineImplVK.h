#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"
#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

struct VkPipelineLayout_T;
struct VkPipeline_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxPipelineGraphicsImplVK : public gfxPipelineGraphicsImpl
{
public:
    explicit gfxPipelineGraphicsImplVK(const gfxDeviceImplVK& device);
    gfxPipelineGraphicsImplVK(const gfxPipelineGraphicsImplVK& rhs) = delete;
    gfxPipelineGraphicsImplVK& operator=(const gfxPipelineGraphicsImplVK& rhs) = delete;
    gfxPipelineGraphicsImplVK(gfxPipelineGraphicsImplVK&& rhs) = default;
    gfxPipelineGraphicsImplVK& operator=(gfxPipelineGraphicsImplVK&& rhs) = default;
    ~gfxPipelineGraphicsImplVK() override;

    epiBool Init(const gfxPipelineGraphicsCreateInfo& info, const gfxShaderProgramImpl& shaderProgramImpl, const gfxRenderPassImpl& renderPassImpl);

    VkPipeline_T* GetVkPipeline() const;

protected:
    const gfxDeviceImplVK& m_Device;
    VkPipeline_T* m_VkPipeline{nullptr};
    VkPipelineLayout_T* m_VkPipelineLayout{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
