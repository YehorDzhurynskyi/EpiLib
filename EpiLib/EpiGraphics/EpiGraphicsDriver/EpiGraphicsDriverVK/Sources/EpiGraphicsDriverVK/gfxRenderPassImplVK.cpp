#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxRenderPassImplVK::gfxRenderPassImplVK(VkDevice_T* device)
    : m_VkDevice{device}
{
}

epiBool gfxRenderPassImplVK::Init(const gfxRenderPassCreateInfo& info)
{
    struct RenderSubpassInfo
    {
        VkSubpassDescription Subpass;
        std::vector<VkAttachmentReference> ColorAttachmentRefs;
        std::vector<VkAttachmentReference> DepthStencilAttachmentRefs;
    };

    std::vector<RenderSubpassInfo> subpasses;
    subpasses.reserve(info.GetSubPasses().Size());

    std::vector<VkAttachmentDescription> attachments;
    for (const gfxRenderSubPass& subpass : info.GetSubPasses())
    {
        attachments.reserve(subpass.GetAttachmentsColor().Size() + subpass.GetAttachmentsDepthStencil().Size());

        RenderSubpassInfo& subpassInfo = subpasses.emplace_back();
        subpassInfo = {};
        subpassInfo.Subpass.pipelineBindPoint = gfxPipelineBindPointTo(subpass.GetBindPoint());

        subpassInfo.ColorAttachmentRefs.reserve(subpass.GetAttachmentsColor().Size());
        for (const gfxAttachmentRef& ref : subpass.GetAttachmentsColor())
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

            VkAttachmentReference& colorAttachmentRef = subpassInfo.ColorAttachmentRefs.emplace_back();
            colorAttachmentRef = {};
            colorAttachmentRef.attachment = ref.GetAttachmentIndex();
            colorAttachmentRef.layout = gfxImageLayoutTo(ref.GetLayuot());
        }

        subpassInfo.Subpass.colorAttachmentCount = subpassInfo.ColorAttachmentRefs.size();
        subpassInfo.Subpass.pColorAttachments = subpassInfo.ColorAttachmentRefs.data();

        subpassInfo.DepthStencilAttachmentRefs.reserve(subpass.GetAttachmentsDepthStencil().Size());
        for (const gfxAttachmentRef& ref : subpass.GetAttachmentsDepthStencil())
        {
            const gfxAttachment& attachment = ref.GetAttachment();

            VkAttachmentDescription& depthStencilAttachment = attachments.emplace_back();
            depthStencilAttachment = {};
            depthStencilAttachment.format = gfxFormatTo(attachment.GetFormat());
            depthStencilAttachment.samples = gfxSampleCountTo(attachment.GetSampleCount());
            depthStencilAttachment.loadOp = gfxAttachmentLoadOpTo(attachment.GetLoadOp());
            depthStencilAttachment.storeOp = gfxAttachmentStoreOpTo(attachment.GetStoreOp());
            depthStencilAttachment.stencilLoadOp = gfxAttachmentLoadOpTo(attachment.GetStencilLoadOp());
            depthStencilAttachment.stencilStoreOp = gfxAttachmentStoreOpTo(attachment.GetStencilStoreOp());
            depthStencilAttachment.initialLayout = gfxImageLayoutTo(attachment.GetInitialLayout());
            depthStencilAttachment.finalLayout = gfxImageLayoutTo(attachment.GetFinalLayout());

            VkAttachmentReference& depthStencilAttachmentRef = subpassInfo.DepthStencilAttachmentRefs.emplace_back();
            depthStencilAttachmentRef = {};
            depthStencilAttachmentRef.attachment = ref.GetAttachmentIndex();
            depthStencilAttachmentRef.layout = gfxImageLayoutTo(ref.GetLayuot());
        }

        subpassInfo.Subpass.pDepthStencilAttachment = subpassInfo.DepthStencilAttachmentRefs.data();
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

    std::vector<VkSubpassDescription> vkSubpasses;
    vkSubpasses.reserve(subpasses.size());

    std::transform(subpasses.begin(), subpasses.end(), std::back_inserter(vkSubpasses), [](const RenderSubpassInfo& subpassInfo)
    {
        return subpassInfo.Subpass;
    });

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = attachments.size();
    renderPassInfo.pAttachments = attachments.data();
    renderPassInfo.subpassCount = vkSubpasses.size();
    renderPassInfo.pSubpasses = vkSubpasses.data();
    renderPassInfo.dependencyCount = dependencies.size();
    renderPassInfo.pDependencies = dependencies.data();

    if (const VkResult result = vkCreateRenderPass(m_VkDevice, &renderPassInfo, nullptr, &m_VkRenderPass); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateRenderPass!");
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
