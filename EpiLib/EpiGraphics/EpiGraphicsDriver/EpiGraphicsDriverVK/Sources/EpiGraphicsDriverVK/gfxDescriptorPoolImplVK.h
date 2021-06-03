#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

#include "EpiGraphicsDriverVK/gfxDescriptorSetLayoutImplVK.h"

struct VkDevice_T;
struct VkDescriptorPool_T;

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDescriptorPoolImplVK : public gfxDescriptorPoolImpl
{
public:
    explicit gfxDescriptorPoolImplVK(VkDevice_T* device);
    gfxDescriptorPoolImplVK(const gfxDescriptorPoolImplVK& rhs) = delete;
    gfxDescriptorPoolImplVK& operator=(const gfxDescriptorPoolImplVK& rhs) = delete;
    gfxDescriptorPoolImplVK(gfxDescriptorPoolImplVK&& rhs) = default;
    gfxDescriptorPoolImplVK& operator=(gfxDescriptorPoolImplVK&& rhs) = default;
    ~gfxDescriptorPoolImplVK() override;

    epiBool Init(const gfxDescriptorPoolCreateInfo& info, const epiPtrArray<const gfxDescriptorSetLayoutImplVK>& descriptorSetLayoutImpls);

    VkDescriptorPool_T* GetVkDescriptorPool() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkDescriptorPool_T* m_VkDescriptorPool{nullptr};
};

} // namespace internalgfx

EPI_NAMESPACE_END()
