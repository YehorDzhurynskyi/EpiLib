#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkDevice_T;
struct VkPipelineLayout_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxPipelineLayoutImplVK : public gfxPipelineLayoutImpl
{
public:
    explicit gfxPipelineLayoutImplVK(VkDevice_T* device);
    gfxPipelineLayoutImplVK(const gfxPipelineLayoutImplVK& rhs) = delete;
    gfxPipelineLayoutImplVK& operator=(const gfxPipelineLayoutImplVK& rhs) = delete;
    gfxPipelineLayoutImplVK(gfxPipelineLayoutImplVK&& rhs) = default;
    gfxPipelineLayoutImplVK& operator=(gfxPipelineLayoutImplVK&& rhs) = default;
    ~gfxPipelineLayoutImplVK() override;

    epiBool Init(const gfxPipelineLayoutCreateInfo& info);

    VkPipelineLayout_T* GetVkPipelineLayout() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkPipelineLayout_T* m_VkPipelineLayout{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
