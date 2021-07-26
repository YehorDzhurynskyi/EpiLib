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
#include "EpiGraphicsDriverVK/gfxTextureImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

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

void gfxCommandBufferImplVK::RenderPassBegin(const gfxRenderPassBeginInfo& info)
{
    if (!info.GetRenderPass().HasImpl())
    {
        epiLogError("Failed to begin RenderPass! Provided RenderPass has no implementation!");
        return;
    }

    if (!info.GetFrameBuffer().HasImpl())
    {
        epiLogError("Failed to begin RenderPass! Provided FrameBuffer has no implementation!");
        return;
    }

    const internalgfx::gfxRenderPassImplVK* renderPassImpl = static_cast<const internalgfx::gfxRenderPassImplVK*>(internalgfx::gfxRenderPassImpl::ExtractImpl(info.GetRenderPass()));
    epiAssert(renderPassImpl != nullptr);

    const gfxFrameBufferImplVK* frameBufferImpl = static_cast<const gfxFrameBufferImplVK*>(gfxFrameBuffer::Impl::ExtractImpl(info.GetFrameBuffer()));
    epiAssert(frameBufferImpl != nullptr);

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPassImpl->GetVkRenderPass();
    renderPassInfo.framebuffer = frameBufferImpl->GetVkFrameBuffer();

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

        cv.depthStencil.depth = clearValue.GetDepth();
        cv.depthStencil.stencil = clearValue.GetStencil();
    }

    renderPassInfo.clearValueCount = clearValues.size();
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(m_VkCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE); // TODO: handle other option with a secondary buffers
}

void gfxCommandBufferImplVK::RenderPassEnd()
{
    vkCmdEndRenderPass(m_VkCommandBuffer);
}

