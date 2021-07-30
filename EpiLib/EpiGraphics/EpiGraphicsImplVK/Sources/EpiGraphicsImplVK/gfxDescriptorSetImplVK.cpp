#include "EpiGraphicsImplVK/gfxDescriptorSetImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxDescriptorSetImplVK::gfxDescriptorSetImplVK(VkDescriptorSet descriptorSet)
    : m_VkDescriptorSet{descriptorSet}
{
}

VkDescriptorSet gfxDescriptorSetImplVK::GetVkDescriptorSet() const
{
    return m_VkDescriptorSet;
}

EPI_NAMESPACE_END()
