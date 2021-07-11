#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxRenderPass.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxPipeline.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxRenderPassImpl;

} // internalgfx

enum class gfxAttachmentBindPoint : epiS32
{
EPI_GENREGION_BEGIN(gfxAttachmentBindPoint)
    Input = 0,
    Color = 1,
    DepthStencil = 2,
    Resolve = 3
EPI_GENREGION_END(gfxAttachmentBindPoint)
};

class gfxAttachmentSchema : public Object
{
EPI_GENREGION_BEGIN(gfxAttachmentSchema)

EPI_GENHIDDEN_gfxAttachmentSchema()

public:
    constexpr static epiMetaTypeID TypeID{0xe8a9ebd9};

    enum gfxAttachmentSchema_PIDs
    {
        PID_Format = 0xd91677e9,
        PID_SampleCount = 0x2397b6e7,
        PID_COUNT = 2
    };

protected:
    gfxFormat m_Format{gfxFormat::UNDEFINED};
    gfxSampleCount m_SampleCount{gfxSampleCount::Sample1};

EPI_GENREGION_END(gfxAttachmentSchema)
};

class gfxAttachmentRefSchema : public Object
{
EPI_GENREGION_BEGIN(gfxAttachmentRefSchema)

EPI_GENHIDDEN_gfxAttachmentRefSchema()

public:
    constexpr static epiMetaTypeID TypeID{0x5a53d803};

    enum gfxAttachmentRefSchema_PIDs
    {
        PID_Attachment = 0x3602da6b,
        PID_AttachmentIndex = 0x6c2112bf,
        PID_COUNT = 2
    };

protected:
    gfxAttachmentSchema m_Attachment{};
    epiU32 m_AttachmentIndex{0};

EPI_GENREGION_END(gfxAttachmentRefSchema)
};

class gfxRenderSubPassSchema : public Object
{
EPI_GENREGION_BEGIN(gfxRenderSubPassSchema)

EPI_GENHIDDEN_gfxRenderSubPassSchema()

public:
    constexpr static epiMetaTypeID TypeID{0xc7486cb2};

    enum gfxRenderSubPassSchema_PIDs
    {
        PID_AttachmentsInput = 0xc826fdca,
        PID_AttachmentsColor = 0x765887f4,
        PID_AttachmentsDepthStencil = 0x929bf3a8,
        PID_AttachmentsResolve = 0x9252270f,
        PID_COUNT = 4
    };

protected:
    epiArray<gfxAttachmentRefSchema> m_AttachmentsInput{};
    epiArray<gfxAttachmentRefSchema> m_AttachmentsColor{};
    epiArray<gfxAttachmentRefSchema> m_AttachmentsDepthStencil{};
    epiArray<gfxAttachmentRefSchema> m_AttachmentsResolve{};

EPI_GENREGION_END(gfxRenderSubPassSchema)

public:
    void AddAttachment(const gfxAttachmentSchema& attachment, epiU32 attachmentIndex, gfxAttachmentBindPoint bindPoint);
};

class gfxRenderPassSchema : public Object
{
EPI_GENREGION_BEGIN(gfxRenderPassSchema)

EPI_GENHIDDEN_gfxRenderPassSchema()

public:
    constexpr static epiMetaTypeID TypeID{0x32e90ba9};

    enum gfxRenderPassSchema_PIDs
    {
        PID_SubPasses = 0x3289b30,
        PID_Attachments = 0xc1587501,
        PID_COUNT = 2
    };

protected:
    epiArray<gfxAttachmentSchema> GetAttachments_Callback() const;

protected:
    epiArray<gfxRenderSubPassSchema> m_SubPasses{};

EPI_GENREGION_END(gfxRenderPassSchema)

public:
    void AddSubPass(gfxRenderSubPassSchema&& subpass);
    void AddAttachment(gfxAttachmentSchema&& attachment);
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
    gfxFormat m_Format{gfxFormat::UNDEFINED};
    gfxSampleCount m_SampleCount{gfxSampleCount::Sample1};
    gfxAttachmentLoadOp m_LoadOp{gfxAttachmentLoadOp::DontCare};
    gfxAttachmentStoreOp m_StoreOp{gfxAttachmentStoreOp::DontCare};
    gfxAttachmentLoadOp m_StencilLoadOp{gfxAttachmentLoadOp::DontCare};
    gfxAttachmentStoreOp m_StencilStoreOp{gfxAttachmentStoreOp::DontCare};
    gfxImageLayout m_InitialLayout{gfxImageLayout::Undefined};
    gfxImageLayout m_FinalLayout{gfxImageLayout::Undefined};

EPI_GENREGION_END(gfxAttachment)

public:
    epiBool IsCompatibleWith(const gfxAttachment& rhs) const;
    epiBool IsCompatibleWith(const gfxAttachmentSchema& rhs) const;
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
    epiBool IsCompatibleWith(const gfxAttachmentRefSchema& rhs) const;
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
    epiBool IsCompatibleWith(const gfxRenderSubPassSchema& rhs) const;

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
    friend class gfxDevice;
    friend class gfxSwapChain;
    friend class gfxCommandBufferRecord;
    friend class internalgfx::gfxRenderPassImpl;

public:
    gfxRenderPass() = default;
    explicit gfxRenderPass(const std::shared_ptr<internalgfx::gfxRenderPassImpl>& impl);

    epiBool HasImpl() const;

    epiBool IsCompatibleWith(const gfxRenderPass& rhs) const;
    epiBool IsCompatibleWith(const gfxRenderPassSchema& rhs) const;

protected:
    epiPimpl<internalgfx::gfxRenderPassImpl> m_Impl;
};

EPI_NAMESPACE_END()
