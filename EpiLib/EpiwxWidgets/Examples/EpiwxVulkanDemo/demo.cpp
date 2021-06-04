#pragma once

#include "EpiGraphicsDriver/gfxDriver.h"
#include "EpiGraphicsDriverCommon/gfxDescriptorSet.h"

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/window.h>
#include <wx/sizer.h>
#include <wx/timer.h>

#include <glm/gtc/matrix_transform.hpp>

#include "EpiGraphics/Camera/gfxCameraPersp.h"

#include "EpiwxWidgets/Vulkan/epiWXVulkanCanvas.h"

EPI_NAMESPACE_USING()

gfxPhysicalDevice g_PhysicalDevice;
gfxDevice g_Device;

constexpr gfxFormat kFormatRequired = gfxFormat::B8G8R8A8_SRGB;
constexpr gfxSurfaceColorSpace kColorSpaceRequired = gfxSurfaceColorSpace::SRGB_NONLINEAR;
constexpr gfxSurfacePresentMode kPresentModeRequired = gfxSurfacePresentMode::MAILBOX;

class epiWXVulkanDemoFrame : public wxFrame
{
public:
    epiWXVulkanDemoFrame(wxWindow* parent,
                         wxWindowID id = wxID_ANY,
                         const wxString& title = wxEmptyString,
                         const wxPoint& pos = wxDefaultPosition,
                         const wxSize& size = wxSize(623, 441),
                         long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
};

class EpiwxVulkanDemo : public wxApp
{
public:
    bool OnInit() override;
    int OnExit() override;

protected:
    epiWXVulkanDemoFrame* m_Frame;
};

class epiWXVulkanDemoTriangleCanvas : public epiWXVulkanCanvas
{
public:
    wxDECLARE_EVENT_TABLE();

public:
    struct Vertex
    {
        epiVec2f Position;
        epiVec3f Color;
    };

    struct UniformBufferObject
    {
        alignas(16) epiMat4x4f Model;
        alignas(16) epiMat4x4f View;
        alignas(16) epiMat4x4f Proj;
    };

public:
    epiWXVulkanDemoTriangleCanvas(wxWindow* parent,
                                  wxWindowID id = wxID_ANY,
                                  const wxPoint& pos = wxDefaultPosition,
                                  const wxSize& size = wxDefaultSize,
                                  long style = 0,
                                  const wxString& name = wxASCII_STR("epiWXVulkanDemoTriangleCanvas"))
    {
        {
            gfxAttachment attachment;
            attachment.SetFormat(kFormatRequired);
            attachment.SetSampleCount(gfxSampleCount::Sample1);
            attachment.SetLoadOp(gfxAttachmentLoadOp::Clear);
            attachment.SetStoreOp(gfxAttachmentStoreOp::Store);
            attachment.SetStencilLoadOp(gfxAttachmentLoadOp::DontCare);
            attachment.SetStencilStoreOp(gfxAttachmentStoreOp::DontCare);
            attachment.SetInitialLayout(gfxImageLayout::Undefined);
            attachment.SetFinalLayout(gfxImageLayout::PresentSrc);

            gfxRenderSubPass subpass;
            subpass.SetBindPoint(gfxPipelineBindPoint::Graphics);
            subpass.AddAttachment(attachment, 0, gfxImageLayout::ColorAttachmentOptimal, gfxAttachmentBindPoint::Color);

            gfxRenderSubPassDependency subpassDependency;
            subpassDependency.SetIsSrcSubPassExternal(true);
            subpassDependency.SetDstSubPass(0);
            subpassDependency.SetSrcStageMask(gfxPipelineStage_ColorAttachmentOutput);
            subpassDependency.SetSrcAccessMask(gfxAccess{0});
            subpassDependency.SetDstStageMask(gfxPipelineStage_ColorAttachmentOutput);
            subpassDependency.SetDstAccessMask(gfxAccess_ColorAttachmentWrite);

            gfxRenderPassCreateInfo renderPassCreateInfo{};
            renderPassCreateInfo.AddSubPass(std::move(subpass));
            renderPassCreateInfo.AddSubPassDependency(std::move(subpassDependency));

            std::optional<gfxRenderPass> renderPass = g_Device.CreateRenderPass(renderPassCreateInfo);
            epiAssert(renderPass.has_value());

            m_RenderPass = *renderPass;
        }

        gfxSurfaceFormat surfaceFormat;
        surfaceFormat.SetFormat(kFormatRequired);
        surfaceFormat.SetColorSpace(kColorSpaceRequired);

        {
            const auto queueFamilyIt = std::find_if(g_Device.GetQueueFamilies().begin(),
                                                    g_Device.GetQueueFamilies().end(),
                                                    [](const gfxQueueFamily& queueFamily)
            {
                return queueFamily.GetQueueTypeSupportedMask() & gfxQueueType_Graphics;
            });

            epiAssert(queueFamilyIt != g_Device.GetQueueFamilies().end());

            m_QueueFamily = *queueFamilyIt;
        }

        epiWXVulkanCanvasCreateInfo canvasCreateInfo;
        canvasCreateInfo.PhysicalDevice = g_PhysicalDevice;
        canvasCreateInfo.Device = g_Device;
        canvasCreateInfo.RenderPass = m_RenderPass;
        canvasCreateInfo.QueueFamily = m_QueueFamily;
        canvasCreateInfo.Format = surfaceFormat;
        canvasCreateInfo.PresentMode = kPresentModeRequired;

        if (!Create(canvasCreateInfo, parent, id, pos, size, style, name))
        {
            return;
        }

        {
            gfxDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo;
            descriptorSetLayoutCreateInfo.AddBinding(0, gfxDescriptorType::UniformBuffer, 1, gfxShaderStage_Vertex);

            std::optional<gfxDescriptorSetLayout> descriptorSetLayout = g_Device.CreateDescriptorSetLayout(descriptorSetLayoutCreateInfo);
            epiAssert(descriptorSetLayout.has_value());

            m_DescriptorSetLayout = *descriptorSetLayout;
        }

        gfxPipelineColorBlendAttachment colorBlendAttachment;
        colorBlendAttachment.SetColorWriteMask(gfxColorComponent_RGBA);
        colorBlendAttachment.SetBlendEnable(false);
        colorBlendAttachment.SetSrcColorBlendFactor(gfxBlendFactor::One);
        colorBlendAttachment.SetDstColorBlendFactor(gfxBlendFactor::Zero);
        colorBlendAttachment.SetColorBlendOp(gfxBlendOp::Add);
        colorBlendAttachment.SetSrcAlphaBlendFactor(gfxBlendFactor::One);
        colorBlendAttachment.SetDstAlphaBlendFactor(gfxBlendFactor::Zero);
        colorBlendAttachment.SetAlphaBlendOp(gfxBlendOp::Add);

        const std::string kVertexShaderModule = R"(
            #version 450
            #extension GL_ARB_separate_shader_objects : enable

            layout(set = 0, binding = 0) uniform UniformBufferObject {
                mat4 model;
                mat4 view;
                mat4 proj;
            } ubo;

            layout(location = 0) in vec2 inPosition;
            layout(location = 1) in vec3 inColor;

            layout(location = 0) out vec3 outFragColor;

            void main() {
                gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 0.0, 1.0);
                outFragColor = inColor;
            }
        )";

