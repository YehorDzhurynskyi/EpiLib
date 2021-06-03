#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"
#include "EpiGraphicsDriverVK/gfxShaderProgramImplVK.h"
#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"
#include "EpiGraphicsDriverVK/gfxDescriptorSetLayoutImplVK.h"

struct VkDevice_T;
struct VkPipeline_T;
struct VkDescriptorSetLayout_T;

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

    epiBool Init(const gfxPipelineGraphicsCreateInfo& info,
                 const gfxShaderProgramImplVK& shaderProgramImpl,
                 const gfxRenderPassImplVK& renderPassImpl);

    VkPipeline_T* GetVkPipeline() const;

protected:
    const gfxDeviceImplVK& m_Device;
    VkPipeline_T* m_VkPipeline{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
