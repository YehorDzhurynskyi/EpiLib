#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxAttachment.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

class gfxAttachment : public Object
{
EPI_GENREGION_BEGIN(gfxAttachment)

EPI_GENHIDDEN_gfxAttachment()

public:
    constexpr static epiMetaTypeID TypeID{0x2af252c7};

    enum gfxAttachment_PIDs
    {
        PID_Format = 0xd91677e9,
        PID_SampleCount = 0x2397b6e7,
        PID_LoadOp = 0x399a5a44,
        PID_StoreOp = 0xac4ec035,
        PID_StencilLoadOp = 0x1cd17288,
        PID_StencilStoreOp = 0x3eb90586,
        PID_InitialLayout = 0xcf791b4,
        PID_FinalLayout = 0x302a5e0f,
        PID_COUNT = 8
    };

protected:
    gfxFormat m_Format{gfxFormat::UNDEFINED};
    gfxSampleCount m_SampleCount{gfxSampleCount::Sample1};
    gfxAttachmentLoadOp m_LoadOp{gfxAttachmentLoadOp::DontCare};
    gfxAttachmentStoreOp m_StoreOp{gfxAttachmentStoreOp::DontCare};
    gfxAttachmentLoadOp m_StencilLoadOp{gfxAttachmentLoadOp::DontCare};
    gfxAttachmentStoreOp m_StencilStoreOp{gfxAttachmentStoreOp::DontCare};
    gfxImageLayout m_InitialLayout{gfxImageLayout::Undefined};
    gfxImageLayout m_FinalLayout{gfxImageLayout::Undefined};

EPI_GENREGION_END(gfxAttachment)
};

EPI_NAMESPACE_END()
