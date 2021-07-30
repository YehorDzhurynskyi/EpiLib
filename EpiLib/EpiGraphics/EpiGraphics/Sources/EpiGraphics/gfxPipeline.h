#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxPipeline.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphics/gfxEnum.h"
#include "EpiGraphics/gfxRenderPass.h"
#include "EpiGraphics/gfxShaderModule.h"
#include "EpiGraphics/gfxPipelineLayout.h"

EPI_NAMESPACE_BEGIN()

class gfxPipelineViewport : public Object
{
EPI_GENREGION_BEGIN(gfxPipelineViewport)

EPI_GENHIDDEN_gfxPipelineViewport()

public:
    constexpr static epiMetaTypeID TypeID{0xb66dc74d};

    enum gfxPipelineViewport_PIDs
    {
        PID_Rect = 0x17e49cbf,
        PID_MinDepth = 0x62aab39,
        PID_MaxDepth = 0xe04a04d8,
        PID_COUNT = 3
    };

protected:
    epiRect2f m_Rect{};
    epiFloat m_MinDepth{0.0f};
    epiFloat m_MaxDepth{1.0f};

EPI_GENREGION_END(gfxPipelineViewport)

public:
    epiBool IsValid() const;
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

class gfxPipelineVertexInputAttributeDescription : public Object
{
EPI_GENREGION_BEGIN(gfxPipelineVertexInputAttributeDescription)

EPI_GENHIDDEN_gfxPipelineVertexInputAttributeDescription()

public:
    constexpr static epiMetaTypeID TypeID{0xce0392ee};

    enum gfxPipelineVertexInputAttributeDescription_PIDs
    {
        PID_Location = 0xa7e8eb9d,
        PID_Format = 0xd91677e9,
        PID_Offset = 0x5ea6cfe6,
        PID_COUNT = 3
    };

protected:
    epiU32 m_Location{0};
    gfxFormat m_Format{};
    epiU32 m_Offset{0};

EPI_GENREGION_END(gfxPipelineVertexInputAttributeDescription)
};

class gfxPipelineVertexInputBindingDescription : public Object
{
EPI_GENREGION_BEGIN(gfxPipelineVertexInputBindingDescription)

EPI_GENHIDDEN_gfxPipelineVertexInputBindingDescription()

public:
    constexpr static epiMetaTypeID TypeID{0x70dc9b70};

    enum gfxPipelineVertexInputBindingDescription_PIDs
    {
        PID_Stride = 0x8df33e39,
        PID_InputRate = 0xb4165636,
        PID_AttributeDescriptions = 0x25f611b8,
        PID_COUNT = 3
    };

protected:
    epiU32 m_Stride{0};
    gfxPipelineVertexInputRate m_InputRate{gfxPipelineVertexInputRate::Vertex};
    epiArray<gfxPipelineVertexInputAttributeDescription> m_AttributeDescriptions{};

EPI_GENREGION_END(gfxPipelineVertexInputBindingDescription)

public:
    gfxPipelineVertexInputBindingDescription& AddAttribute(epiU32 location, gfxFormat format, epiU32 offset);
};

class gfxPipelineShaderStageCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxPipelineShaderStageCreateInfo)

EPI_GENHIDDEN_gfxPipelineShaderStageCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xa448ef5};

    enum gfxPipelineShaderStageCreateInfo_PIDs
    {
        PID_ShaderModule = 0xbc3b6b68,
        PID_COUNT = 1
    };

protected:
    gfxShaderModule m_ShaderModule{};

EPI_GENREGION_END(gfxPipelineShaderStageCreateInfo)
};

class gfxPipelineGraphicsCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxPipelineGraphicsCreateInfo)

