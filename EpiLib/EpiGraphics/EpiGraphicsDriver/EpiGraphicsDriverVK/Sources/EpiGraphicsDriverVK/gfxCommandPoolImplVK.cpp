#include "EpiGraphicsDriverVK/gfxCommandPoolImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxFrameBufferImplVK.h"
#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"
#include "EpiGraphicsDriverVK/gfxPipelineImplVK.h"
#include "EpiGraphicsDriverVK/gfxBufferImplVK.h"

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

epiBool gfxCommandBufferImplVK::RecordBegin()
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

    return true;
}

epiBool gfxCommandBufferImplVK::RecordEnd()
{
    if (const VkResult result = vkEndCommandBuffer(m_VkCommandBuffer); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkEndCommandBuffer!");
        return false;
    }

    return true;
}

void gfxCommandBufferImplVK::RenderPassBegin(const gfxRenderPassBeginInfo& info, const gfxRenderPassImpl& renderPassImpl, const gfxFrameBufferImpl& frameBufferImpl)
{
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = static_cast<const gfxRenderPassImplVK&>(renderPassImpl).GetVkRenderPass();
    renderPassInfo.framebuffer = static_cast<const gfxFrameBufferImplVK&>(frameBufferImpl).GetVkFrameBuffer();

    const epiRect2s& renderArea = info.GetRenderArea();
    renderPassInfo.renderArea.offset.x = renderArea.Left;
    renderPassInfo.renderArea.offset.y = renderArea.GetHeight() - renderArea.Top; // TODO: replace with an image space rect
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
}

void gfxCommandBufferImplVK::RenderPassEnd()
{
    vkCmdEndRenderPass(m_VkCommandBuffer);
}

void gfxCommandBufferImplVK::PipelineBind(const gfxPipelineGraphicsImpl& pipeline)
{
    vkCmdBindPipeline(m_VkCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, static_cast<const gfxPipelineGraphicsImplVK&>(pipeline).GetVkPipeline());

    const auto apply = [this, &pipeline](gfxPipelineDynamicState state)
    {
        switch (state)
        {
        case gfxPipelineDynamicState::Viewport:
        {
            std::vector<VkViewport> viewportsVk;
            viewportsVk.reserve(pipeline.GetViewports().Size());

            std::transform(pipeline.GetViewports().begin(),
                           pipeline.GetViewports().end(),
                           std::back_inserter(viewportsVk),
                           [](const gfxPipelineViewport& viewport)
            {
                VkViewport viewportVk;
                viewportVk.x = viewport.GetRect().Left;
                viewportVk.y = viewport.GetRect().GetHeight() - viewport.GetRect().Top; // TODO: replace with image space based rect
                viewportVk.width = viewport.GetRect().GetWidth();
                viewportVk.height = viewport.GetRect().GetHeight();
                viewportVk.minDepth = viewport.GetMinDepth();
                viewportVk.maxDepth = viewport.GetMaxDepth();

                return viewportVk;
            });

            vkCmdSetViewport(m_VkCommandBuffer, 0, viewportsVk.size(), viewportsVk.data());
        } break;
        case gfxPipelineDynamicState::Scissor:
        {
            std::vector<VkRect2D> scissorsVk;
            scissorsVk.reserve(pipeline.GetScissors().Size());

            std::transform(pipeline.GetScissors().begin(),
                           pipeline.GetScissors().end(),
                           std::back_inserter(scissorsVk),
                           [](const epiRect2s& scissor)
            {
                VkRect2D scissorVk;
                scissorVk.offset.x = scissor.Left;
                scissorVk.offset.y = scissor.GetHeight() - scissor.Top; // TODO: replace with image space based rect
                scissorVk.extent.width = scissor.GetWidth();
                scissorVk.extent.height = scissor.GetHeight();

                return scissorVk;
            });

            vkCmdSetScissor(m_VkCommandBuffer, 0, scissorsVk.size(), scissorsVk.data());
        } break;
        default: epiLogError("Unhandled case gfxPipelineDynamicState=`{}`!", state); break; // TODO: str repr
        }
    };

    for (epiU32 i = 0; i < static_cast<epiU32>(gfxPipelineDynamicState::COUNT); ++i)
    {
        const gfxPipelineDynamicState state = static_cast<gfxPipelineDynamicState>(i);
        if (!pipeline.IsDynamic(state))
        {
            continue;
        }

        apply(state);
    }
}

void gfxCommandBufferImplVK::VertexBuffersBind(const epiPtrArray<const gfxBufferImpl>& buffers, const epiArray<epiU32>& offsets)
{
    std::vector<VkBuffer> buffersVk;
    buffersVk.reserve(buffers.Size());

    std::transform(buffers.begin(), buffers.end(), std::back_inserter(buffersVk), [](const gfxBufferImpl* buffer)
    {
        return static_cast<const gfxBufferImplVK*>(buffer)->GetVkBuffer();
    });

    std::vector<VkDeviceSize> offsetsVk(buffersVk.size(), 0);
    for (epiU32 i = 0; i < offsets.Size(); ++i)
    {
        offsetsVk[i] = offsets[i];
    }

    vkCmdBindVertexBuffers(m_VkCommandBuffer, 0, buffersVk.size(), buffersVk.data(), offsetsVk.data());
}

void gfxCommandBufferImplVK::Draw(epiU32 vertexCount, epiU32 instanceCount, epiU32 firstVertex, epiU32 firstInstance)
{
    vkCmdDraw(m_VkCommandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
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

    vkDestroyCommandPool(m_VkDevice, m_VkCommandPool, nullptr);
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
