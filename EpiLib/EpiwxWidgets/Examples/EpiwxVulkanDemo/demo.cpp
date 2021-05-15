#pragma once

#include "EpiGraphicsDriver/gfxDriver.h"

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/window.h>
#include <wx/sizer.h>

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
    epiWXVulkanDemoTriangleCanvas(wxWindow* parent,
                                  wxWindowID id = wxID_ANY,
                                  const wxPoint& pos = wxDefaultPosition,
                                  const wxSize& size = wxDefaultSize,
                                  long style = 0,
                                  const wxString& name = wxASCII_STR("epiWXVulkanDemoTriangleCanvas"))
    {
    #if 0
        gfxAttachmentSchema attachmentSchema;
        attachmentSchema.SetFormat(kFormatRequired);
        attachmentSchema.SetSampleCount(gfxSampleCount::Sample1);

        gfxRenderSubPassSchema renderSubPassSchema;
        renderSubPassSchema.AddAttachment(attachmentSchema, 0, gfxAttachmentBindPoint::Color);

        gfxRenderPassSchema renderPassSchema;
        renderPassSchema.AddSubPass(std::move(renderSubPassSchema));
    #endif

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

            layout(location = 0) out vec3 fragColor;

            vec2 positions[3] = vec2[](
                vec2(0.0, -0.5),
                vec2(0.5, 0.5),
                vec2(-0.5, 0.5)
            );

            vec3 colors[3] = vec3[](
                vec3(1.0, 0.0, 0.0),
                vec3(0.0, 1.0, 0.0),
                vec3(0.0, 0.0, 1.0)
            );

            void main() {
                gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
                fragColor = colors[gl_VertexIndex];
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
        viewport.SetViewportRect(epiRect2f(0.0f, 0.0f, m_SwapChain.GetExtent().x, m_SwapChain.GetExtent().y));
        viewport.SetViewportMinDepth(0.0f);
        viewport.SetViewportMaxDepth(1.0f);

        gfxPipelineGraphicsCreateInfo pipelineCreateInfo;
        pipelineCreateInfo.SetInputAssemblyType(gfxPipelineInputAssemblyType::TriangleList);
        pipelineCreateInfo.AddViewport(viewport);
        pipelineCreateInfo.AddScissor(epiRect2s(0, 0, m_SwapChain.GetExtent().x, m_SwapChain.GetExtent().y));
        pipelineCreateInfo.SetDepthClampEnable(false);
        pipelineCreateInfo.SetRasterizerDiscardEnable(false);
        pipelineCreateInfo.SetPolygonMode(gfxPolygonMode::Fill);
        pipelineCreateInfo.SetLineWidth(1.0f);
        pipelineCreateInfo.SetCullMode(gfxCullMode::Back);
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

        {
            std::optional<gfxPipelineGraphics> pipeline = g_Device.CreatePipelineGraphics(pipelineCreateInfo, m_RenderPass);
            epiAssert(pipeline.has_value());

            m_Pipeline = *pipeline;
        }

        m_SwapChain.AssignRenderPass(m_RenderPass, m_Pipeline);
    }

protected:
    void OnPaint(wxPaintEvent& event);
    void OnEraseBackground(wxEraseEvent& event);

protected:
    gfxQueueFamily m_QueueFamily;
    gfxRenderPass m_RenderPass;
    gfxPipelineGraphics m_Pipeline;
};

wxBEGIN_EVENT_TABLE(epiWXVulkanDemoTriangleCanvas, epiWXVulkanCanvas)
    EVT_PAINT(epiWXVulkanDemoTriangleCanvas::OnPaint)
    EVT_ERASE_BACKGROUND(epiWXVulkanDemoTriangleCanvas::OnEraseBackground)
wxEND_EVENT_TABLE()

void epiWXVulkanDemoTriangleCanvas::OnPaint(wxPaintEvent& event)
{
    m_SwapChain.Present(m_QueueFamily[0]);
}

void epiWXVulkanDemoTriangleCanvas::OnEraseBackground(wxEraseEvent&)
{
    // NOTE: should reduce flickering
}

DECLARE_APP(EpiwxVulkanDemo)

IMPLEMENT_APP_NO_MAIN(EpiwxVulkanDemo);
IMPLEMENT_WX_THEME_SUPPORT;

int main(int argc, char* argv[])
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("%^[%l][%H:%M:%S:%e][thread %t] %v%$");

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
