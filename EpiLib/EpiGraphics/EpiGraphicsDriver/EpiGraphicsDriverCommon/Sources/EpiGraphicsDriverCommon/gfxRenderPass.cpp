EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxRenderPass.h"
#include "EpiGraphicsDriverCommon/gfxRenderPass.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

void gfxRenderSubPassSchema::AddAttachment(const gfxAttachmentSchema& attachment, epiU32 attachmentIndex)
{
    gfxAttachmentRefSchema ref;
    ref.SetAttachment(attachment);
    ref.SetAttachmentIndex(attachmentIndex);

    m_Attachments.push_back(ref);
}

void gfxRenderPassSchema::AddSubPass(gfxRenderSubPassSchema&& subpass)
{
    GetSubPasses().push_back(std::move(subpass));
}

void gfxRenderPassSchema::AddAttachment(gfxAttachmentSchema&& attachment)
{
    GetAttachments().push_back(std::move(attachment));
}

epiBool gfxAttachment::IsCompatibleWith(const gfxAttachment& rhs) const
{
    return GetFormat() == rhs.GetFormat() && GetSampleCount() == rhs.GetSampleCount();
}

epiBool gfxAttachment::IsCompatibleWith(const gfxAttachmentSchema& rhs) const
{
    return GetFormat() == rhs.GetFormat() && GetSampleCount() == rhs.GetSampleCount();
}

epiBool gfxAttachmentRef::IsCompatibleWith(const gfxAttachmentRef& rhs) const
{
    return GetAttachmentIndex() == rhs.GetAttachmentIndex() && GetAttachment().IsCompatibleWith(rhs.GetAttachment());
}

epiBool gfxAttachmentRef::IsCompatibleWith(const gfxAttachmentRefSchema& rhs) const
{
    return GetAttachmentIndex() == rhs.GetAttachmentIndex() && GetAttachment().IsCompatibleWith(rhs.GetAttachment());
}

void gfxRenderSubPass::AddAttachment(const gfxAttachment& attachment, epiU32 attachmentIndex, gfxImageLayout layout)
{
    gfxAttachmentRef ref;
    ref.SetAttachment(attachment);
    ref.SetAttachmentIndex(attachmentIndex);
    ref.SetLayuot(layout);

    m_Attachments.push_back(ref);
}

epiArray<gfxAttachmentRef> gfxRenderSubPass::GetInputAttachments_Callback() const
{
    epiArray<gfxAttachmentRef> result;
    result.Reserve(GetAttachments().Size());

    std::copy_if(GetAttachments().begin(), GetAttachments().end(), std::back_inserter(result), [](const gfxAttachmentRef& ref)
    {
        switch (ref.GetLayuot())
        {
        // TODO: implement
        default: return false;
        }
    });

    return result;
}

epiArray<gfxAttachmentRef> gfxRenderSubPass::GetColorAttachments_Callback() const
{
    epiArray<gfxAttachmentRef> result;
    result.Reserve(GetAttachments().Size());

    std::copy_if(GetAttachments().begin(), GetAttachments().end(), std::back_inserter(result), [](const gfxAttachmentRef& ref)
    {
        switch (ref.GetLayuot())
        {
        case gfxImageLayout::ColorAttachmentOptimal:
            return true;
        default: return false;
        }
    });

    return result;
}

epiArray<gfxAttachmentRef> gfxRenderSubPass::GetDepthStencilAttachments_Callback() const
{
    epiArray<gfxAttachmentRef> result;
    result.Reserve(GetAttachments().Size());

    std::copy_if(GetAttachments().begin(), GetAttachments().end(), std::back_inserter(result), [](const gfxAttachmentRef& ref)
    {
        switch (ref.GetLayuot())
        {
        case gfxImageLayout::DepthStencilAttachmentOptimal:
        case gfxImageLayout::DepthStencilReadOnlyOptimal:
        case gfxImageLayout::DepthReadOnlyStencilAttachmentOptimal:
        case gfxImageLayout::DepthAttachmentStencilReadOnlyOptimal:
        case gfxImageLayout::DepthAttachmentOptimal:
        case gfxImageLayout::DepthReadOnlyOptimal:
        case gfxImageLayout::StencilAttachmentOptimal:
        case gfxImageLayout::StencilReadOnlyOptimal:
            return true;
        default: return false;
        }
    });

    return result;
}

epiArray<gfxAttachmentRef> gfxRenderSubPass::GetResolveAttachments_Callback() const
{
    // TODO: implement
    return {};
}

