#include "EpiGraphicsDriverVK/gfxDescriptorSetImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxDescriptorSetImplVK::gfxDescriptorSetImplVK(VkDescriptorSet descriptorSet)
    : m_VkDescriptorSet{descriptorSet}
{
}

VkDescriptorSet gfxDescriptorSetImplVK::GetVkDescriptorSet() const
{
    return m_VkDescriptorSet;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
