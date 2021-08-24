#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxRenderPass.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

enum class gfxAttachmentBindPoint : epiS32
{
EPI_GENREGION_BEGIN(gfxAttachmentBindPoint)
    Input = 0,
    Color = 1,
    DepthStencil = 2,
    Resolve = 3
EPI_GENREGION_END(gfxAttachmentBindPoint)
};

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
    gfxFormat m_Format{};
    gfxSampleCountMask m_SampleCount{};
    gfxAttachmentLoadOp m_LoadOp{};
    gfxAttachmentStoreOp m_StoreOp{};
    gfxAttachmentLoadOp m_StencilLoadOp{};
    gfxAttachmentStoreOp m_StencilStoreOp{};
    gfxImageLayout m_InitialLayout{};
    gfxImageLayout m_FinalLayout{};

EPI_GENREGION_END(gfxAttachment)

public:
    epiBool IsCompatibleWith(const gfxAttachment& rhs) const;
};

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

public:
    epiBool IsCompatibleWith(const gfxAttachmentRef& rhs) const;
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
        PID_AttachmentsInput = 0xc826fdca,
        PID_AttachmentsColor = 0x765887f4,
        PID_AttachmentsDepthStencil = 0x929bf3a8,
        PID_AttachmentsResolve = 0x9252270f,
        PID_COUNT = 5
    };

protected:
    gfxPipelineBindPoint m_BindPoint{};
    epiArray<gfxAttachmentRef> m_AttachmentsInput{};
    epiArray<gfxAttachmentRef> m_AttachmentsColor{};
    epiArray<gfxAttachmentRef> m_AttachmentsDepthStencil{};
    epiArray<gfxAttachmentRef> m_AttachmentsResolve{};

EPI_GENREGION_END(gfxRenderSubPass)

public:
    epiBool IsCompatibleWith(const gfxRenderSubPass& rhs) const;

    void AddAttachment(const gfxAttachment& attachment, epiU32 attachmentIndex, gfxImageLayout layout, gfxAttachmentBindPoint bindPoint);
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

class gfxRenderPassCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxRenderPassCreateInfo)

EPI_GENHIDDEN_gfxRenderPassCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x32e02da9};

    enum gfxRenderPassCreateInfo_PIDs
    {
        PID_SubPasses = 0x3289b30,
        PID_SubPassDependencies = 0x86181723,
        PID_Attachments = 0xc1587501,
        PID_COUNT = 3
    };

protected:
    epiArray<gfxAttachment> GetAttachments_Callback() const;

protected:
    epiArray<gfxRenderSubPass> m_SubPasses{};
    epiArray<gfxRenderSubPassDependency> m_SubPassDependencies{};

EPI_GENREGION_END(gfxRenderPassCreateInfo)

public:
    void AddSubPass(gfxRenderSubPass&& subpass);
    void AddSubPassDependency(gfxRenderSubPassDependency&& subpassDependency);
};

class gfxRenderPass : public Object
{
EPI_GENREGION_BEGIN(gfxRenderPass)

EPI_GENHIDDEN_gfxRenderPass()

public:
    constexpr static epiMetaTypeID TypeID{0x7ada217b};

    enum gfxRenderPass_PIDs
    {
        PID_SubPasses = 0x3289b30,
        PID_SubPassDependencies = 0x86181723,
        PID_Attachments = 0xc1587501,
        PID_COUNT = 3
    };

protected:
    epiArray<gfxRenderSubPass> m_SubPasses{};
    epiArray<gfxRenderSubPassDependency> m_SubPassDependencies{};
    epiArray<gfxAttachment> m_Attachments{};

EPI_GENREGION_END(gfxRenderPass)

public:
    class Impl;

public:
    gfxRenderPass() = default;
    explicit gfxRenderPass(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    epiBool IsCompatibleWith(const gfxRenderPass& rhs) const;

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()