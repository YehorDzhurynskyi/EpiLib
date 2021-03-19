EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxRenderSubPass.h"
#include "EpiGraphicsDriverCommon/gfxRenderSubPass.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

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

EPI_NAMESPACE_END()