epiBool gfxRenderSubPass::IsCompatibleWith(const gfxRenderSubPass& rhs) const
{
    auto compatible = [](const epiArray<gfxAttachmentRef>& lhsAttachments,
                         const epiArray<gfxAttachmentRef>& rhsAttachments)
    {
        if (lhsAttachments.Size() != rhsAttachments.Size())
        {
            return false;
        }

        for (epiU32 i = 0; i < lhsAttachments.Size(); ++i)
        {
            if (!lhsAttachments[i].IsCompatibleWith(rhsAttachments[i]))
            {
                return false;
            }
        }

        return true;
    };

    return compatible(GetColorAttachments(), rhs.GetColorAttachments()) &&
           compatible(GetInputAttachments(), rhs.GetInputAttachments()) &&
           compatible(GetDepthStencilAttachments(), rhs.GetDepthStencilAttachments()) &&
           compatible(GetResolveAttachments(), rhs.GetResolveAttachments());
}

epiBool gfxRenderSubPass::IsCompatibleWith(const gfxRenderSubPassSchema& rhs) const
{
    auto compatible = [](const epiArray<gfxAttachmentRef>& lhsAttachments,
                         const epiArray<gfxAttachmentRefSchema>& rhsAttachments)
    {
        if (lhsAttachments.Size() != rhsAttachments.Size())
        {
            return false;
        }

        for (epiU32 i = 0; i < lhsAttachments.Size(); ++i)
        {
            if (!lhsAttachments[i].IsCompatibleWith(rhsAttachments[i]))
            {
                return false;
            }
        }

        return true;
    };

    return compatible(GetColorAttachments(), rhs.GetColorAttachments()) &&
           compatible(GetInputAttachments(), rhs.GetInputAttachments()) &&
           compatible(GetDepthStencilAttachments(), rhs.GetDepthStencilAttachments()) &&
           compatible(GetResolveAttachments(), rhs.GetResolveAttachments());
}

void gfxRenderPassCreateInfo::AddSubPass(gfxRenderSubPass&& subpass)
{
    GetSubPasses().push_back(std::move(subpass));
}

void gfxRenderPassCreateInfo::AddSubPassDependency(gfxRenderSubPassDependency&& subpassDependency)
{
    GetSubPassDependencies().push_back(std::move(subpassDependency));
}

epiArray<gfxAttachment> gfxRenderPassCreateInfo::GetAttachments_Callback() const
{
    epiArray<gfxAttachment> attachments;

    for (const gfxRenderSubPass& subpass : GetSubPasses())
    {
        for (const gfxAttachmentRef& ref : subpass.GetAttachments())
        {
            attachments.push_back(ref.GetAttachment());
        }
    }

    return attachments;
}

gfxRenderPass::gfxRenderPass(const std::shared_ptr<internalgfx::gfxRenderPassImpl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxRenderPass::IsCompatibleWith(const gfxRenderPass& rhs) const
{
    // TODO: consider unused attachments
    // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap8.html#renderpass-compatibility

    const epiArray<gfxAttachment>& lhsAttachments = GetAttachments();
    const epiArray<gfxAttachment>& rhsAttachments = rhs.GetAttachments();

    if (lhsAttachments.Size() != rhsAttachments.Size())
    {
        return false;
    }

    for (epiU32 i = 0; i < lhsAttachments.Size(); ++i)
    {
        if (!lhsAttachments[i].IsCompatibleWith(rhsAttachments[i]))
        {
            return false;
        }
    }

    const epiArray<gfxRenderSubPass>& lhsSubPasses = GetSubPasses();
    const epiArray<gfxRenderSubPass>& rhsSubPasses = rhs.GetSubPasses();

    if (lhsSubPasses.Size() != rhsSubPasses.Size())
    {
        return false;
    }

    // TODO: consider special case for a single subpass
    for (epiU32 i = 0; i < lhsSubPasses.Size(); ++i)
    {
        if (!lhsSubPasses[i].IsCompatibleWith(rhsSubPasses[i]))
        {
            return false;
        }
    }

    return true;
}

epiBool gfxRenderPass::IsCompatibleWith(const gfxRenderPassSchema& rhs) const
{
    // TODO: consider unused attachments
    // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap8.html#renderpass-compatibility

    const epiArray<gfxAttachment>& lhsAttachments = GetAttachments();
    const epiArray<gfxAttachmentSchema>& rhsAttachments = rhs.GetAttachments();

    if (lhsAttachments.Size() != rhsAttachments.Size())
    {
        return false;
    }

    for (epiU32 i = 0; i < lhsAttachments.Size(); ++i)
    {
        if (!lhsAttachments[i].IsCompatibleWith(rhsAttachments[i]))
        {
            return false;
        }
    }

    const epiArray<gfxRenderSubPass>& lhsSubPasses = GetSubPasses();
    const epiArray<gfxRenderSubPassSchema>& rhsSubPasses = rhs.GetSubPasses();

    if (lhsSubPasses.Size() != rhsSubPasses.Size())
    {
        return false;
    }

    // TODO: consider special case for a single subpass
    for (epiU32 i = 0; i < lhsSubPasses.Size(); ++i)
    {
        if (!lhsSubPasses[i].IsCompatibleWith(rhsSubPasses[i]))
        {
            return false;
        }
    }

    return true;
}

EPI_NAMESPACE_END()