        const std::string kFragmentShaderModule = R"(
            #version 450
            #extension GL_ARB_separate_shader_objects : enable

            layout(location = 0) in vec3 fragColor;

            layout(location = 0) out vec4 outColor;

            void main() {
                outColor = vec4(fragColor, 1.0);
            }
        )";

        std::optional<gfxShader> vertexShader = g_Device.CreateShaderFromSource(kVertexShaderModule.c_str(), gfxShaderType::Vertex);
        std::optional<gfxShader> fragmentShader = g_Device.CreateShaderFromSource(kFragmentShaderModule.c_str(), gfxShaderType::Fragment);

        epiAssert(vertexShader.has_value());
        epiAssert(fragmentShader.has_value());

        gfxShaderProgramCreateInfo shaderProgramCreateInfo;
        shaderProgramCreateInfo.SetVertex(&*vertexShader);
        shaderProgramCreateInfo.SetFragment(&*fragmentShader);

        std::optional<gfxShaderProgram> shaderProgram = g_Device.CreateShaderProgram(shaderProgramCreateInfo);
        epiAssert(shaderProgram.has_value());

        gfxPipelineViewport viewport;
        viewport.SetRect(epiRect2f(0.0f, 0.0f, m_SwapChain.GetExtent().x, m_SwapChain.GetExtent().y));
        viewport.SetMinDepth(0.0f);
        viewport.SetMaxDepth(1.0f);

        gfxPipelineVertexInputBindingDescription vertexInputBindingDescription;
        vertexInputBindingDescription.SetStride(sizeof(Vertex));
        vertexInputBindingDescription.SetInputRate(gfxPipelineVertexInputRate::Vertex);
        vertexInputBindingDescription
            .AddAttribute(0, gfxFormat::R32G32_SFLOAT, offsetof(Vertex, Position))
            .AddAttribute(1, gfxFormat::R32G32B32_SFLOAT, offsetof(Vertex, Color));

        {
            gfxPipelineLayoutCreateInfo pipelineLayoutCreateInfo;
            pipelineLayoutCreateInfo.AddDescriptorSetLayout(m_DescriptorSetLayout);

            std::optional<gfxPipelineLayout> pipelineLayout = g_Device.CreatePipelineLayout(pipelineLayoutCreateInfo);
            epiAssert(pipelineLayout.has_value());

            m_PipelineLayout = *pipelineLayout;
        }

        gfxPipelineGraphicsCreateInfo pipelineCreateInfo;
        pipelineCreateInfo.SetPipelineLayout(m_PipelineLayout);
        pipelineCreateInfo.SetInputAssemblyType(gfxPipelineInputAssemblyType::TriangleList);
        pipelineCreateInfo.AddViewport(viewport);
        pipelineCreateInfo.AddScissor(epiRect2s(0, 0, m_SwapChain.GetExtent().x, m_SwapChain.GetExtent().y));
        pipelineCreateInfo.SetDepthClampEnable(false);
        pipelineCreateInfo.SetRasterizerDiscardEnable(false);
        pipelineCreateInfo.SetPolygonMode(gfxPolygonMode::Fill);
        pipelineCreateInfo.SetLineWidth(1.0f);
        pipelineCreateInfo.SetCullMode(gfxCullMode::None);
        pipelineCreateInfo.SetFrontFace(gfxFrontFace::CW);
        pipelineCreateInfo.SetDepthClampEnable(false);
        pipelineCreateInfo.SetDepthBiasConstantFactor(0.0f);
        pipelineCreateInfo.SetDepthBiasClamp(0.0f);
        pipelineCreateInfo.SetDepthBiasSlopeFactor(0.0f);
        pipelineCreateInfo.AddColorBlendAttachment(colorBlendAttachment);
        pipelineCreateInfo.SetColorBlendLogicOpEnable(false);
        pipelineCreateInfo.SetColorBlendLogicOp(gfxLogicOp::Copy);
        pipelineCreateInfo.SetColorBlendConstants(epiVec4f{0.0f, 0.0f, 0.0f, 0.0f});
        pipelineCreateInfo.SetRenderSubPassIndex(0);
        pipelineCreateInfo.SetShaderProgram(*shaderProgram);
        pipelineCreateInfo
            .AddDynamicState(gfxPipelineDynamicState::Viewport)
            .AddDynamicState(gfxPipelineDynamicState::Scissor)
            .AddVertexInputBinding(vertexInputBindingDescription);

        {
            std::optional<gfxPipelineGraphics> pipeline = g_Device.CreatePipelineGraphics(pipelineCreateInfo, m_RenderPass);
            epiAssert(pipeline.has_value());

            m_Pipeline = *pipeline;
        }

        m_Vertices = {
            {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
            {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
        };
        const epiSize_t vertexBufferCapacity = m_Vertices.size() * sizeof(m_Vertices[0]);

        {
            gfxBufferCreateInfo vertexBufferCreateInfo;
            vertexBufferCreateInfo.SetCapacity(vertexBufferCapacity);
            vertexBufferCreateInfo.SetUsage(epiMask(gfxBufferUsage_VertexBuffer, gfxBufferUsage_TransferDst));

            std::optional<gfxBuffer> vertexBuffer = g_Device.CreateBuffer(vertexBufferCreateInfo);
            epiAssert(vertexBuffer.has_value());

            m_VertexBuffer = *vertexBuffer;

            gfxDeviceMemoryCreateInfo vertexDeviceMemoryCreateInfo;
            vertexDeviceMemoryCreateInfo.SetBuffer(m_VertexBuffer);
            vertexDeviceMemoryCreateInfo.SetPropertyMask(gfxDeviceMemoryProperty_DeviceLocal);

            std::optional<gfxDeviceMemory> deviceMemory = g_Device.CreateDeviceMemory(vertexDeviceMemoryCreateInfo);
            epiAssert(deviceMemory.has_value());

            m_VertexDeviceMemory = *deviceMemory;
        }

        {
            gfxBufferCreateInfo stagingBufferCreateInfo;
            stagingBufferCreateInfo.SetCapacity(vertexBufferCapacity);
            stagingBufferCreateInfo.SetUsage(gfxBufferUsage_TransferSrc);

            std::optional<gfxBuffer> stagingBuffer = g_Device.CreateBuffer(stagingBufferCreateInfo);
            epiAssert(stagingBuffer.has_value());

            gfxDeviceMemoryCreateInfo stagingDeviceMemoryCreateInfo;
            stagingDeviceMemoryCreateInfo.SetBuffer(*stagingBuffer);
            stagingDeviceMemoryCreateInfo.SetPropertyMask(epiMask(gfxDeviceMemoryProperty_HostCoherent, gfxDeviceMemoryProperty_HostVisible));

            std::optional<gfxDeviceMemory> stagingDeviceMemory = g_Device.CreateDeviceMemory(stagingDeviceMemoryCreateInfo);
            epiAssert(stagingDeviceMemory.has_value());

            if (gfxDeviceMemory::Mapping mapping = stagingDeviceMemory->Map(vertexBufferCapacity))
            {
                for (const Vertex& v : m_Vertices)
                {
                    mapping.PushBack(v);
                }
            }

            gfxCommandPoolCreateInfo commandPoolCreateInfo;
            commandPoolCreateInfo.SetQueueFamily(m_QueueFamily);
            commandPoolCreateInfo.SetUsage(gfxCommandPoolUsage_TRANSIENT);
            commandPoolCreateInfo.SetPrimaryCommandBufferCount(1);

            std::optional<gfxCommandPool> copyCmdPool = g_Device.CreateCommandPool(commandPoolCreateInfo);
            epiAssert(copyCmdPool.has_value());

            if (gfxCommandBufferRecord record = copyCmdPool->GetPrimaryCommandBuffers()[0].RecordCommands(gfxCommandBufferUsage_OneTimeSubmit))
            {
                gfxCommandBufferRecordCopyRegion copyRegion;
                copyRegion.SetSize(vertexBufferCapacity);

                record.Copy(*stagingBuffer, m_VertexBuffer, {copyRegion});
            }

            gfxQueueSubmitInfo submitInfo;
            submitInfo.GetCommandBuffers().push_back(copyCmdPool->GetPrimaryCommandBuffers()[0]);

            m_QueueFamily[0].Submit(submitInfo);
        }

        m_Indices = { 0, 1, 2, 2, 3, 0 };
        const epiSize_t indexBufferCapacity = m_Indices.size() * sizeof(m_Indices[0]);

        {
            gfxBufferCreateInfo indexBufferCreateInfo;
            indexBufferCreateInfo.SetCapacity(indexBufferCapacity);
            indexBufferCreateInfo.SetUsage(epiMask(gfxBufferUsage_IndexBuffer, gfxBufferUsage_TransferDst));

            std::optional<gfxBuffer> indexBuffer = g_Device.CreateBuffer(indexBufferCreateInfo);
            epiAssert(indexBuffer.has_value());

            m_IndexBuffer = *indexBuffer;

            gfxDeviceMemoryCreateInfo indexDeviceMemoryCreateInfo;
            indexDeviceMemoryCreateInfo.SetBuffer(m_IndexBuffer);
            indexDeviceMemoryCreateInfo.SetPropertyMask(gfxDeviceMemoryProperty_DeviceLocal);

            std::optional<gfxDeviceMemory> deviceMemory = g_Device.CreateDeviceMemory(indexDeviceMemoryCreateInfo);
            epiAssert(deviceMemory.has_value());

            m_IndexDeviceMemory = *deviceMemory;
        }

        {
            gfxBufferCreateInfo stagingBufferCreateInfo;
            stagingBufferCreateInfo.SetCapacity(indexBufferCapacity);
            stagingBufferCreateInfo.SetUsage(gfxBufferUsage_TransferSrc);

            std::optional<gfxBuffer> stagingBuffer = g_Device.CreateBuffer(stagingBufferCreateInfo);
            epiAssert(stagingBuffer.has_value());

            gfxDeviceMemoryCreateInfo stagingDeviceMemoryCreateInfo;
            stagingDeviceMemoryCreateInfo.SetBuffer(*stagingBuffer);
            stagingDeviceMemoryCreateInfo.SetPropertyMask(epiMask(gfxDeviceMemoryProperty_HostCoherent, gfxDeviceMemoryProperty_HostVisible));

            std::optional<gfxDeviceMemory> stagingDeviceMemory = g_Device.CreateDeviceMemory(stagingDeviceMemoryCreateInfo);
            epiAssert(stagingDeviceMemory.has_value());

            if (gfxDeviceMemory::Mapping mapping = stagingDeviceMemory->Map(indexBufferCapacity))
            {
                for (const epiU16& v : m_Indices)
                {
                    mapping.PushBack(v);
                }
            }

            gfxCommandPoolCreateInfo commandPoolCreateInfo;
            commandPoolCreateInfo.SetQueueFamily(m_QueueFamily);
            commandPoolCreateInfo.SetUsage(gfxCommandPoolUsage_TRANSIENT);
            commandPoolCreateInfo.SetPrimaryCommandBufferCount(1);

            std::optional<gfxCommandPool> copyCmdPool = g_Device.CreateCommandPool(commandPoolCreateInfo);
            epiAssert(copyCmdPool.has_value());

            if (gfxCommandBufferRecord record = copyCmdPool->GetPrimaryCommandBuffers()[0].RecordCommands(gfxCommandBufferUsage_OneTimeSubmit))
            {
                gfxCommandBufferRecordCopyRegion copyRegion;
                copyRegion.SetSize(indexBufferCapacity);

                record.Copy(*stagingBuffer, m_IndexBuffer, {copyRegion});
            }

            gfxQueueSubmitInfo submitInfo;
            submitInfo.GetCommandBuffers().push_back(copyCmdPool->GetPrimaryCommandBuffers()[0]);

            m_QueueFamily[0].Submit(submitInfo);
        }

        {
            m_UniformBuffers.Resize(m_SwapChain.GetBufferCount());
            m_UniformDeviceMemories.Resize(m_SwapChain.GetBufferCount());
            for (epiU32 i = 0; i < m_SwapChain.GetBufferCount(); ++i)
            {
                gfxBufferCreateInfo uniformBufferCreateInfo;
                uniformBufferCreateInfo.SetCapacity(sizeof(UniformBufferObject));
                uniformBufferCreateInfo.SetUsage(gfxBufferUsage_UniformBuffer);

                std::optional<gfxBuffer> uniformBuffer = g_Device.CreateBuffer(uniformBufferCreateInfo);
                epiAssert(uniformBuffer.has_value());

                m_UniformBuffers[i] = *uniformBuffer;

                gfxDeviceMemoryCreateInfo uniformDeviceMemoryCreateInfo;
                uniformDeviceMemoryCreateInfo.SetBuffer(m_UniformBuffers[i]);
                uniformDeviceMemoryCreateInfo.SetPropertyMask(epiMask(gfxDeviceMemoryProperty_HostCoherent, gfxDeviceMemoryProperty_HostVisible));

                std::optional<gfxDeviceMemory> uniformDeviceMemory = g_Device.CreateDeviceMemory(uniformDeviceMemoryCreateInfo);
                epiAssert(uniformDeviceMemory.has_value());

                m_UniformDeviceMemories[i] = *uniformDeviceMemory;
            }

            {
                gfxDescriptorPoolSize poolSize;
                poolSize.SetDescriptorType(gfxDescriptorType::UniformBuffer);
                poolSize.SetDescriptorCount(m_SwapChain.GetBufferCount());

                gfxDescriptorPoolCreateInfo descriptorPoolCreateInfo;
                descriptorPoolCreateInfo.SetMaxSets(m_SwapChain.GetBufferCount());
                descriptorPoolCreateInfo.AddDescriptorPoolSize(poolSize);

                for (epiU32 i = 0; i < m_SwapChain.GetBufferCount(); ++i)
                {
                    descriptorPoolCreateInfo.AddDescriptorSetLayout(m_DescriptorSetLayout);
                }

                std::optional<gfxDescriptorPool> descriptorPool = g_Device.CreateDescriptorPool(descriptorPoolCreateInfo);
                epiAssert(descriptorPool.has_value());

                m_DescriptorPool = *descriptorPool;

                for (epiU32 i = 0; i < m_SwapChain.GetBufferCount(); ++i)
                {
                    gfxDescriptorBufferInfo bufferInfo;
                    bufferInfo.SetBuffer(m_UniformBuffers[i]);
                    bufferInfo.SetOffset(0);
                    bufferInfo.SetRange(sizeof(UniformBufferObject));

                    gfxDescriptorSetWrite descriptorWrite;
                    descriptorWrite.SetDstSet(m_DescriptorPool.GetDescriptorSets()[i]);
                    descriptorWrite.SetDstBinding(0);
                    descriptorWrite.SetDstArrayElement(0);
                    descriptorWrite.SetDescriptorType(gfxDescriptorType::UniformBuffer);
                    descriptorWrite.SetDescriptorCount(1);
                    descriptorWrite.AddBufferInfo(bufferInfo);

                    g_Device.UpdateDescriptorSets({descriptorWrite}, {});
                }
            }
        }

        RecordCommandBuffers();

        m_Timer.SetOwner(this, -1);
        m_Timer.Start(30);
    }

protected:
    void OnPaint(wxPaintEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnTimer(wxTimerEvent& event);

    void RecordCommandBuffers();

protected:
    wxTimer m_Timer;

    gfxDescriptorSetLayout m_DescriptorSetLayout;
    gfxQueueFamily m_QueueFamily;
    gfxRenderPass m_RenderPass;
    gfxPipelineLayout m_PipelineLayout;
    gfxPipelineGraphics m_Pipeline;
    gfxBuffer m_VertexBuffer;
    gfxBuffer m_IndexBuffer;
    epiArray<gfxBuffer> m_UniformBuffers;
    gfxDeviceMemory m_VertexDeviceMemory;
    gfxDeviceMemory m_IndexDeviceMemory;
    epiArray<gfxDeviceMemory> m_UniformDeviceMemories;
    gfxDescriptorPool m_DescriptorPool;
    std::vector<Vertex> m_Vertices;
    std::vector<epiU16> m_Indices;
};

wxBEGIN_EVENT_TABLE(epiWXVulkanDemoTriangleCanvas, epiWXVulkanCanvas)
    EVT_PAINT(epiWXVulkanDemoTriangleCanvas::OnPaint)
    EVT_ERASE_BACKGROUND(epiWXVulkanDemoTriangleCanvas::OnEraseBackground)
    EVT_SIZE(epiWXVulkanDemoTriangleCanvas::OnSize)
    EVT_TIMER(-1, epiWXVulkanDemoTriangleCanvas::OnTimer)
wxEND_EVENT_TABLE()

void epiWXVulkanDemoTriangleCanvas::OnPaint(wxPaintEvent& event)
{
    m_SwapChain.Present(m_QueueFamily[0], [this](epiU32 frameIndex)
    {
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

        UniformBufferObject ubo{};

        gfxCameraPersp camera;
        camera.SetPosition(epiVec3f{0.0f, 0.0f, 2.0f});
        camera.SetLookAtPosition(epiVec3f{0.0f, 0.0f, 0.0f});
        camera.SetUpDirection(epiVec3f{0.0f, 1.0f, 0.0f});
        camera.SetFOV(90.0f);
        camera.SetAspectRatio(static_cast<epiFloat>(m_SwapChain.GetExtent().x) / m_SwapChain.GetExtent().y);
        camera.SetPlaneNear(0.1f);
        camera.SetPlaneNear(10.0f);

        ubo.Model = glm::rotate(epiMat4x4f{1.0f}, time, epiVec3f{0.0f, 1.0f, 0.0f}); // TODO: replace with epiMat4x4fRotate()
        ubo.View = camera.GetViewMatrix();
        ubo.Proj = camera.GetProjectionMatrix();

        if (gfxDeviceMemory::Mapping mapping = m_UniformDeviceMemories[frameIndex].Map(sizeof(ubo)))
        {
            mapping.PushBack(ubo);
        }
    });
}

void epiWXVulkanDemoTriangleCanvas::OnEraseBackground(wxEraseEvent&)
{
    // NOTE: should reduce flickering
}

void epiWXVulkanDemoTriangleCanvas::OnSize(wxSizeEvent& event)
{
    if (!m_Surface)
    {
        return;
    }

    const gfxSurfaceCapabilities surfaceCapabilities = m_Surface.GetCapabilitiesFor(g_PhysicalDevice);

    epiSize2u extent{};
    if (surfaceCapabilities.GetCurrentExtent().x != std::numeric_limits<epiU32>::max())
    {
        extent = surfaceCapabilities.GetCurrentExtent();
    }
    else
    {
        extent.x = std::clamp(static_cast<epiU32>(event.GetSize().x), surfaceCapabilities.GetMinImageExtent().x, surfaceCapabilities.GetMaxImageExtent().x);
        extent.y = std::clamp(static_cast<epiU32>(event.GetSize().y), surfaceCapabilities.GetMinImageExtent().y, surfaceCapabilities.GetMaxImageExtent().y);
    }

    gfxSurfaceFormat surfaceFormat;
    surfaceFormat.SetFormat(kFormatRequired);
    surfaceFormat.SetColorSpace(kColorSpaceRequired);

    gfxSwapChainCreateInfo swapChainCreateInfo{};
    swapChainCreateInfo.SetSurface(m_Surface);
    swapChainCreateInfo.SetRenderPass(m_RenderPass);
    swapChainCreateInfo.SetQueueFamily(m_QueueFamily);
    swapChainCreateInfo.SetCapabilities(surfaceCapabilities);
    swapChainCreateInfo.SetFormat(surfaceFormat);
    swapChainCreateInfo.SetPresentMode(kPresentModeRequired);
    swapChainCreateInfo.SetExtent(extent);

    // TODO: recreate descriptor pool

    m_SwapChain.Recreate(swapChainCreateInfo);

    m_UniformBuffers.Clear();
    m_UniformDeviceMemories.Clear();

    // TODO: bind uniform buffers to the swapchain recreation in a proper way
    {
        m_UniformBuffers.Resize(m_SwapChain.GetBufferCount());
        m_UniformDeviceMemories.Resize(m_SwapChain.GetBufferCount());
        for (epiU32 i = 0; i < m_SwapChain.GetBufferCount(); ++i)
        {
            gfxBufferCreateInfo uniformBufferCreateInfo;
            uniformBufferCreateInfo.SetCapacity(sizeof(UniformBufferObject));
            uniformBufferCreateInfo.SetUsage(gfxBufferUsage_UniformBuffer);

            std::optional<gfxBuffer> uniformBuffer = g_Device.CreateBuffer(uniformBufferCreateInfo);
            epiAssert(uniformBuffer.has_value());

            m_UniformBuffers[i] = *uniformBuffer;

            gfxDeviceMemoryCreateInfo uniformDeviceMemoryCreateInfo;
            uniformDeviceMemoryCreateInfo.SetBuffer(m_UniformBuffers[i]);
            uniformDeviceMemoryCreateInfo.SetPropertyMask(epiMask(gfxDeviceMemoryProperty_HostCoherent, gfxDeviceMemoryProperty_HostVisible));

            std::optional<gfxDeviceMemory> uniformDeviceMemory = g_Device.CreateDeviceMemory(uniformDeviceMemoryCreateInfo);
            epiAssert(uniformDeviceMemory.has_value());

            m_UniformDeviceMemories[i] = *uniformDeviceMemory;
        }

        {
            gfxDescriptorPoolSize poolSize;
            poolSize.SetDescriptorType(gfxDescriptorType::UniformBuffer);
            poolSize.SetDescriptorCount(m_SwapChain.GetBufferCount());

            gfxDescriptorPoolCreateInfo descriptorPoolCreateInfo;
            descriptorPoolCreateInfo.SetMaxSets(m_SwapChain.GetBufferCount());
            descriptorPoolCreateInfo.AddDescriptorPoolSize(poolSize);

            for (epiU32 i = 0; i < m_SwapChain.GetBufferCount(); ++i)
            {
                descriptorPoolCreateInfo.AddDescriptorSetLayout(m_DescriptorSetLayout);
            }

            std::optional<gfxDescriptorPool> descriptorPool = g_Device.CreateDescriptorPool(descriptorPoolCreateInfo);
            epiAssert(descriptorPool.has_value());

            m_DescriptorPool = *descriptorPool;

            for (epiU32 i = 0; i < m_SwapChain.GetBufferCount(); ++i)
            {
                gfxDescriptorBufferInfo bufferInfo;
                bufferInfo.SetBuffer(m_UniformBuffers[i]);
                bufferInfo.SetOffset(0);
                bufferInfo.SetRange(sizeof(UniformBufferObject));

                gfxDescriptorSetWrite descriptorWrite;
                descriptorWrite.SetDstSet(m_DescriptorPool.GetDescriptorSets()[i]);
                descriptorWrite.SetDstBinding(0);
                descriptorWrite.SetDstArrayElement(0);
                descriptorWrite.SetDescriptorType(gfxDescriptorType::UniformBuffer);
                descriptorWrite.SetDescriptorCount(1);
                descriptorWrite.AddBufferInfo(bufferInfo);

                g_Device.UpdateDescriptorSets({descriptorWrite}, {});
            }
        }
    }

    m_Pipeline.DynamicClearViewports();
    m_Pipeline.DynamicClearScissors();

    gfxPipelineViewport viewport;
    viewport.SetRect(epiRect2f(0.0f, 0.0f, m_SwapChain.GetExtent().x, m_SwapChain.GetExtent().y));
    viewport.SetMinDepth(0.0f);
    viewport.SetMaxDepth(1.0f);

    m_Pipeline.DynamicAddViewport(viewport);
    m_Pipeline.DynamicAddScissor(epiRect2s(0, 0, m_SwapChain.GetExtent().x, m_SwapChain.GetExtent().y));

    RecordCommandBuffers();

    Refresh();
}

void epiWXVulkanDemoTriangleCanvas::OnTimer(wxTimerEvent& event)
{
    Refresh();
}

void epiWXVulkanDemoTriangleCanvas::RecordCommandBuffers()
{
    gfxRenderPassClearValue clearValue;
    clearValue.SetColor({0.0f, 0.0f, 0.0f, 1.0f});

    epiArray<gfxRenderPassClearValue> clearValues;
    clearValues.push_back(clearValue);

    for (epiU32 i = 0; i < m_SwapChain.GetBufferCount(); ++i)
    {
        if (gfxCommandBufferRecord record = m_SwapChain.ForBufferRecordCommands(i))
        {
            const gfxDescriptorSet& descriptorSet = m_DescriptorPool.GetDescriptorSets()[i];

            record
                .RenderPassBegin(m_SwapChain.ForBufferCreateRenderPassBeginInfo(i, m_RenderPass, clearValues))
                .PipelineBind(m_Pipeline)
                .VertexBuffersBind({m_VertexBuffer})
                .IndexBufferBind(m_IndexBuffer, gfxIndexBufferType::UInt16)
                .DescriptorSetsBind(gfxPipelineBindPoint::Graphics, m_PipelineLayout, {descriptorSet})
                .DrawIndexed(m_Indices.size(), 1, 0, 0, 0)
                .RenderPassEnd();
        }
    }
}

DECLARE_APP(EpiwxVulkanDemo)

IMPLEMENT_APP_NO_MAIN(EpiwxVulkanDemo);
IMPLEMENT_WX_THEME_SUPPORT;

int main(int argc, char* argv[])
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("%^[%l][%H:%M:%S:%e][%s:%#] %v%$");

    epiArray<gfxDriverExtension> driverExtensionsRequired;
    driverExtensionsRequired.push_back(gfxDriverExtension::Surface);

#ifdef EPI_PLATFORM_WINDOWS
    driverExtensionsRequired.push_back(gfxDriverExtension::SurfaceWin32);
#endif // EPI_PLATFORM_WINDOWS

    gfxDriver::SwitchBackend(gfxDriverBackend::Vulkan, driverExtensionsRequired);

    epiArray<gfxPhysicalDeviceExtension> deviceExtensionsRequired;
    deviceExtensionsRequired.push_back(gfxPhysicalDeviceExtension::SwapChain);
    //deviceExtensionsRequired.push_back(gfxPhysicalDeviceExtension::ImageLessFrameBuffer);
    //deviceExtensionsRequired.push_back(gfxPhysicalDeviceExtension::ImageFormatList);

    epiArray<gfxPhysicalDeviceFeature> deviceFeaturesRequired;
    //deviceFeaturesRequired.push_back(gfxPhysicalDeviceFeature::ImagelessFramebuffer);

    const gfxWindow window(GetActiveWindow());
    std::optional<gfxSurface> surface = gfxDriver::GetInstance().CreateSurface(window);

    const epiArray<gfxPhysicalDevice>& physicalDevices = gfxDriver::GetInstance().GetPhysicalDevices();
    auto physicalDevice = std::find_if(physicalDevices.begin(),
                                       physicalDevices.end(),
                                       [&surface,
                                        &deviceExtensionsRequired,
                                        &deviceFeaturesRequired](const gfxPhysicalDevice& physicalDevice)
    {
        if (physicalDevice.GetType() != gfxPhysicalDeviceType::DiscreteGPU ||
            !std::all_of(deviceExtensionsRequired.begin(), deviceExtensionsRequired.end(), [&physicalDevice](gfxPhysicalDeviceExtension extension)
        {
            return physicalDevice.IsExtensionSupported(extension);
        }) ||
            !std::all_of(deviceFeaturesRequired.begin(), deviceFeaturesRequired.end(), [&physicalDevice](gfxPhysicalDeviceFeature feature)
        {
            return physicalDevice.IsFeatureSupported(feature);
        }) ||
            !physicalDevice.IsQueueTypeSupported(gfxQueueType_Graphics))
        {
            return false;
        }

        const epiArray<gfxSurfaceFormat> supportedFormats = surface->GetSupportedFormatsFor(physicalDevice);
        const epiBool formatIsAppropriate = std::any_of(supportedFormats.begin(), supportedFormats.end(), [](const gfxSurfaceFormat& format)
        {
            return format.GetFormat() == kFormatRequired && format.GetColorSpace() == kColorSpaceRequired;
        });

        if (!formatIsAppropriate)
        {
            return false;
        }

        const epiArray<gfxSurfacePresentMode> supportedPresentModes = surface->GetSupportedPresentModesFor(physicalDevice);
        const epiBool presentModeIsAppropriate = std::any_of(supportedPresentModes.begin(), supportedPresentModes.end(), [](const gfxSurfacePresentMode& presentMode)
        {
            return presentMode == kPresentModeRequired;
        });

        if (!presentModeIsAppropriate)
        {
            return false;
        }

        return surface->IsPresentSupportedFor(physicalDevice);
    });

    if (physicalDevice == physicalDevices.end())
    {
        epiLogError("Failed to select a proper PhysicalDevice!");
        return -1;
    }

    gfxQueueDescriptorList queueDescriptorList;
    queueDescriptorList.Push(gfxQueueType_Graphics, {1.0f}, {&*surface});

    std::optional<gfxDevice> device = physicalDevice->CreateDevice(queueDescriptorList,
                                                                   deviceExtensionsRequired,
                                                                   deviceFeaturesRequired);
    if (!device.has_value())
    {
        epiLogError("Falied to create Device!");
        return -1;
    }

    g_PhysicalDevice = *physicalDevice;
    g_Device = std::move(*device);

    wxEntryStart(argc, argv);
    wxTheApp->CallOnInit();
    wxTheApp->OnRun();

    return 0;
}

