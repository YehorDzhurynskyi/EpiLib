#pragma once

#include "EpiGraphics/gfxDriverInternal.h"

struct VkDevice_T;
struct VkDescriptorSetLayout_T;

EPI_NAMESPACE_BEGIN()

class gfxDescriptorSetLayoutImplVK : public gfxDescriptorSetLayout::Impl
{
public:
    explicit gfxDescriptorSetLayoutImplVK(VkDevice_T* device);
    gfxDescriptorSetLayoutImplVK(const gfxDescriptorSetLayoutImplVK& rhs) = delete;
    gfxDescriptorSetLayoutImplVK& operator=(const gfxDescriptorSetLayoutImplVK& rhs) = delete;
    gfxDescriptorSetLayoutImplVK(gfxDescriptorSetLayoutImplVK&& rhs) = default;
    gfxDescriptorSetLayoutImplVK& operator=(gfxDescriptorSetLayoutImplVK&& rhs) = default;
    ~gfxDescriptorSetLayoutImplVK() override;

    epiBool Init(const gfxDescriptorSetLayoutCreateInfo& info);

    VkDescriptorSetLayout_T* GetVkDescriptorSetLayout() const;

protected:
    VkDevice_T* m_VkDevice{nullptr};
    VkDescriptorSetLayout_T* m_VkDescriptorSetLayout{nullptr};
};

EPI_NAMESPACE_END()
