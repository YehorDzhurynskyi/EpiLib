#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkDevice_T;
struct VkSampler_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxSamplerImplVK : public gfxSamplerImpl
{
public:
    explicit gfxSamplerImplVK(VkDevice_T* device);
    gfxSamplerImplVK(const gfxSamplerImplVK& rhs) = delete;
    gfxSamplerImplVK& operator=(const gfxSamplerImplVK& rhs) = delete;
    gfxSamplerImplVK(gfxSamplerImplVK&& rhs) = default;
    gfxSamplerImplVK& operator=(gfxSamplerImplVK&& rhs) = default;
    ~gfxSamplerImplVK() override;

    epiBool Init(const gfxSamplerCreateInfo& info);

    VkSampler_T* GetVkSampler() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkSampler_T* m_VkSampler{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
