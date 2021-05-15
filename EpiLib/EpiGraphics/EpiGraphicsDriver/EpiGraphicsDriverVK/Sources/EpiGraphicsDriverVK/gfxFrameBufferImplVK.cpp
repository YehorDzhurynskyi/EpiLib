#include "EpiGraphicsDriverVK/gfxFrameBufferImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"
#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"
#include "EpiGraphicsDriverVK/gfxTextureViewImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxFrameBufferImplVK::gfxFrameBufferImplVK(VkDevice_T* device)
    : m_VkDevice{device}
{
}

epiBool gfxFrameBufferImplVK::Init(const gfxFrameBufferCreateInfo& info, const gfxRenderPassImpl& renderPassImpl, const epiPtrArray<const gfxTextureViewImpl>& textureViewImpls)
{
    std::vector<VkImageView> attachments;
    attachments.reserve(textureViewImpls.Size());

    std::transform(textureViewImpls.begin(), textureViewImpls.end(), std::back_inserter(attachments), [](const gfxTextureViewImpl* impl)
    {
        return static_cast<const gfxTextureViewImplVK*>(impl)->GetVkImageView();
    });

    // TODO: add renderpass compatibility check
    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = static_cast<const gfxRenderPassImplVK&>(renderPassImpl).GetVkRenderPass();
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

} // namespace internalgfx

EPI_NAMESPACE_END()
