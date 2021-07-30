EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxRenderPass.h"
#include "EpiGraphics/gfxRenderPass.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

void gfxRenderSubPassSchema::AddAttachment(const gfxAttachmentSchema& attachment, epiU32 attachmentIndex, gfxAttachmentBindPoint bindPoint)
{
    gfxAttachmentRefSchema ref;
    ref.SetAttachment(attachment);
    ref.SetAttachmentIndex(attachmentIndex);

    epiArray<gfxAttachmentRefSchema>* attachments = nullptr;
    switch (bindPoint)
    {
    case gfxAttachmentBindPoint::Input: attachments = &GetAttachmentsInput(); break;
    case gfxAttachmentBindPoint::Color: attachments = &GetAttachmentsColor(); break;
    case gfxAttachmentBindPoint::DepthStencil: attachments = &GetAttachmentsDepthStencil(); break;
    case gfxAttachmentBindPoint::Resolve: attachments = &GetAttachmentsResolve(); break;
    default: epiLogError("Unrecognized AttachmentBindPoint=`{}`", bindPoint); // TODO: str repr
    }

    if (attachments != nullptr)
    {
        attachments->push_back(ref);
    }
}

void gfxRenderPassSchema::AddSubPass(gfxRenderSubPassSchema&& subpass)
{
    GetSubPasses().push_back(std::move(subpass));
}

epiArray<gfxAttachmentSchema> gfxRenderPassSchema::GetAttachments_Callback() const
{
    epiArray<gfxAttachmentSchema> attachments;

    auto pushBackAttachments = [&attachments](const epiArray<gfxAttachmentRefSchema>& refs)
    {
        for (const gfxAttachmentRefSchema& ref : refs)
        {
            attachments.push_back(ref.GetAttachment());
        }
    };

    for (const gfxRenderSubPassSchema& subpass : GetSubPasses())
    {
        pushBackAttachments(subpass.GetAttachmentsInput());
        pushBackAttachments(subpass.GetAttachmentsColor());
        pushBackAttachments(subpass.GetAttachmentsDepthStencil());
        pushBackAttachments(subpass.GetAttachmentsResolve());
    }

    return attachments;
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

void gfxRenderSubPass::AddAttachment(const gfxAttachment& attachment, epiU32 attachmentIndex, gfxImageLayout layout, gfxAttachmentBindPoint bindPoint)
{
    gfxAttachmentRef ref;
    ref.SetAttachment(attachment);
    ref.SetAttachmentIndex(attachmentIndex);
    ref.SetLayuot(layout);

    epiArray<gfxAttachmentRef>* attachments = nullptr;
    switch (bindPoint)
    {
    case gfxAttachmentBindPoint::Input: attachments = &GetAttachmentsInput(); break;
    case gfxAttachmentBindPoint::Color: attachments = &GetAttachmentsColor(); break;
    case gfxAttachmentBindPoint::DepthStencil: attachments = &GetAttachmentsDepthStencil(); break;
    case gfxAttachmentBindPoint::Resolve: attachments = &GetAttachmentsResolve(); break;
    default: epiLogError("Unrecognized AttachmentBindPoint=`{}`", bindPoint); // TODO: str repr
    }

    if (attachments != nullptr)
    {
        attachments->push_back(ref);
    }
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

    return compatible(GetAttachmentsColor(), rhs.GetAttachmentsColor()) &&
           compatible(GetAttachmentsInput(), rhs.GetAttachmentsInput()) &&
           compatible(GetAttachmentsDepthStencil(), rhs.GetAttachmentsDepthStencil()) &&
           compatible(GetAttachmentsResolve(), rhs.GetAttachmentsResolve());
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

    return compatible(GetAttachmentsColor(), rhs.GetAttachmentsColor()) &&
           compatible(GetAttachmentsInput(), rhs.GetAttachmentsInput()) &&
           compatible(GetAttachmentsDepthStencil(), rhs.GetAttachmentsDepthStencil()) &&
           compatible(GetAttachmentsResolve(), rhs.GetAttachmentsResolve());
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

    auto pushBackAttachments = [&attachments](const epiArray<gfxAttachmentRef>& refs)
    {
        for (const gfxAttachmentRef& ref : refs)
        {
            attachments.push_back(ref.GetAttachment());
        }
    };

    for (const gfxRenderSubPass& subpass : GetSubPasses())
    {
        pushBackAttachments(subpass.GetAttachmentsInput());
        pushBackAttachments(subpass.GetAttachmentsColor());
        pushBackAttachments(subpass.GetAttachmentsDepthStencil());
        pushBackAttachments(subpass.GetAttachmentsResolve());
    }

    return attachments;
}

gfxRenderPass::gfxRenderPass(const std::shared_ptr<Impl>& impl)
    : m_Impl{impl}
{
}

epiBool gfxRenderPass::HasImpl() const
{
    return static_cast<epiBool>(m_Impl);
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
