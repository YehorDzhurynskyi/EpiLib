#pragma once

#include "EpiGraphics/gfxDriverInternal.h"

#include "EpiGraphicsImplVK/gfxDescriptorSetLayoutImplVK.h"

struct VkDevice_T;
struct VkDescriptorPool_T;

EPI_NAMESPACE_BEGIN()

class gfxDescriptorPoolImplVK : public gfxDescriptorPool::Impl
{
public:
    explicit gfxDescriptorPoolImplVK(VkDevice_T* device);
    gfxDescriptorPoolImplVK(const gfxDescriptorPoolImplVK& rhs) = delete;
    gfxDescriptorPoolImplVK& operator=(const gfxDescriptorPoolImplVK& rhs) = delete;
    gfxDescriptorPoolImplVK(gfxDescriptorPoolImplVK&& rhs) = default;
    gfxDescriptorPoolImplVK& operator=(gfxDescriptorPoolImplVK&& rhs) = default;
    ~gfxDescriptorPoolImplVK() override;

    epiBool Init(const gfxDescriptorPoolCreateInfo& info);

    VkDescriptorPool_T* GetVkDescriptorPool() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkDescriptorPool_T* m_VkDescriptorPool{nullptr};
};

EPI_NAMESPACE_END()
