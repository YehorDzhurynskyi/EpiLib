#include "EpiGraphicsDriverVK/gfxPipelineLayoutImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxDescriptorSetLayoutImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxPipelineLayoutImplVK::gfxPipelineLayoutImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

gfxPipelineLayoutImplVK::~gfxPipelineLayoutImplVK()
{
    vkDestroyPipelineLayout(m_VkDevice, m_VkPipelineLayout, nullptr);
}

epiBool gfxPipelineLayoutImplVK::Init(const gfxPipelineLayoutCreateInfo& info)
{
    const epiBool layoutsAreValid = std::all_of(info.GetDescriptorSetLayouts().begin(),
                                                info.GetDescriptorSetLayouts().end(),
                                                [](const gfxDescriptorSetLayout& layout)
    {
        return layout.HasImpl();
    });

    if (!layoutsAreValid)
    {
        epiLogError("Failed to Init PipelineLayout! Some of the provided DescriptorSetLayout has no implementation!");
        return false;
    }

    std::vector<VkDescriptorSetLayout> layouts;
    layouts.reserve(info.GetDescriptorSetLayouts().Size());

    std::transform(info.GetDescriptorSetLayouts().begin(),
                   info.GetDescriptorSetLayouts().end(),
                   std::back_inserter(layouts),
                   [](const gfxDescriptorSetLayout& layout)
    {
        const gfxDescriptorSetLayoutImplVK* layoutVk = static_cast<const gfxDescriptorSetLayoutImplVK*>(gfxDescriptorSetLayout::Impl::ExtractImpl(layout));
        epiAssert(layoutVk != nullptr);

        return layoutVk->GetVkDescriptorSetLayout();
    });

    // TODO: configure through gfxPipelineCreateInfo
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = layouts.size();
    pipelineLayoutInfo.pSetLayouts = layouts.data();
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;

    if (const VkResult result = vkCreatePipelineLayout(m_VkDevice, &pipelineLayoutInfo, nullptr, &m_VkPipelineLayout); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreatePipelineLayout!");
        return false;
    }

    return true;
}

VkPipelineLayout gfxPipelineLayoutImplVK::GetVkPipelineLayout() const
{
    return m_VkPipelineLayout;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
