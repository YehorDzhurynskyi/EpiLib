EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxRenderPass.h"
#include "EpiGraphicsDriverCommon/gfxRenderPass.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

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

gfxRenderPass::gfxRenderPass(internalgfx::gfxRenderPassImpl* impl)
    : m_Impl{impl}
{
}

gfxRenderPass::gfxRenderPass(gfxRenderPass&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;
}

gfxRenderPass& gfxRenderPass::operator=(gfxRenderPass&& rhs)
{
    m_Impl = rhs.m_Impl;

    rhs.m_Impl = nullptr;

    return *this;
}

gfxRenderPass::~gfxRenderPass()
{
    delete m_Impl;
}

EPI_NAMESPACE_END()
