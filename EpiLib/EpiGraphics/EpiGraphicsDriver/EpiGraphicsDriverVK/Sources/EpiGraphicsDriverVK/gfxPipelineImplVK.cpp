#include "EpiGraphicsDriverVK/gfxPipelineImplVK.h"

#include "EpiGraphicsDriverVK/gfxErrorVK.h"
#include "EpiGraphicsDriverVK/gfxEnumVK.h"
#include "EpiGraphicsDriverVK/gfxShaderProgramImplVK.h"
#include "EpiGraphicsDriverVK/gfxRenderPassImplVK.h"

#include <vulkan/vulkan.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxPipelineGraphicsImplVK::gfxPipelineGraphicsImplVK(const gfxDeviceImplVK& device)
    : m_Device{device}
{
}

gfxPipelineGraphicsImplVK::~gfxPipelineGraphicsImplVK()
{
    vkDestroyPipeline(m_Device.GetVkDevice(), m_VkPipeline, nullptr);
    vkDestroyPipelineLayout(m_Device.GetVkDevice(), m_VkPipelineLayout, nullptr);
}

epiBool gfxPipelineGraphicsImplVK::Init(const gfxPipelineGraphicsCreateInfo& info, const gfxShaderProgramImpl& shaderProgramImpl, const gfxRenderPassImpl& renderPassImpl)
{
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
        v.x = viewport.GetViewportRect().LeftTop().x;
        v.y = viewport.GetViewportRect().GetHeight() - viewport.GetViewportRect().LeftTop().y; // TODO: replace with image-space rect
        v.width = viewport.GetViewportRect().GetWidth();
        v.height = viewport.GetViewportRect().GetHeight();
        v.minDepth = viewport.GetViewportMinDepth();
        v.maxDepth = viewport.GetViewportMaxDepth();
    }

    std::vector<VkRect2D> scissors;
    scissors.reserve(info.GetScissors().Size());
    for (const epiRect2s& scissor : info.GetScissors())
    {
        VkRect2D& s = scissors.emplace_back();
        s = {};
        s.offset.x = scissor.LeftTop().x;
        s.offset.y = scissor.GetHeight() - scissor.LeftTop().y; // TODO: replace with image-space rect
        s.extent.width = scissor.GetWidth();
        s.extent.height = scissor.GetHeight();
    }

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

    // TODO: configure through gfxPipelineCreateInfo
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;

    if (const VkResult result = vkCreatePipelineLayout(m_Device.GetVkDevice(), &pipelineLayoutInfo, nullptr, &m_VkPipelineLayout); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreatePipelineLayout!");
        return false;
    }

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{}; // TODO: configure through gfxPipelineCreateInfo
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.pVertexBindingDescriptions = nullptr;
    vertexInputInfo.vertexAttributeDescriptionCount = 0;
    vertexInputInfo.pVertexAttributeDescriptions = nullptr;

    std::vector<VkPipelineShaderStageCreateInfo> stages;

    const gfxShaderProgramImplVK& shaderProgramImplVk = static_cast<const gfxShaderProgramImplVK&>(shaderProgramImpl);
    if (!shaderProgramImplVk.GetIsCreated())
    {
        epiLogError("Failed to initialize Pipeline! ShaderProgram isn't created!");
        return false;
    }

    const epiArray<gfxShaderImplVK*> modules = shaderProgramImplVk.GetCompiledModules();
    stages.reserve(modules.Size());

    for (const gfxShaderImplVK* module : modules)
    {
        VkPipelineShaderStageCreateInfo& shaderStageCreateInfo = stages.emplace_back();
        shaderStageCreateInfo = {};
        shaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        shaderStageCreateInfo.module = module->GetVkShaderModule();
        shaderStageCreateInfo.pName = module->GetEntryPoint().c_str();

        switch (module->GetType())
        {
        case gfxShaderType::Vertex: shaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT; break;
        case gfxShaderType::Geometry: shaderStageCreateInfo.stage = VK_SHADER_STAGE_GEOMETRY_BIT; break;
        case gfxShaderType::Fragment: shaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT; break;
        default: epiLogError("Unhandled gfxShaderType=`{}`", module->GetType()); shaderStageCreateInfo.stage = VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM; break; // TODO: get str repr of enum value
        }
    }

    std::vector<VkDynamicState> dynamicStates;
    std::transform(info.GetDynamicState().begin(),
                   info.GetDynamicState().end(),
                   std::back_inserter(dynamicStates),
                   [](const gfxPipelineDynamicState& state) {
        return gfxPipelineDynamicStateTo(state);
    });

    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = dynamicStates.size();
    dynamicState.pDynamicStates = dynamicStates.data();

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = stages.size();
    pipelineInfo.pStages = stages.data();
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = nullptr; // TODO: set
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = nullptr;
    pipelineInfo.layout = m_VkPipelineLayout;
    pipelineInfo.renderPass = static_cast<const gfxRenderPassImplVK&>(renderPassImpl).GetVkRenderPass();
    pipelineInfo.subpass = info.GetRenderSubPassIndex();
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
    pipelineInfo.basePipelineIndex = -1;
    pipelineInfo.pDynamicState = &dynamicState;

    if (const VkResult result = vkCreateGraphicsPipelines(m_Device.GetVkDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_VkPipeline); result != VK_SUCCESS)
    {
        gfxLogErrorEx(result, "Failed to call vkCreateGraphicsPipelines!");
        return false;
    }

    return true;
}

VkPipeline gfxPipelineGraphicsImplVK::GetVkPipeline() const
{
    return m_VkPipeline;
}

} // namespace internalgfx

EPI_NAMESPACE_END()
