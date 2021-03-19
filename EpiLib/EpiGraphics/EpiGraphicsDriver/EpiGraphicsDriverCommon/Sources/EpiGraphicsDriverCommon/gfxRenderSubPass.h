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

EPI_NAMESPACE_END()
