#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxRenderPass.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxRenderSubPass.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxRenderPassImpl;

} // internalgfx

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
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxRenderPass)

public:
    friend class gfxDevice;
    friend class gfxCommandBuffer;

public:
    gfxRenderPass() = default;
    gfxRenderPass(internalgfx::gfxRenderPassImpl* impl);
    gfxRenderPass(const gfxRenderPass& rhs) = delete;
    gfxRenderPass& operator=(const gfxRenderPass& rhs) = delete;
    gfxRenderPass(gfxRenderPass&& rhs);
    gfxRenderPass& operator=(gfxRenderPass&& rhs);
    ~gfxRenderPass();

protected:
    internalgfx::gfxRenderPassImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
