#include "EpiGraphicsDriverVK/gfxFrameBufferImplVK.h"

#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"

#include "EpiGraphicsDriverVK/gfxEnumVK.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxFrameBufferImplVK::gfxFrameBufferImplVK(VkDevice_T* device)
    : m_VkDevice{device}
{
}

epiBool gfxFrameBufferImplVK::Init(const gfxFrameBufferCreateInfo& info, const gfxRenderPassImpl& renderPassImpl)
{
    std::vector<VkFramebufferAttachmentImageInfo> frameBufferAttachmentImageInfos;
    frameBufferAttachmentImageInfos.reserve(info.GetAttachmentImageInfos().Size());

    std::vector<std::vector<VkFormat>> frameBufferAttachmentFormats;
    frameBufferAttachmentFormats.reserve(info.GetAttachmentImageInfos().Size());

    for (const gfxFramebufferAttachmentImageInfo& attachmentInfo : info.GetAttachmentImageInfos())
    {
        VkFramebufferAttachmentImageInfo& attachment = frameBufferAttachmentImageInfos.emplace_back();
        attachment = {};
        attachment.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO;
        attachment.usage = gfxImageUsageTo(attachmentInfo.GetUsage());
        attachment.width = attachmentInfo.GetSize().x;
        attachment.height = attachmentInfo.GetSize().y;
        attachment.layerCount = attachmentInfo.GetLayerCount();

        std::vector<VkFormat>& formats = frameBufferAttachmentFormats.emplace_back();
        formats.reserve(attachmentInfo.GetFormats().Size());
        std::transform(attachmentInfo.GetFormats().begin(), attachmentInfo.GetFormats().end(), std::back_inserter(formats), [](const gfxFormat f) {
            return gfxFormatTo(f);
        });

        attachment.viewFormatCount = formats.size();
        attachment.pViewFormats = formats.data();
    }

    VkFramebufferAttachmentsCreateInfo frameBufferAttachmentsCreateInfo{};
    frameBufferAttachmentsCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO;
    frameBufferAttachmentsCreateInfo.attachmentImageInfoCount = frameBufferAttachmentImageInfos.size();
    frameBufferAttachmentsCreateInfo.pAttachmentImageInfos = frameBufferAttachmentImageInfos.data();

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.pNext = &frameBufferAttachmentsCreateInfo;
    framebufferInfo.flags = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT;
    framebufferInfo.renderPass = static_cast<const gfxRenderPassImplVK&>(renderPassImpl).GetVkRenderPass();
    framebufferInfo.attachmentCount = frameBufferAttachmentImageInfos.size();
    framebufferInfo.pAttachments = nullptr;
    framebufferInfo.width = info.GetSize().x;
    framebufferInfo.height = info.GetSize().y;
    framebufferInfo.layers = 1;

    if (vkCreateFramebuffer(m_VkDevice, &framebufferInfo, nullptr, &m_VkFrameBuffer) != VK_SUCCESS)
    {
        return false;
    }

    return true;
}

gfxFrameBufferImplVK::~gfxFrameBufferImplVK()
{
    vkDestroyFramebuffer(m_VkDevice, m_VkFrameBuffer, nullptr);
}

VkFramebuffer gfxFrameBufferImplVK::GetVkFrameBuffer() const
{
    return m_VkFrameBuffer;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
