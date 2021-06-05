#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

struct VkDescriptorSet_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDescriptorSetImplVK : public gfxDescriptorSetImpl
{
public:
    explicit gfxDescriptorSetImplVK(VkDescriptorSet_T* descriptorSet);
    gfxDescriptorSetImplVK(const gfxDescriptorSetImplVK& rhs) = delete;
    gfxDescriptorSetImplVK& operator=(const gfxDescriptorSetImplVK& rhs) = delete;
    gfxDescriptorSetImplVK(gfxDescriptorSetImplVK&& rhs) = default;
    gfxDescriptorSetImplVK& operator=(gfxDescriptorSetImplVK&& rhs) = default;
    ~gfxDescriptorSetImplVK() override = default;

    VkDescriptorSet_T* GetVkDescriptorSet() const;

protected:
    VkDescriptorSet_T* m_VkDescriptorSet{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()