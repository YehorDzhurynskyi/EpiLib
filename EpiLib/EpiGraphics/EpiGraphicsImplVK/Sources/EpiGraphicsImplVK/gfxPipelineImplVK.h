#pragma once

#include "EpiGraphics/gfxDriverInternal.h"

#include "EpiGraphicsImplVK/gfxDeviceImplVK.h"
#include "EpiGraphicsImplVK/gfxShaderModuleImplVK.h"
#include "EpiGraphicsImplVK/gfxRenderPassImplVK.h"
#include "EpiGraphicsImplVK/gfxDescriptorSetLayoutImplVK.h"

struct VkDevice_T;
struct VkPipeline_T;
struct VkDescriptorSetLayout_T;

EPI_NAMESPACE_BEGIN()

class gfxPipelineGraphicsImplVK : public gfxPipelineGraphics::Impl
{
public:
    explicit gfxPipelineGraphicsImplVK(const gfxDeviceImplVK& device);
    gfxPipelineGraphicsImplVK(const gfxPipelineGraphicsImplVK& rhs) = delete;
    gfxPipelineGraphicsImplVK& operator=(const gfxPipelineGraphicsImplVK& rhs) = delete;
    gfxPipelineGraphicsImplVK(gfxPipelineGraphicsImplVK&& rhs) = default;
    gfxPipelineGraphicsImplVK& operator=(gfxPipelineGraphicsImplVK&& rhs) = default;
    ~gfxPipelineGraphicsImplVK() override;

    epiBool Init(const gfxPipelineGraphicsCreateInfo& info);

    VkPipeline_T* GetVkPipeline() const;

protected:
    const gfxDeviceImplVK& m_Device;
    VkPipeline_T* m_VkPipeline{nullptr};
};

EPI_NAMESPACE_END()
