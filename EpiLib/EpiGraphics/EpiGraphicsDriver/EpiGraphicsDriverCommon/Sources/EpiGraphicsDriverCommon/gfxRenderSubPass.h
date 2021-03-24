#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxRenderSubPass.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxAttachment.h"

EPI_NAMESPACE_BEGIN()

class gfxAttachmentRef : public Object
{
EPI_GENREGION_BEGIN(gfxAttachmentRef)

EPI_GENHIDDEN_gfxAttachmentRef()

public:
    constexpr static epiMetaTypeID TypeID{0x63fc544a};

    enum gfxAttachmentRef_PIDs
    {
        PID_Attachment = 0x3602da6b,
        PID_AttachmentIndex = 0x6c2112bf,
        PID_Layuot = 0x9c0ab2a9,
        PID_COUNT = 3
    };

protected:
    gfxAttachment m_Attachment{};
    epiU32 m_AttachmentIndex{0};
    gfxImageLayout m_Layuot{};

EPI_GENREGION_END(gfxAttachmentRef)
};

class gfxRenderSubPass : public Object
{
EPI_GENREGION_BEGIN(gfxRenderSubPass)

EPI_GENHIDDEN_gfxRenderSubPass()

public:
    constexpr static epiMetaTypeID TypeID{0x8fdf3fa6};

    enum gfxRenderSubPass_PIDs
    {
        PID_BindPoint = 0x2163d576,
        PID_Attachments = 0xc1587501,
        PID_InputAttachments = 0x70d4ec53,
        PID_ColorAttachments = 0x10be45ca,
        PID_DepthStencilAttachments = 0xcebd1dbf,
        PID_COUNT = 5
    };

protected:
    epiArray<gfxAttachmentRef> GetInputAttachments_Callback() const;
    epiArray<gfxAttachmentRef> GetColorAttachments_Callback() const;
    epiArray<gfxAttachmentRef> GetDepthStencilAttachments_Callback() const;

protected:
    gfxPipelineBindPoint m_BindPoint{};
    epiArray<gfxAttachmentRef> m_Attachments{};

EPI_GENREGION_END(gfxRenderSubPass)

public:
    void AddAttachment(const gfxAttachment& attachment, epiU32 attachmentIndex, gfxImageLayout layout);
};

class gfxRenderSubPassDependency : public Object
{
EPI_GENREGION_BEGIN(gfxRenderSubPassDependency)

EPI_GENHIDDEN_gfxRenderSubPassDependency()

public:
    constexpr static epiMetaTypeID TypeID{0x94a8ddeb};

    enum gfxRenderSubPassDependency_PIDs
    {
        PID_SrcSubPass = 0xd4bef645,
        PID_DstSubPass = 0x70c940a5,
        PID_IsSrcSubPassExternal = 0xe55095a5,
        PID_IsDstSubPassExternal = 0xb6a5ce71,
        PID_SrcStageMask = 0x5890cb97,
        PID_DstStageMask = 0x24ec8ab5,
        PID_SrcAccessMask = 0xe4d2b1e8,
        PID_DstAccessMask = 0x31ce8c4d,
        PID_DependencyFlags = 0x68167a5,
        PID_COUNT = 9
    };

protected:
    epiU32 m_SrcSubPass{0};
    epiU32 m_DstSubPass{0};
    epiBool m_IsSrcSubPassExternal{false};
    epiBool m_IsDstSubPassExternal{false};
    gfxPipelineStage m_SrcStageMask{};
    gfxPipelineStage m_DstStageMask{};
    gfxAccess m_SrcAccessMask{};
    gfxAccess m_DstAccessMask{};
    gfxDependency m_DependencyFlags{};

EPI_GENREGION_END(gfxRenderSubPassDependency)
};

EPI_NAMESPACE_END()
