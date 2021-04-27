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
    struct RenderSubpassInfo
    {
        VkSubpassDescription Subpass;
        std::vector<VkAttachmentReference> ColorAttachmentRefs;
    };

    std::vector<RenderSubpassInfo> subpasses;
    subpasses.reserve(info.GetSubPasses().Size());

    std::vector<VkAttachmentDescription> attachments;
    for (const gfxRenderSubPass& subpass : info.GetSubPasses())
    {
        attachments.reserve(subpass.GetColorAttachments().Size());

        RenderSubpassInfo& subpassInfo = subpasses.emplace_back();
        subpassInfo = {};
        subpassInfo.ColorAttachmentRefs.reserve(subpass.GetColorAttachments().Size());

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

            VkAttachmentReference& colorAttachmentRef = subpassInfo.ColorAttachmentRefs.emplace_back();
            colorAttachmentRef = {};
            colorAttachmentRef.attachment = ref.GetAttachmentIndex();
            colorAttachmentRef.layout = gfxImageLayoutTo(ref.GetLayuot());
        }

        subpassInfo.Subpass.pipelineBindPoint = gfxPipelineBindPointTo(subpass.GetBindPoint());
        subpassInfo.Subpass.colorAttachmentCount = subpassInfo.ColorAttachmentRefs.size();
        subpassInfo.Subpass.pColorAttachments = subpassInfo.ColorAttachmentRefs.data();

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

    if (vkCreateRenderPass(m_VkDevice, &renderPassInfo, nullptr, &m_VkRenderPass) != VK_SUCCESS)
    {
        return false;
    }

    return true;
}

epiBool gfxRenderPassImplVK::Init(const gfxRenderPassSchema& schema)
{
    struct RenderSubpassInfo
    {
        VkSubpassDescription Subpass;
        std::vector<VkAttachmentReference> ColorAttachmentRefs;
    };

    std::vector<RenderSubpassInfo> subpasses;
    subpasses.reserve(schema.GetSubPasses().Size());

    std::vector<VkAttachmentDescription> attachments;
    for (const gfxRenderSubPassSchema& subpass : schema.GetSubPasses())
    {
        attachments.reserve(subpass.GetColorAttachments().Size());

        RenderSubpassInfo& subpassInfo = subpasses.emplace_back();
        subpassInfo = {};
        subpassInfo.ColorAttachmentRefs.reserve(subpass.GetColorAttachments().Size());

        for (const gfxAttachmentRefSchema& ref : subpass.GetColorAttachments())
        {
            const gfxAttachmentSchema& attachment = ref.GetAttachment();

            VkAttachmentDescription& colorAttachment = attachments.emplace_back();
            colorAttachment = {};
            colorAttachment.format = gfxFormatTo(attachment.GetFormat());
            colorAttachment.samples = gfxSampleCountTo(attachment.GetSampleCount());

            VkAttachmentReference& colorAttachmentRef = subpassInfo.ColorAttachmentRefs.emplace_back();
            colorAttachmentRef = {};
            colorAttachmentRef.attachment = ref.GetAttachmentIndex();
        }

        subpassInfo.Subpass.colorAttachmentCount = subpassInfo.ColorAttachmentRefs.size();
        subpassInfo.Subpass.pColorAttachments = subpassInfo.ColorAttachmentRefs.data();

        // TODO: handle other attachment types
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
