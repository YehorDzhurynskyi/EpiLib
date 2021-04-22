#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxPipeline.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxRenderPass.h"
#include "EpiGraphicsDriverCommon/gfxShaderProgram.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxPipelineImpl;

} // internalgfx

class gfxPipelineViewport : public Object
{
EPI_GENREGION_BEGIN(gfxPipelineViewport)

EPI_GENHIDDEN_gfxPipelineViewport()

public:
    constexpr static epiMetaTypeID TypeID{0xb66dc74d};

    enum gfxPipelineViewport_PIDs
    {
        PID_ViewportRect = 0x8db0f4ec,
        PID_ViewportMinDepth = 0x575b73e7,
        PID_ViewportMaxDepth = 0xb13bdc06,
        PID_COUNT = 3
    };

protected:
    epiRect2f m_ViewportRect{};
    epiFloat m_ViewportMinDepth{0.0f};
    epiFloat m_ViewportMaxDepth{1.0f};

EPI_GENREGION_END(gfxPipelineViewport)
};

class gfxPipelineColorBlendAttachment : public Object
{
EPI_GENREGION_BEGIN(gfxPipelineColorBlendAttachment)

EPI_GENHIDDEN_gfxPipelineColorBlendAttachment()

public:
    constexpr static epiMetaTypeID TypeID{0xde0b5681};

    enum gfxPipelineColorBlendAttachment_PIDs
    {
        PID_BlendEnable = 0xc7da870f,
        PID_SrcColorBlendFactor = 0x2fc8b306,
        PID_DstColorBlendFactor = 0xae255090,
        PID_ColorBlendOp = 0x17c36f81,
        PID_SrcAlphaBlendFactor = 0xf3a76809,
        PID_DstAlphaBlendFactor = 0x724a8b9f,
        PID_AlphaBlendOp = 0xc9ddad78,
        PID_ColorWriteMask = 0x3805c8,
        PID_COUNT = 8
    };

protected:
    epiBool m_BlendEnable{false};
    gfxBlendFactor m_SrcColorBlendFactor{};
    gfxBlendFactor m_DstColorBlendFactor{};
    gfxBlendOp m_ColorBlendOp{};
    gfxBlendFactor m_SrcAlphaBlendFactor{};
    gfxBlendFactor m_DstAlphaBlendFactor{};
    gfxBlendOp m_AlphaBlendOp{};
    gfxColorComponent m_ColorWriteMask{gfxColorComponent_RGBA};

EPI_GENREGION_END(gfxPipelineColorBlendAttachment)
};

class gfxPipelineCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxPipelineCreateInfo)

EPI_GENHIDDEN_gfxPipelineCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xe3024e64};

    enum gfxPipelineCreateInfo_PIDs
    {
        PID_ShaderProgram = 0xe4812959,
        PID_RenderSubPassIndex = 0xdaca0981,
        PID_InputAssemblyType = 0xe816cd01,
        PID_Viewports = 0xa8f1ee29,
        PID_Scissors = 0x7b580124,
        PID_DepthClampEnable = 0xf410b2f0,
        PID_RasterizerDiscardEnable = 0xcc8a6a07,
        PID_PolygonMode = 0xbd90fa7f,
        PID_LineWidth = 0x19426b4a,
        PID_CullMode = 0x4928870f,
        PID_FrontFace = 0x62c4e7a2,
        PID_DepthBiasEnable = 0x605ab99,
        PID_DepthBiasConstantFactor = 0x18f11b49,
        PID_DepthBiasClamp = 0xaa48bad,
        PID_DepthBiasSlopeFactor = 0xf2d2e9cb,
        PID_ColorBlendAttachments = 0x64eca9dc,
        PID_ColorBlendLogicOpEnable = 0xa19e601f,
        PID_ColorBlendLogicOp = 0x7caacb6d,
        PID_ColorBlendConstants = 0x739a4ae9,
        PID_COUNT = 19
    };

protected:
    gfxShaderProgram* m_ShaderProgram{nullptr};
    epiU32 m_RenderSubPassIndex{0};
    gfxPipelineInputAssemblyType m_InputAssemblyType{gfxPipelineInputAssemblyType::None};
    epiArray<gfxPipelineViewport> m_Viewports{};
    epiArray<epiRect2s> m_Scissors{};
    epiBool m_DepthClampEnable{false};
    epiBool m_RasterizerDiscardEnable{false};
    gfxPolygonMode m_PolygonMode{gfxPolygonMode::Fill};
    epiFloat m_LineWidth{1.0f};
    gfxCullMode m_CullMode{gfxCullMode::None};
    gfxFrontFace m_FrontFace{gfxFrontFace::CW};
    epiBool m_DepthBiasEnable{false};
    epiFloat m_DepthBiasConstantFactor{0.0f};
    epiFloat m_DepthBiasClamp{0.0f};
    epiFloat m_DepthBiasSlopeFactor{0.0f};
    epiArray<gfxPipelineColorBlendAttachment> m_ColorBlendAttachments{};
    epiBool m_ColorBlendLogicOpEnable{false};
    gfxLogicOp m_ColorBlendLogicOp{};
    epiVec4f m_ColorBlendConstants{};

EPI_GENREGION_END(gfxPipelineCreateInfo)

public:
    gfxPipelineCreateInfo() = default;
    gfxPipelineCreateInfo(const gfxPipelineCreateInfo& rhs) = delete;
    gfxPipelineCreateInfo& operator=(const gfxPipelineCreateInfo& rhs) = delete;
    gfxPipelineCreateInfo(gfxPipelineCreateInfo&& rhs) = default;
    gfxPipelineCreateInfo& operator=(gfxPipelineCreateInfo&& rhs) = default;
    ~gfxPipelineCreateInfo() = default;

public:
    gfxPipelineCreateInfo& AddScissor(const epiRect2s& scissor);
    gfxPipelineCreateInfo& AddViewport(const gfxPipelineViewport& viewport);
    gfxPipelineCreateInfo& AddColorBlendAttachment(const gfxPipelineColorBlendAttachment& attachment);
};

class gfxPipeline : public Object
{
EPI_GENREGION_BEGIN(gfxPipeline)

EPI_GENHIDDEN_gfxPipeline()

public:
    constexpr static epiMetaTypeID TypeID{0x6442434b};

    enum gfxPipeline_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxPipeline)

public:
    gfxPipeline() = default;
    gfxPipeline(internalgfx::gfxPipelineImpl* impl);
    gfxPipeline(const gfxPipeline& rhs) = delete;
    gfxPipeline& operator=(const gfxPipeline& rhs) = delete;
    gfxPipeline(gfxPipeline&& rhs);
    gfxPipeline& operator=(gfxPipeline&& rhs);
    ~gfxPipeline();

protected:
    internalgfx::gfxPipelineImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
