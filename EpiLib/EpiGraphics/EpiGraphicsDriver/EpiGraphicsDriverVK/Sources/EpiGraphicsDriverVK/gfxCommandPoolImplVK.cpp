#include "EpiGraphicsDriverVK/gfxCommandPoolImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxFrameBufferImplVK.h"
#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxCommandBufferImplVK::gfxCommandBufferImplVK(VkCommandBuffer commandBuffer, epiBool isPrimary)
    : m_VkCommandBuffer{commandBuffer}
    , m_IsPrimary{isPrimary}
{
}

epiBool gfxCommandBufferImplVK::GetIsPrimary() const
{
    return m_IsPrimary;
}

epiBool gfxCommandBufferImplVK::RenderPassBegin(const gfxRenderPassBeginInfo& info, const gfxRenderPassImpl& renderPassImpl, const gfxFrameBufferImpl& frameBufferImpl) const
{
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0; // TODO: configure
    beginInfo.pInheritanceInfo = nullptr;

    if (const VkResult result = vkBeginCommandBuffer(m_VkCommandBuffer, &beginInfo); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkBeginCommandBuffer!");
        return false;
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = static_cast<const gfxRenderPassImplVK&>(renderPassImpl).GetVkRenderPass();
    renderPassInfo.framebuffer = static_cast<const gfxFrameBufferImplVK&>(frameBufferImpl).GetVkFrameBuffer();

    const epiRect2s& renderArea = info.GetRenderArea();
    renderPassInfo.renderArea.offset.x = renderArea.LeftTop().x;
    renderPassInfo.renderArea.offset.y = renderArea.LeftTop().y;
    renderPassInfo.renderArea.extent.width = renderArea.GetWidth();
    renderPassInfo.renderArea.extent.height = renderArea.GetHeight();

    std::vector<VkClearValue> clearValues;
    clearValues.reserve(info.GetClearValues().Size());

    for (const gfxRenderPassClearValue& clearValue : info.GetClearValues())
    {
        VkClearValue& cv = clearValues.emplace_back();
        cv.color.float32[0] = clearValue.GetColor().r;
        cv.color.float32[1] = clearValue.GetColor().g;
        cv.color.float32[2] = clearValue.GetColor().b;
        cv.color.float32[3] = clearValue.GetColor().a;

        cv.depthStencil.stencil = clearValue.GetStencil();
        cv.depthStencil.depth = clearValue.GetDepth();
    }

    renderPassInfo.clearValueCount = clearValues.size();
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(m_VkCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE); // TODO: handle other option with a secondary buffers

    return true;
}

epiBool gfxCommandBufferImplVK::RenderPassEnd() const
{
    vkCmdEndRenderPass(m_VkCommandBuffer);

    if (const VkResult result = vkEndCommandBuffer(m_VkCommandBuffer); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkEndCommandBuffer!");
        return false;
    }

    return true;
}

VkCommandBuffer gfxCommandBufferImplVK::GetVkCommandBuffer() const
{
    return m_VkCommandBuffer;
}

gfxCommandPoolImplVK::gfxCommandPoolImplVK(VkDevice device)
    : m_VkDevice{device}
{
}

gfxCommandPoolImplVK::~gfxCommandPoolImplVK()
{
    vkDestroyCommandPool(m_VkDevice, m_VkCommandPool, nullptr);

    if (!m_PrimaryCommandBuffers.IsEmpty())
    {
        std::vector<VkCommandBuffer> primaryCommandBuffers;
        primaryCommandBuffers.reserve(m_PrimaryCommandBuffers.Size());

        std::transform(m_PrimaryCommandBuffers.begin(),
                       m_PrimaryCommandBuffers.end(),
                       std::back_inserter(primaryCommandBuffers),
                       [](const std::shared_ptr<gfxCommandBufferImpl>& commandBuffer)
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
                       [](const std::shared_ptr<gfxCommandBufferImpl>& commandBuffer)
        {
            const gfxCommandBufferImplVK* commandBufferVk = static_cast<const gfxCommandBufferImplVK*>(commandBuffer.get());
            return commandBufferVk->GetVkCommandBuffer();
        });

        vkFreeCommandBuffers(m_VkDevice, m_VkCommandPool, secondaryCommandBuffers.size(), secondaryCommandBuffers.data());
    }
}

epiBool gfxCommandPoolImplVK::Init(const gfxCommandPoolCreateInfo& info, const gfxQueueFamilyImpl& queueFamilyImpl)
{
    const gfxQueueFamilyImplVK& queueFamilyImplVk = static_cast<const gfxQueueFamilyImplVK&>(queueFamilyImpl);
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyImplVk.GetIndex();
    poolInfo.flags = 0; // TODO: configure via gfxCommandPoolCreateInfo

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

} // namespace internalgfx

EPI_NAMESPACE_END()