void gfxCommandBufferImplVK::PipelineBind(const gfxPipelineGraphics& pipeline)
{
    if (!pipeline.HasImpl())
    {
        epiLogError("Failed to bind Pipeline! The provided Pipeline has no implementation!");
        return;
    }

    const internalgfx::gfxPipelineGraphicsImplVK* pipelineImpl = static_cast<const internalgfx::gfxPipelineGraphicsImplVK*>(internalgfx::gfxPipelineGraphicsImpl::ExtractImpl(pipeline));
    epiAssert(pipelineImpl != nullptr);

    vkCmdBindPipeline(m_VkCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineImpl->GetVkPipeline());

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

void gfxCommandBufferImplVK::PipelineBarrier(const gfxCommandBufferRecordPipelineBarier& pipelineBarrier)
{
    std::vector<VkMemoryBarrier> memoryBarriers;
    memoryBarriers.reserve(pipelineBarrier.GetMemoryBarriers().Size());

    std::vector<VkBufferMemoryBarrier> bufferMemoryBarriers;
    bufferMemoryBarriers.reserve(pipelineBarrier.GetBufferMemoryBarriers().Size());

    std::vector<VkImageMemoryBarrier> imageMemoryBarriers;
    imageMemoryBarriers.reserve(pipelineBarrier.GetImageMemoryBarriers().Size());

    std::transform(pipelineBarrier.GetMemoryBarriers().begin(),
                   pipelineBarrier.GetMemoryBarriers().end(),
                   std::back_inserter(memoryBarriers),
                   [](const gfxMemoryBarrier& barrier)
    {
        VkMemoryBarrier barrierVk{};
        barrierVk.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
        barrierVk.srcAccessMask = gfxAccessTo(barrier.GetSrcAccessMask());
        barrierVk.dstAccessMask = gfxAccessTo(barrier.GetDstAccessMask());

        return barrierVk;
    });

    std::transform(pipelineBarrier.GetBufferMemoryBarriers().begin(),
                   pipelineBarrier.GetBufferMemoryBarriers().end(),
                   std::back_inserter(bufferMemoryBarriers),
                   [](const gfxBufferMemoryBarrier& barrier)
    {
        const gfxBufferImplVK* bufferImpl = static_cast<const gfxBufferImplVK*>(gfxBuffer::Impl::ExtractImpl(barrier.GetBuffer()));
        epiAssert(bufferImpl != nullptr);

        VkBufferMemoryBarrier barrierVk{};
        barrierVk.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
        barrierVk.srcAccessMask = gfxAccessTo(barrier.GetSrcAccessMask());
        barrierVk.dstAccessMask = gfxAccessTo(barrier.GetDstAccessMask());
        barrierVk.srcQueueFamilyIndex = barrier.GetIsSrcQueueFamilyIndexIgnored() ? VK_QUEUE_FAMILY_IGNORED : barrier.GetSrcQueueFamilyIndex();
        barrierVk.dstQueueFamilyIndex = barrier.GetIsDstQueueFamilyIndexIgnored() ? VK_QUEUE_FAMILY_IGNORED : barrier.GetDstQueueFamilyIndex();
        barrierVk.buffer = bufferImpl->GetVkBuffer();
        barrierVk.offset = barrier.GetOffset();
        barrierVk.size = barrier.GetSize();

        return barrierVk;
    });

    std::transform(pipelineBarrier.GetImageMemoryBarriers().begin(),
                   pipelineBarrier.GetImageMemoryBarriers().end(),
                   std::back_inserter(imageMemoryBarriers),
                   [](const gfxImageMemoryBarrier& barrier)
    {
        const internalgfx::gfxTextureImplVK* imageImpl = static_cast<const internalgfx::gfxTextureImplVK*>(internalgfx::gfxTextureImpl::ExtractImpl(barrier.GetImage()));
        epiAssert(imageImpl != nullptr);

        VkImageMemoryBarrier barrierVk{};
        barrierVk.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrierVk.srcAccessMask = gfxAccessTo(barrier.GetSrcAccessMask());
        barrierVk.dstAccessMask = gfxAccessTo(barrier.GetDstAccessMask());
        barrierVk.oldLayout = gfxImageLayoutTo(barrier.GetOldLayout());
        barrierVk.newLayout = gfxImageLayoutTo(barrier.GetNewLayout());;
        barrierVk.srcQueueFamilyIndex = barrier.GetIsSrcQueueFamilyIndexIgnored() ? VK_QUEUE_FAMILY_IGNORED : barrier.GetSrcQueueFamilyIndex();
        barrierVk.dstQueueFamilyIndex = barrier.GetIsDstQueueFamilyIndexIgnored() ? VK_QUEUE_FAMILY_IGNORED : barrier.GetDstQueueFamilyIndex();
        barrierVk.image = imageImpl->GetVkImage();
        barrierVk.subresourceRange.aspectMask = gfxImageAspectTo(barrier.GetSubresourceRange().GetAspectMask());
        barrierVk.subresourceRange.baseArrayLayer = barrier.GetSubresourceRange().GetBaseArrayLayer();
        barrierVk.subresourceRange.baseMipLevel = barrier.GetSubresourceRange().GetBaseMipLevel();
        barrierVk.subresourceRange.layerCount = barrier.GetSubresourceRange().GetLayerCount();
        barrierVk.subresourceRange.levelCount = barrier.GetSubresourceRange().GetLevelCount();

        return barrierVk;
    });

    vkCmdPipelineBarrier(m_VkCommandBuffer,
                         gfxPipelineStageTo(pipelineBarrier.GetSrcStageMask()),
                         gfxPipelineStageTo(pipelineBarrier.GetDstStageMask()),
                         gfxDependencyTo(pipelineBarrier.GetDependencyFlags()),
                         memoryBarriers.size(),
                         memoryBarriers.data(),
                         bufferMemoryBarriers.size(),
                         bufferMemoryBarriers.data(),
                         imageMemoryBarriers.size(),
                         imageMemoryBarriers.data());
}

void gfxCommandBufferImplVK::VertexBuffersBind(const epiArray<gfxBuffer>& buffers, const epiArray<epiU32>& offsets)
{
    std::vector<VkBuffer> buffersVk;
    buffersVk.reserve(buffers.Size());

    const epiBool allBuffersAreValid = std::all_of(buffers.begin(), buffers.end(), [](const gfxBuffer& buffer)
    {
        return buffer.HasImpl();
    });

    if (!allBuffersAreValid)
    {
        epiLogError("Failed to bind vertex Buffers! Some of the provided Buffers have no implementation!");
        return;
    }

    std::transform(buffers.begin(), buffers.end(), std::back_inserter(buffersVk), [](const gfxBuffer& buffer)
    {
        const gfxBufferImplVK* bufferImpl = static_cast<const gfxBufferImplVK*>(gfxBuffer::Impl::ExtractImpl(buffer));
        epiAssert(bufferImpl != nullptr);

        return bufferImpl->GetVkBuffer();
    });

    std::vector<VkDeviceSize> offsetsVk(buffersVk.size(), 0);
    for (epiU32 i = 0; i < offsets.Size(); ++i)
    {
        offsetsVk[i] = offsets[i];
    }

    vkCmdBindVertexBuffers(m_VkCommandBuffer, 0, buffersVk.size(), buffersVk.data(), offsetsVk.data());
}

void gfxCommandBufferImplVK::IndexBufferBind(const gfxBuffer& buffer, gfxIndexBufferType type, epiU32 offset)
{
    if (!buffer.HasImpl())
    {
        epiLogError("Failed to bind index Buffer! The provided Buffer has no implementation!");
        return;
    }

    const gfxBufferImplVK* bufferImpl = static_cast<const gfxBufferImplVK*>(gfxBuffer::Impl::ExtractImpl(buffer));
    epiAssert(bufferImpl != nullptr);

    vkCmdBindIndexBuffer(m_VkCommandBuffer, bufferImpl->GetVkBuffer(), offset, gfxIndexBufferTypeTo(type));
}

void gfxCommandBufferImplVK::DescriptorSetsBind(gfxPipelineBindPoint bindPoint,
                                                const gfxPipelineLayout& pipelineLayout,
                                                const epiArray<gfxDescriptorSet>& sets,
                                                const epiArray<epiU32>& offsets,
                                                epiU32 firstSet)
{
    const internalgfx::gfxPipelineLayoutImplVK* pipelineLayoutVk = static_cast<const internalgfx::gfxPipelineLayoutImplVK*>(internalgfx::gfxPipelineLayoutImpl::ExtractImpl(pipelineLayout));
    if (pipelineLayoutVk == nullptr)
    {
        epiLogError("Failed to Bind DescriptorSets! Provided PipelineLayout has no implementation!");
        return;
    }

    const epiBool setsAreValid = std::all_of(sets.begin(), sets.end(), [](const gfxDescriptorSet& set)
    {
        return set.HasImpl();
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
        return static_cast<const gfxDescriptorSetImplVK*>(gfxDescriptorSet::Impl::ExtractImpl(set))->GetVkDescriptorSet();
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

void gfxCommandBufferImplVK::Copy(const gfxBuffer& src, const gfxBuffer& dst, const epiArray<gfxCommandBufferRecordCopyRegion>& copyRegions)
{
    if (!src.HasImpl())
    {
        epiLogError("Failed to copy Buffer! The provided source Buffer has no implementation!");
        return;
    }

    if (!dst.HasImpl())
    {
        epiLogError("Failed to copy Buffer! The provided destination Buffer has no implementation!");
        return;
    }

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

    const gfxBufferImplVK* srcImpl = static_cast<const gfxBufferImplVK*>(gfxBuffer::Impl::ExtractImpl(src));
    epiAssert(srcImpl != nullptr);

    const gfxBufferImplVK* dstImpl = static_cast<const gfxBufferImplVK*>(gfxBuffer::Impl::ExtractImpl(dst));
    epiAssert(dstImpl != nullptr);

    vkCmdCopyBuffer(m_VkCommandBuffer,
                    srcImpl->GetVkBuffer(),
                    dstImpl->GetVkBuffer(),
                    copyRegionsVk.size(),
                    copyRegionsVk.data());
}

void gfxCommandBufferImplVK::Copy(const gfxBuffer& src, const gfxTexture& dst, gfxImageLayout dstLayout, const epiArray<gfxCommandBufferRecordCopyBufferToImage>& copyRegions)
{
    const gfxBufferImplVK* bufferImpl = static_cast<const gfxBufferImplVK*>(gfxBuffer::Impl::ExtractImpl(src));
    epiAssert(bufferImpl != nullptr);

    const internalgfx::gfxTextureImplVK* imageImpl = static_cast<const internalgfx::gfxTextureImplVK*>(internalgfx::gfxTextureImpl::ExtractImpl(dst));
    epiAssert(imageImpl != nullptr);

    std::vector<VkBufferImageCopy> regions;
    regions.reserve(copyRegions.Size());

    std::transform(copyRegions.begin(), copyRegions.end(), std::back_inserter(regions), [](const gfxCommandBufferRecordCopyBufferToImage& region)
    {
        const VkOffset3D offsetVk{region.GetImageOffset().x, region.GetImageOffset().y, region.GetImageOffset().z};
        const VkExtent3D extentVk{region.GetImageExtent().x, region.GetImageExtent().y, region.GetImageExtent().z};

        VkBufferImageCopy regionVk{};
        regionVk.bufferOffset = region.GetBufferOffset();
        regionVk.bufferRowLength = region.GetBufferRowLength();
        regionVk.bufferImageHeight = region.GetBufferImageHeight();
        regionVk.imageSubresource.aspectMask = gfxImageAspectTo(region.GetImageSubresource().GetAspectMask());
        regionVk.imageSubresource.mipLevel = region.GetImageSubresource().GetMipLevel();
        regionVk.imageSubresource.baseArrayLayer = region.GetImageSubresource().GetBaseArrayLayer();
        regionVk.imageSubresource.layerCount = region.GetImageSubresource().GetLayerCount();
        regionVk.imageOffset = offsetVk;
        regionVk.imageExtent = extentVk;

        return regionVk;
    });

    vkCmdCopyBufferToImage(m_VkCommandBuffer, bufferImpl->GetVkBuffer(), imageImpl->GetVkImage(), gfxImageLayoutTo(dstLayout), regions.size(), regions.data());
}

VkCommandBuffer gfxCommandBufferImplVK::GetVkCommandBuffer() const
{
    return m_VkCommandBuffer;
}

EPI_NAMESPACE_END()
