#include "EpiGraphicsImplVK/gfxCommandPoolImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"
#include "EpiGraphicsImplVK/gfxCommandBufferImplVK.h"
#include "EpiGraphicsImplVK/gfxQueueFamilyImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxCommandPoolImplVK::gfxCommandPoolImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

gfxCommandPoolImplVK::~gfxCommandPoolImplVK()
{
    if (!m_PrimaryCommandBuffers.IsEmpty())
    {
        std::vector<VkCommandBuffer> primaryCommandBuffers;
        primaryCommandBuffers.reserve(m_PrimaryCommandBuffers.Size());

        std::transform(m_PrimaryCommandBuffers.begin(),
                       m_PrimaryCommandBuffers.end(),
                       std::back_inserter(primaryCommandBuffers),
                       [](const std::shared_ptr<gfxCommandBuffer::Impl>& commandBuffer)
        {
            const gfxCommandBufferImplVK* commandBufferVk = static_cast<const gfxCommandBufferImplVK*>(commandBuffer.get());
            return commandBufferVk->GetVkCommandBuffer();
        });

        vkFreeCommandBuffers(m_VkDevice, m_VkCommandPool, primaryCommandBuffers.size(), primaryCommandBuffers.data());
    }

    if (!m_SecondaryCommandBuffers.IsEmpty())
    {
        std::vector<VkCommandBuffer> secondaryCommandBuffers;
        secondaryCommandBuffers.reserve(m_SecondaryCommandBuffers.Size());

        std::transform(m_SecondaryCommandBuffers.begin(),
                       m_SecondaryCommandBuffers.end(),
                       std::back_inserter(secondaryCommandBuffers),
                       [](const std::shared_ptr<gfxCommandBuffer::Impl>& commandBuffer)
        {
            const gfxCommandBufferImplVK* commandBufferVk = static_cast<const gfxCommandBufferImplVK*>(commandBuffer.get());
            return commandBufferVk->GetVkCommandBuffer();
        });

        vkFreeCommandBuffers(m_VkDevice, m_VkCommandPool, secondaryCommandBuffers.size(), secondaryCommandBuffers.data());
    }

    vkDestroyCommandPool(m_VkDevice, m_VkCommandPool, nullptr);
}

epiBool gfxCommandPoolImplVK::Init(const gfxCommandPoolCreateInfo& info)
{
    // TODO: free cmd buffer independently if pool is able to
    // TODO: allocate cmd buffers independently from cmd pool initialization

    if (!info.GetQueueFamily().HasImpl())
    {
        epiLogError("Failed to init CommandPool! The provided QueueFamily has no implementation!");
        return false;
    }

    const gfxQueueFamilyImplVK* queueFamilyImplVk = static_cast<const gfxQueueFamilyImplVK*>(gfxQueueFamily::Impl::ExtractImpl(info.GetQueueFamily()));
    epiAssert(queueFamilyImplVk != nullptr);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyImplVk->GetIndex();
    poolInfo.flags = gfxCommandPoolUsageTo(info.GetUsage());

    if (const VkResult result = vkCreateCommandPool(m_VkDevice, &poolInfo, nullptr, &m_VkCommandPool); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateCommandPool!");
        return false;
    }

    if (epiU32 primaryBufferCount = info.GetPrimaryCommandBufferCount(); primaryBufferCount != 0)
    {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = m_VkCommandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = primaryBufferCount;

        std::vector<VkCommandBuffer> commandBuffers;
        commandBuffers.resize(primaryBufferCount);
        if (const VkResult result = vkAllocateCommandBuffers(m_VkDevice, &allocInfo, commandBuffers.data()); result != VK_SUCCESS)
        {
            gfxLogErrorEx(result, "Failed to call vkAllocateCommandBuffers!");
            return false;
        }

        constexpr epiBool kIsPrimary = true;
        for (const VkCommandBuffer& commandBuffer : commandBuffers)
        {
            m_PrimaryCommandBuffers.push_back(std::make_unique<gfxCommandBufferImplVK>(commandBuffer, kIsPrimary));
        }
    }

    if (epiU32 secondaryBufferCount = info.GetSecondaryCommandBufferCount(); secondaryBufferCount != 0)
    {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = m_VkCommandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
        allocInfo.commandBufferCount = secondaryBufferCount;

        std::vector<VkCommandBuffer> commandBuffers;
        commandBuffers.resize(secondaryBufferCount);
        if (const VkResult result = vkAllocateCommandBuffers(m_VkDevice, &allocInfo, commandBuffers.data()); result != VK_SUCCESS)
        {
            gfxLogErrorEx(result, "Failed to call vkAllocateCommandBuffers!");
            return false;
        }

        constexpr epiBool kIsPrimary = false;
        for (const VkCommandBuffer& commandBuffer : commandBuffers)
        {
            m_SecondaryCommandBuffers.push_back(std::make_unique<gfxCommandBufferImplVK>(commandBuffer, kIsPrimary));
        }
    }

    return true;
}

EPI_NAMESPACE_END()
