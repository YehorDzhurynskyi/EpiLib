#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"

#include "EpiGraphicsDriverVK/gfxEnumVK.h"

#include <vulkan/vulkan.hpp>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxRenderPassImplVK::gfxRenderPassImplVK(VkDevice_T* device)
    : m_VkDevice{device}
{
}

epiBool gfxRenderPassImplVK::Init(const gfxRenderPassCreateInfo& info)
{
    std::vector<VkSubpassDescription> subpasses;
    subpasses.reserve(info.GetSubPasses().Size());

    std::vector<VkAttachmentDescription> attachments;
    for (const gfxRenderSubPass& subpass : info.GetSubPasses())
    {
        attachments.reserve(subpass.GetColorAttachments().Size());

        std::vector<VkAttachmentReference> colorAttachmentRefs;
        colorAttachmentRefs.reserve(subpass.GetColorAttachments().Size());

        for (const gfxAttachmentRef& ref : subpass.GetColorAttachments())
        {
            const gfxAttachment& attachment = ref.GetAttachment();

            VkAttachmentDescription& colorAttachment = attachments.emplace_back();
            colorAttachment = {};
            colorAttachment.format = gfxFormatTo(attachment.GetFormat());
            colorAttachment.samples = gfxSampleCountTo(attachment.GetSampleCount());
            colorAttachment.loadOp = gfxAttachmentLoadOpTo(attachment.GetLoadOp());
            colorAttachment.storeOp = gfxAttachmentStoreOpTo(attachment.GetStoreOp());
            colorAttachment.stencilLoadOp = gfxAttachmentLoadOpTo(attachment.GetStencilLoadOp());
            colorAttachment.stencilStoreOp = gfxAttachmentStoreOpTo(attachment.GetStencilStoreOp());
            colorAttachment.initialLayout = gfxImageLayoutTo(attachment.GetInitialLayout());
            colorAttachment.finalLayout = gfxImageLayoutTo(attachment.GetFinalLayout());

            VkAttachmentReference& colorAttachmentRef = colorAttachmentRefs.emplace_back();
            colorAttachmentRef = {};
            colorAttachmentRef.attachment = ref.GetAttachmentIndex();
            colorAttachmentRef.layout = gfxImageLayoutTo(ref.GetLayuot());
        }

        VkSubpassDescription& subpassDesc = subpasses.emplace_back();
        subpassDesc = {};
        subpassDesc.pipelineBindPoint = gfxPipelineBindPointTo(subpass.GetBindPoint());
        subpassDesc.colorAttachmentCount = colorAttachmentRefs.size();
        subpassDesc.pColorAttachments = colorAttachmentRefs.data();

        // TODO: handle other attachment types
    }

    std::vector<VkSubpassDependency> dependencies;
    dependencies.reserve(info.GetSubPassDependencies().Size());

    for (const gfxRenderSubPassDependency& dependency : info.GetSubPassDependencies())
    {
        VkSubpassDependency& dep = dependencies.emplace_back();
        dep = {};

        dep.srcSubpass = dependency.GetIsSrcSubPassExternal() ? VK_SUBPASS_EXTERNAL : dependency.GetSrcSubPass();
        dep.dstSubpass = dependency.GetIsDstSubPassExternal() ? VK_SUBPASS_EXTERNAL : dependency.GetDstSubPass();
        dep.srcStageMask = gfxPipelineStageTo(dependency.GetSrcStageMask());
        dep.dstStageMask = gfxPipelineStageTo(dependency.GetDstStageMask());
        dep.srcAccessMask = gfxAccessTo(dependency.GetSrcAccessMask());
        dep.dstAccessMask = gfxAccessTo(dependency.GetDstAccessMask());
        dep.dependencyFlags = gfxDependencyTo(dependency.GetDependencyFlags());
    }

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = attachments.size();
    renderPassInfo.pAttachments = attachments.data();
    renderPassInfo.subpassCount = subpasses.size();
    renderPassInfo.pSubpasses = subpasses.data();
    renderPassInfo.dependencyCount = dependencies.size();
    renderPassInfo.pDependencies = dependencies.data();

    if (vkCreateRenderPass(m_VkDevice, &renderPassInfo, nullptr, &m_VkRenderPass) != VK_SUCCESS)
    {
        return false;
    }

    return true;
}

gfxRenderPassImplVK::~gfxRenderPassImplVK()
{
    vkDestroyRenderPass(m_VkDevice, m_VkRenderPass, nullptr);
}

VkRenderPass gfxRenderPassImplVK::GetVkRenderPass() const
{
    return m_VkRenderPass;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
