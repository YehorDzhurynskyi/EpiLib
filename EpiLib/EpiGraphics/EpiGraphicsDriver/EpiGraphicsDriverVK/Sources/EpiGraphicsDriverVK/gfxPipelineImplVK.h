#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"
#include "EpiGraphicsDriverVK/gfxDeviceImplVK.h"

struct VkPipelineLayout_T;
struct VkPipeline_T;
struct VkDevice_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxPipelineImplVK : public gfxPipelineImpl
{
public:
    explicit gfxPipelineImplVK(const gfxDeviceImplVK& device);
    gfxPipelineImplVK(const gfxPipelineImplVK& rhs) = delete;
    gfxPipelineImplVK& operator=(const gfxPipelineImplVK& rhs) = delete;
    gfxPipelineImplVK(gfxPipelineImplVK&& rhs) = default;
    gfxPipelineImplVK& operator=(gfxPipelineImplVK&& rhs) = default;
    ~gfxPipelineImplVK() override;

    epiBool Init(const gfxPipelineCreateInfo& info, const gfxShaderProgramImpl& shaderProgramImpl, const gfxRenderPassImpl& renderPassImpl);

protected:
    const gfxDeviceImplVK& m_Device;
    VkPipeline_T* m_VkPipeline{nullptr};
    VkPipelineLayout_T* m_VkPipelineLayout{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