EPI_GENHIDDEN_gfxPipelineGraphicsCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xae3d6062};

    enum gfxPipelineGraphicsCreateInfo_PIDs
    {
        PID_PipelineLayout = 0xd1bf14df,
        PID_RenderPass = 0x662aa9d7,
        PID_ShaderStageCreateInfos = 0x6e8babc7,
        PID_RenderSubPassIndex = 0xdaca0981,
        PID_InputAssemblyType = 0xe816cd01,
        PID_Viewports = 0xa8f1ee29,
        PID_Scissors = 0x7b580124,
        PID_VertexInputBindingDescriptions = 0xedcbd1c7,
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
        PID_DepthEnableTest = 0x73321fc6,
        PID_DepthEnableWrite = 0x6711c90,
        PID_DepthCompareOp = 0x31f83c87,
        PID_DepthEnableBoundsTest = 0x5617d231,
        PID_DepthBoundsTestMin = 0xea5069eb,
        PID_DepthBoundsTestMax = 0xd65d56b2,
        PID_ColorBlendAttachments = 0x64eca9dc,
        PID_ColorBlendLogicOpEnable = 0xa19e601f,
        PID_ColorBlendLogicOp = 0x7caacb6d,
        PID_ColorBlendConstants = 0x739a4ae9,
        PID_DynamicStates = 0xa85e8c69,
        PID_COUNT = 29
    };

protected:
    gfxPipelineLayout m_PipelineLayout{};
    gfxRenderPass m_RenderPass{};
    epiArray<gfxPipelineShaderStageCreateInfo> m_ShaderStageCreateInfos{};
    epiU32 m_RenderSubPassIndex{0};
    gfxPipelineInputAssemblyType m_InputAssemblyType{gfxPipelineInputAssemblyType::None};
    epiArray<gfxPipelineViewport> m_Viewports{};
    epiArray<epiRect2s> m_Scissors{};
    epiArray<gfxPipelineVertexInputBindingDescription> m_VertexInputBindingDescriptions{};
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
    epiBool m_DepthEnableTest{false};
    epiBool m_DepthEnableWrite{false};
    gfxCompareOp m_DepthCompareOp{};
    epiBool m_DepthEnableBoundsTest{false};
    epiFloat m_DepthBoundsTestMin{0.0f};
    epiFloat m_DepthBoundsTestMax{0.0f};
    epiArray<gfxPipelineColorBlendAttachment> m_ColorBlendAttachments{};
    epiBool m_ColorBlendLogicOpEnable{false};
    gfxLogicOp m_ColorBlendLogicOp{};
    epiVec4f m_ColorBlendConstants{};
    epiArray<gfxPipelineDynamicState> m_DynamicStates{};

EPI_GENREGION_END(gfxPipelineGraphicsCreateInfo)

public:
    gfxPipelineGraphicsCreateInfo& AddViewport(const gfxPipelineViewport& viewport);
    gfxPipelineGraphicsCreateInfo& AddScissor(const epiRect2s& scissor);
    gfxPipelineGraphicsCreateInfo& AddColorBlendAttachment(const gfxPipelineColorBlendAttachment& attachment);
    gfxPipelineGraphicsCreateInfo& AddDynamicState(gfxPipelineDynamicState state);
    gfxPipelineGraphicsCreateInfo& AddVertexInputBinding(const gfxPipelineVertexInputBindingDescription& vertexInputBinding);
    gfxPipelineGraphicsCreateInfo& AddShaderStage(const gfxPipelineShaderStageCreateInfo& info);
};

class gfxPipelineGraphics : public Object
{
EPI_GENREGION_BEGIN(gfxPipelineGraphics)

EPI_GENHIDDEN_gfxPipelineGraphics()

public:
    constexpr static epiMetaTypeID TypeID{0x168915bb};

    enum gfxPipelineGraphics_PIDs
    {
        PID_Viewports = 0xa8f1ee29,
        PID_Scissors = 0x7b580124,
        PID_COUNT = 2
    };

protected:
    const epiArray<gfxPipelineViewport>& GetViewports_Callback() const;
    const epiArray<epiRect2s>& GetScissors_Callback() const;

EPI_GENREGION_END(gfxPipelineGraphics)

public:
    class Impl;

public:
    gfxPipelineGraphics() = default;
    explicit gfxPipelineGraphics(const std::shared_ptr<Impl>& impl);

    epiBool HasImpl() const;

    epiBool IsDynamic(gfxPipelineDynamicState state) const;
    void DynamicClearViewports();
    void DynamicClearScissors();
    void DynamicAddViewport(const gfxPipelineViewport& viewport);
    void DynamicAddScissor(const epiRect2s& scissor);

protected:
    std::shared_ptr<Impl> m_Impl;
};

EPI_NAMESPACE_END()
