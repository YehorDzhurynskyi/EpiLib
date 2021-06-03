#include "EpiGraphicsDriverVK/gfxDescriptorSetLayoutImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxDescriptorSetLayoutImplVK::gfxDescriptorSetLayoutImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

gfxDescriptorSetLayoutImplVK::~gfxDescriptorSetLayoutImplVK()
{
    vkDestroyDescriptorSetLayout(m_VkDevice, m_VkDescriptorSetLayout, nullptr);
}

epiBool gfxDescriptorSetLayoutImplVK::Init(const gfxDescriptorSetLayoutCreateInfo& info)
{
    std::vector<VkDescriptorSetLayoutBinding> bindings;
    bindings.reserve(info.GetBindings().Size());

    std::transform(info.GetBindings().begin(),
                   info.GetBindings().end(),
                   std::back_inserter(bindings),
                   [](const gfxDescriptorSetLayoutBinding& binding)
    {
        VkDescriptorSetLayoutBinding bindingVk{};
        bindingVk.binding = binding.GetBinding();
        bindingVk.descriptorCount = binding.GetDescriptorCount();
        bindingVk.descriptorType = gfxDescriptorTypeTo(binding.GetDescriptorType());
        bindingVk.stageFlags = gfxShaderStageTo(binding.GetShaderStageMask());
        bindingVk.pImmutableSamplers = nullptr; // TODO: set

        return bindingVk;
    });

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.flags = gfxDescriptorSetLayoutUsageTo(info.GetUsageMask());
    layoutInfo.bindingCount = bindings.size();
    layoutInfo.pBindings = bindings.data();

    if (const VkResult result = vkCreateDescriptorSetLayout(m_VkDevice, &layoutInfo, nullptr, &m_VkDescriptorSetLayout); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateDescriptorSetLayout!");
        return false;
    }

    return true;
}

VkDescriptorSetLayout gfxDescriptorSetLayoutImplVK::GetVkDescriptorSetLayout() const
{
    return m_VkDescriptorSetLayout;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
