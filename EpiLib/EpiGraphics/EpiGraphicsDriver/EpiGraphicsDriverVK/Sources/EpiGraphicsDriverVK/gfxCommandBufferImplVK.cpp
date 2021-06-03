#include "EpiGraphicsDriverVK/gfxCommandBufferImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"
#include "EpiGraphicsDriverVK/gfxQueueFamilyImplVK.h"
#include "EpiGraphicsDriverVK/gfxFrameBufferImplVK.h"
#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"
#include "EpiGraphicsDriverVK/gfxPipelineLayoutImplVK.h"
#include "EpiGraphicsDriverVK/gfxPipelineImplVK.h"
#include "EpiGraphicsDriverVK/gfxDescriptorSetImplVK.h"
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

epiBool gfxCommandBufferImplVK::RecordBegin(gfxCommandBufferUsage usage)
{
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = gfxCommandBufferUsageTo(usage);
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

void gfxCommandBufferImplVK::IndexBufferBind(const gfxBufferImpl& bufferImpl, gfxIndexBufferType type, epiU32 offset)
{
    vkCmdBindIndexBuffer(m_VkCommandBuffer, static_cast<const gfxBufferImplVK&>(bufferImpl).GetVkBuffer(), offset, gfxIndexBufferTypeTo(type));
}

void gfxCommandBufferImplVK::DescriptorSetsBind(gfxPipelineBindPoint bindPoint,
                                                const gfxPipelineLayout& pipelineLayout,
                                                const epiArray<gfxDescriptorSet>& sets,
                                                const epiArray<epiU32>& offsets,
                                                epiU32 firstSet)
{
    const gfxPipelineLayoutImplVK* pipelineLayoutVk = static_cast<const gfxPipelineLayoutImplVK*>(gfxPipelineLayoutImpl::ExtractImpl(pipelineLayout));
    if (pipelineLayoutVk == nullptr)
    {
        epiLogError("Failed to Bind DescriptorSets! Provided PipelineLayout has no implementation!");
        return;
    }

    const epiBool setsAreValid = std::all_of(sets.begin(), sets.end(), [](const gfxDescriptorSet& set)
    {
        return gfxDescriptorSetImpl::ExtractImpl(set) != nullptr;
    });

    if (!setsAreValid)
    {
        epiLogError("Failed to Bind DescriptorSets! Some of the provided DescriptorSet has no implementation!");
        return;
    }

    std::vector<VkDescriptorSet> descriptorSets;
    descriptorSets.reserve(sets.GetSize());

    std::transform(sets.begin(), sets.end(), std::back_inserter(descriptorSets), [](const gfxDescriptorSet& set)
    {
        return static_cast<const gfxDescriptorSetImplVK*>(gfxDescriptorSetImpl::ExtractImpl(set))->GetVkDescriptorSet();
    });

    vkCmdBindDescriptorSets(m_VkCommandBuffer,
                            gfxPipelineBindPointTo(bindPoint),
                            pipelineLayoutVk->GetVkPipelineLayout(),
                            firstSet,
                            descriptorSets.size(),
                            descriptorSets.data(),
                            offsets.Size(),
                            offsets.data());
}

void gfxCommandBufferImplVK::Draw(epiU32 vertexCount, epiU32 instanceCount, epiU32 firstVertex, epiU32 firstInstance)
{
    vkCmdDraw(m_VkCommandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
}

void gfxCommandBufferImplVK::DrawIndexed(epiU32 indexCount, epiU32 instanceCount, epiU32 firstIndex, epiU32 vertexOffset, epiU32 firstInstance)
{
    vkCmdDrawIndexed(m_VkCommandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

void gfxCommandBufferImplVK::Copy(const gfxBufferImpl& src, const gfxBufferImpl& dst, const epiArray<gfxCommandBufferRecordCopyRegion>& copyRegions)
{
    std::vector<VkBufferCopy> copyRegionsVk;
    copyRegionsVk.reserve(copyRegions.Size());

    std::transform(copyRegions.begin(), copyRegions.end(), std::back_inserter(copyRegionsVk), [](const gfxCommandBufferRecordCopyRegion& copyRegion)
    {
        VkBufferCopy copyRegionVk{};
        copyRegionVk.size = copyRegion.GetSize();
        copyRegionVk.srcOffset = copyRegion.GetSrcOffset();
        copyRegionVk.dstOffset = copyRegion.GetDstOffset();

        return copyRegionVk;
    });

    vkCmdCopyBuffer(m_VkCommandBuffer,
                    static_cast<const gfxBufferImplVK&>(src).GetVkBuffer(),
                    static_cast<const gfxBufferImplVK&>(dst).GetVkBuffer(),
                    copyRegionsVk.size(),
                    copyRegionsVk.data());
}

VkCommandBuffer gfxCommandBufferImplVK::GetVkCommandBuffer() const
{
    return m_VkCommandBuffer;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