bool EpiwxVulkanDemo::OnInit()
{
    if (!wxApp::OnInit())
    {
        return false;
    }

    SetVendorName("epi");
    SetVendorDisplayName("EPI Computer Inc.");
    SetAppName("epiwxvulkandemo");
    SetAppDisplayName("EPI wxVulkanDemo");
    SetClassName("EpiwxVulkanDemo");

    m_Frame = new epiWXVulkanDemoFrame(nullptr);
    m_Frame->SetPosition(wxDefaultPosition);
    m_Frame->Show(true);

    SetTopWindow(m_Frame);

    return true;
}

int EpiwxVulkanDemo::OnExit()
{
    // TODO: call vkDeviceWaitIdle(device) in a proper place

    delete m_Frame;
    return wxApp::OnExit();
}

epiWXVulkanDemoFrame::epiWXVulkanDemoFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxFrame(parent, id, title, pos, size, style)
{
    wxBoxSizer* vboxSizer = new wxBoxSizer(wxHORIZONTAL);
    vboxSizer->Add(new epiWXVulkanDemoTriangleCanvas(this, wxID_ANY, wxDefaultPosition, {200, 300}), 1, wxALL | wxEXPAND, 20);
    vboxSizer->Add(new epiWXVulkanDemoTriangleCanvas(this, wxID_ANY, wxDefaultPosition, {200, 300}), 1, wxALL | wxEXPAND, 20);

    SetSizerAndFit(vboxSizer);
}
