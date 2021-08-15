#include "EpiGraphicsImplVK/gfxPipelineImplVK.h"

#include "EpiGraphicsImplVK/gfxErrorVK.h"
#include "EpiGraphicsImplVK/gfxEnumVK.h"
#include "EpiGraphicsImplVK/gfxPipelineLayoutImplVK.h"
#include "EpiGraphicsImplVK/gfxDeviceImplVK.h"
#include "EpiGraphicsImplVK/gfxRenderPassImplVK.h"
#include "EpiGraphicsImplVK/gfxShaderModuleImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

gfxPipelineGraphicsImplVK::gfxPipelineGraphicsImplVK(const gfxDeviceImplVK& device)
    : m_Device{device}
{
}

gfxPipelineGraphicsImplVK::~gfxPipelineGraphicsImplVK()
{
    vkDestroyPipeline(m_Device.GetVkDevice(), m_VkPipeline, nullptr);
}

epiBool gfxPipelineGraphicsImplVK::Init(const gfxPipelineGraphicsCreateInfo& info)
{
    const gfxPipelineLayoutImplVK* pipelineLayoutVk = static_cast<const gfxPipelineLayoutImplVK*>(gfxPipelineLayout::Impl::ExtractImpl(info.GetPipelineLayout()));
    if (pipelineLayoutVk == nullptr)
    {
        epiLogError("Failed to Init PipelineGraphics! The provided PipelineLayout has no implementation!");
        return false;
    }

    const gfxRenderPassImplVK* renderPassVk = static_cast<const gfxRenderPassImplVK*>(gfxRenderPass::Impl::ExtractImpl(info.GetRenderPass()));
    if (renderPassVk == nullptr)
    {
        epiLogError("Failed to Init PipelineGraphics! The provided RenderPass has no implementation!");
        return false;
    }

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = gfxPipelineInputAssemblyTypeTo(info.GetInputAssemblyType());
    inputAssembly.primitiveRestartEnable = VK_FALSE; // TODO: make it configurable on demand

    std::vector<VkViewport> viewports;
    viewports.reserve(info.GetViewports().Size());
    for (const gfxPipelineViewport& viewport : info.GetViewports())
    {
        VkViewport& v = viewports.emplace_back();
        v = {};
        v.x = viewport.GetRect().LeftTop().x;
        v.y = viewport.GetRect().GetHeight() - viewport.GetRect().Top; // TODO: replace with image-space rect
        v.width = viewport.GetRect().GetWidth();
        v.height = viewport.GetRect().GetHeight();
        v.minDepth = viewport.GetMinDepth();
        v.maxDepth = viewport.GetMaxDepth();
    }

    m_Viewports.Clear();
    std::copy(info.GetViewports().begin(), info.GetViewports().end(), std::back_inserter(m_Viewports));

    std::vector<VkRect2D> scissors;
    scissors.reserve(info.GetScissors().Size());
    for (const epiRect2s& scissor : info.GetScissors())
    {
        VkRect2D& s = scissors.emplace_back();
        s = {};
        s.offset.x = scissor.Left;
        s.offset.y = scissor.GetHeight() - scissor.Top; // TODO: replace with image-space rect
        s.extent.width = scissor.GetWidth();
        s.extent.height = scissor.GetHeight();
    }

    m_Scissors.Clear();
    std::copy(info.GetScissors().begin(), info.GetScissors().end(), std::back_inserter(m_Scissors));

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = viewports.size();
    viewportState.pViewports = viewports.data();
    viewportState.scissorCount = scissors.size();
    viewportState.pScissors = scissors.data();

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = info.GetDepthBiasEnable();
    rasterizer.rasterizerDiscardEnable = info.GetRasterizerDiscardEnable();
    rasterizer.polygonMode = gfxPolygonModeTo(info.GetPolygonMode());
    rasterizer.lineWidth = info.GetLineWidth();
    rasterizer.cullMode = gfxCullModeTo(info.GetCullMode());
    rasterizer.frontFace = gfxFrontFaceTo(info.GetFrontFace());
    rasterizer.depthBiasEnable = info.GetDepthBiasEnable();
    rasterizer.depthBiasConstantFactor = info.GetDepthBiasConstantFactor();
    rasterizer.depthBiasClamp = info.GetDepthBiasClamp();
    rasterizer.depthBiasSlopeFactor = info.GetDepthBiasSlopeFactor();

    // TODO: configure multisampling through gfxPipelineCreateInfo
    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f;
    multisampling.pSampleMask = nullptr;
    multisampling.alphaToCoverageEnable = VK_FALSE;
    multisampling.alphaToOneEnable = VK_FALSE;

    std::vector<VkPipelineColorBlendAttachmentState> attachments;
    attachments.reserve(info.GetColorBlendAttachments().Size());
    for (const gfxPipelineColorBlendAttachment& attachment : info.GetColorBlendAttachments())
    {
        VkPipelineColorBlendAttachmentState& a = attachments.emplace_back();
        a = {};
        a.colorWriteMask = gfxColorComponentTo(attachment.GetColorWriteMask());
        a.blendEnable = attachment.GetBlendEnable();
        a.srcColorBlendFactor = gfxBlendFactorTo(attachment.GetSrcColorBlendFactor());
        a.dstColorBlendFactor = gfxBlendFactorTo(attachment.GetDstColorBlendFactor());
        a.colorBlendOp = gfxBlendOpTo(attachment.GetColorBlendOp());
        a.srcAlphaBlendFactor = gfxBlendFactorTo(attachment.GetSrcAlphaBlendFactor());
        a.dstAlphaBlendFactor = gfxBlendFactorTo(attachment.GetDstAlphaBlendFactor());
        a.alphaBlendOp = gfxBlendOpTo(attachment.GetAlphaBlendOp());
    }

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = info.GetColorBlendLogicOpEnable();
    colorBlending.logicOp = gfxLogicOpTo(info.GetColorBlendLogicOp());
    colorBlending.attachmentCount = attachments.size();
    colorBlending.pAttachments = attachments.data();
    colorBlending.blendConstants[0] = info.GetColorBlendConstants().r;
    colorBlending.blendConstants[1] = info.GetColorBlendConstants().g;
    colorBlending.blendConstants[2] = info.GetColorBlendConstants().b;
    colorBlending.blendConstants[3] = info.GetColorBlendConstants().a;

    std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions;

    {
        epiU32 binding = 0;
        for (const gfxPipelineVertexInputBindingDescription& bindingDesc : info.GetVertexInputBindingDescriptions())
        {
            VkVertexInputBindingDescription& bindingDescVk = vertexBindingDescriptions.emplace_back();
            bindingDescVk = {};
            bindingDescVk.binding = binding;
            bindingDescVk.inputRate = gfxPipelineVertexInputRateTo(bindingDesc.GetInputRate());
            bindingDescVk.stride = bindingDesc.GetStride();

            for (const gfxPipelineVertexInputAttributeDescription& attrDesc : bindingDesc.GetAttributeDescriptions())
            {
                VkVertexInputAttributeDescription& attrDescVk = vertexAttributeDescriptions.emplace_back();
                attrDescVk = {};
                attrDescVk.binding = binding;
                attrDescVk.location = attrDesc.GetLocation();
                attrDescVk.format = gfxFormatTo(attrDesc.GetFormat());
                attrDescVk.offset = attrDesc.GetOffset();
            }

            ++binding;
        }
    }

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = vertexBindingDescriptions.size();
    vertexInputInfo.pVertexBindingDescriptions = vertexBindingDescriptions.data();
    vertexInputInfo.vertexAttributeDescriptionCount = vertexAttributeDescriptions.size();
    vertexInputInfo.pVertexAttributeDescriptions = vertexAttributeDescriptions.data();

    std::vector<VkPipelineShaderStageCreateInfo> stages;
    stages.reserve(info.GetShaderStageCreateInfos().Size());

    std::transform(info.GetShaderStageCreateInfos().begin(),
                   info.GetShaderStageCreateInfos().end(),
                   std::back_inserter(stages),
                   [](const gfxPipelineShaderStageCreateInfo& stageInfo)
    {
        const gfxShaderModuleImplVK* module = static_cast<const gfxShaderModuleImplVK*>(gfxShaderModule::Impl::ExtractImpl(stageInfo.GetShaderModule()));
        epiAssert(module != nullptr);

        VkPipelineShaderStageCreateInfo stage{};
        stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stage.module = module->GetVkShaderModule();
        stage.pName = module->GetEntryPoint().c_str();
        stage.stage = gfxShaderStageTo(module->GetStage());

        return stage;
    });

    for (gfxPipelineDynamicState state : info.GetDynamicStates())
    {
        m_DynamicStates[static_cast<epiU32>(state)] = true;
    }

    std::vector<VkDynamicState> dynamicStates;
    std::transform(info.GetDynamicStates().begin(),
                   info.GetDynamicStates().end(),
                   std::back_inserter(dynamicStates),
                   [](const gfxPipelineDynamicState& state) {
        return gfxPipelineDynamicStateTo(state);
    });

    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = dynamicStates.size();
    dynamicState.pDynamicStates = dynamicStates.data();

    VkPipelineDepthStencilStateCreateInfo depthStencilState{};
    depthStencilState.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencilState.depthTestEnable = info.GetDepthEnableTest();
    depthStencilState.depthWriteEnable = info.GetDepthEnableWrite();
    depthStencilState.depthCompareOp = gfxCompareOpTo(info.GetDepthCompareOp());
    depthStencilState.depthBoundsTestEnable = info.GetDepthEnableBoundsTest();
    depthStencilState.minDepthBounds = info.GetDepthBoundsTestMin();
    depthStencilState.maxDepthBounds = info.GetDepthBoundsTestMax();

    // TODO: set
    depthStencilState.stencilTestEnable = VK_FALSE;
    depthStencilState.front = {};
    depthStencilState.back = {};

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = stages.size();
    pipelineInfo.pStages = stages.data();
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = &depthStencilState;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = &dynamicState;
    pipelineInfo.layout = pipelineLayoutVk->GetVkPipelineLayout();
    pipelineInfo.renderPass = renderPassVk->GetVkRenderPass();
    pipelineInfo.subpass = info.GetRenderSubPassIndex();
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
    pipelineInfo.basePipelineIndex = -1;

    if (const VkResult result = vkCreateGraphicsPipelines(m_Device.GetVkDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_VkPipeline); result != VK_SUCCESS)
    {
        gfxLogVkResultEx(result, "Failed to call vkCreateGraphicsPipelines!");
        return false;
    }

    return true;
}

VkPipeline gfxPipelineGraphicsImplVK::GetVkPipeline() const
{
    return m_VkPipeline;
}

EPI_NAMESPACE_END()
