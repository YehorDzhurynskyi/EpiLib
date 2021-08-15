#include "EpiGraphicsImplVK/gfxDescriptorPoolImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"
#include "EpiGraphicsImplVK/gfxDescriptorSetImplVK.h"
#include "EpiGraphicsImplVK/gfxDescriptorSetLayoutImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxDescriptorPoolImplVK::gfxDescriptorPoolImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

gfxDescriptorPoolImplVK::~gfxDescriptorPoolImplVK()
{
#if 0 // TODO: handle properly (see VUID-vkFreeDescriptorSets-descriptorPool-00312)
    if (!m_DescriptorSets.IsEmpty())
    {
        std::vector<VkDescriptorSet> descriptorSets;
        descriptorSets.reserve(m_DescriptorSets.Size());

        std::transform(m_DescriptorSets.begin(),
                       m_DescriptorSets.end(),
                       std::back_inserter(descriptorSets),
                       [](const std::shared_ptr<gfxDescriptorSetImpl>& descriptorSet)
        {
            const gfxDescriptorSetImplVK* descriptorSetVk = static_cast<const gfxDescriptorSetImplVK*>(descriptorSet.get());
            return descriptorSetVk->GetVkDescriptorSet();
        });

        if (const VkResult result = vkFreeDescriptorSets(m_VkDevice, m_VkDescriptorPool, descriptorSets.size(), descriptorSets.data()); result != VK_SUCCESS)
        {
            gfxLogErrorEx(result, "Failed to call vkFreeDescriptorSets!");
        }
    }
#endif

    vkDestroyDescriptorPool(m_VkDevice, m_VkDescriptorPool, nullptr);
}

epiBool gfxDescriptorPoolImplVK::Init(const gfxDescriptorPoolCreateInfo& info)
{
    std::vector<VkDescriptorPoolSize> poolSizes;
    poolSizes.reserve(info.GetPoolSizes().Size());

    std::transform(info.GetPoolSizes().begin(), info.GetPoolSizes().end(), std::back_inserter(poolSizes), [](const gfxDescriptorPoolSize& poolSize)
    {
        VkDescriptorPoolSize poolSizeVk{};
        poolSizeVk.type = gfxDescriptorTypeTo(poolSize.GetDescriptorType());
        poolSizeVk.descriptorCount = poolSize.GetDescriptorCount();

        return poolSizeVk;
    });

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.flags = gfxDescriptorPoolUsageTo(info.GetUsageMask());
    poolInfo.poolSizeCount = poolSizes.size();
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = info.GetMaxSets();

    if (const VkResult result = vkCreateDescriptorPool(m_VkDevice, &poolInfo, nullptr, &m_VkDescriptorPool); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkCreateDescriptorPool!");
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

    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = m_VkDescriptorPool;
    allocInfo.descriptorSetCount = layouts.size();
    allocInfo.pSetLayouts = layouts.data();

    std::vector<VkDescriptorSet> sets;
    sets.resize(layouts.size());

    if (const VkResult result = vkAllocateDescriptorSets(m_VkDevice, &allocInfo, sets.data()); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkAllocateDescriptorSets!");
        return false;
    }

    for (const VkDescriptorSet& set : sets)
    {
        m_DescriptorSets.push_back(std::make_unique<gfxDescriptorSetImplVK>(set));
    }

    return true;
}

VkDescriptorPool gfxDescriptorPoolImplVK::GetVkDescriptorPool() const
{
    return m_VkDescriptorPool;
}

EPI_NAMESPACE_END()
