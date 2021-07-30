#include "EpiGraphicsImplVK/gfxFrameBufferImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"
#include "EpiGraphicsImplVK/gfxRenderPassImplVK.h"
#include "EpiGraphicsImplVK/gfxImageViewImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxFrameBufferImplVK::gfxFrameBufferImplVK(VkDevice_T* device)
    : m_VkDevice{device}
{
}

epiBool gfxFrameBufferImplVK::Init(const gfxFrameBufferCreateInfo& info)
{
    if (!info.GetRenderPass().HasImpl())
    {
        epiLogError("Failed to initialize FrameBuffer! The provided RenderPass has no implementation!");
        return false;
    }

    std::vector<VkImageView> attachments;
    attachments.reserve(info.GetAttachments().Size());

    std::transform(info.GetAttachments().begin(),
                   info.GetAttachments().end(),
                   std::back_inserter(attachments),
                   [](const gfxImageView& attachment)
    {
        const gfxImageViewImplVK* attachmentVk = static_cast<const gfxImageViewImplVK*>(gfxImageView::Impl::ExtractImpl(attachment));
        epiAssert(attachmentVk != nullptr);

        return attachmentVk->GetVkImageView();
    });

    const gfxRenderPassImplVK* renderPassVk = static_cast<const gfxRenderPassImplVK*>(gfxRenderPass::Impl::ExtractImpl(info.GetRenderPass()));
    epiAssert(renderPassVk != nullptr);

    // TODO: add renderpass compatibility check
    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPassVk->GetVkRenderPass();
    framebufferInfo.attachmentCount = attachments.size();
    framebufferInfo.pAttachments = attachments.data();
    framebufferInfo.width = info.GetSize().x;
    framebufferInfo.height = info.GetSize().y;
    framebufferInfo.layers = 1;

    if (const VkResult result = vkCreateFramebuffer(m_VkDevice, &framebufferInfo, nullptr, &m_VkFrameBuffer); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateFramebuffer!");
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

EPI_NAMESPACE_END()
