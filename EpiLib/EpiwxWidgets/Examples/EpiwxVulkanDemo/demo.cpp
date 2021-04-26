#pragma once

#include "EpiGraphicsDriver/gfxDriver.h"

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/window.h>

#include "EpiwxWidgets/Vulkan/epiWXVulkanCanvas.h"

EPI_NAMESPACE_USING()

gfxPhysicalDevice g_PhysicalDevice;
gfxDevice g_Device;

class EpiwxVulkanDemoFrame : public wxFrame
{
public:
    EpiwxVulkanDemoFrame(wxWindow* parent,
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
    EpiwxVulkanDemoFrame* m_Frame;
};

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
    deviceExtensionsRequired.push_back(gfxPhysicalDeviceExtension::ImageLessFrameBuffer);
    deviceExtensionsRequired.push_back(gfxPhysicalDeviceExtension::ImageFormatList);

    epiArray<gfxPhysicalDeviceFeature> deviceFeaturesRequired;
    deviceFeaturesRequired.push_back(gfxPhysicalDeviceFeature::ImagelessFramebuffer);

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
            return format.GetFormat() == gfxFormat::B8G8R8A8_SRGB && format.GetColorSpace() == gfxSurfaceColorSpace::SRGB_NONLINEAR;
        });

        if (!formatIsAppropriate)
        {
            return false;
        }

        const epiArray<gfxSurfacePresentMode> supportedPresentModes = surface->GetSupportedPresentModesFor(physicalDevice);
        const epiBool presentModeIsAppropriate = std::any_of(supportedPresentModes.begin(), supportedPresentModes.end(), [](const gfxSurfacePresentMode& presentMode)
        {
            return presentMode == gfxSurfacePresentMode::MAILBOX;
        });

        if (!presentModeIsAppropriate)
        {
            return false;
        }

        return surface->IsPresentSupportedFor(physicalDevice);
    });

    if (physicalDevice == physicalDevices.end())
    {
        epiLogError("Falied to select a proper PhysicalDevice!");
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

    m_Frame = new EpiwxVulkanDemoFrame(nullptr);
    m_Frame->SetPosition(wxDefaultPosition);
    m_Frame->Show(true);

    SetTopWindow(m_Frame);

    return true;
}

int EpiwxVulkanDemo::OnExit()
{
    delete m_Frame;
    return wxApp::OnExit();
}

EpiwxVulkanDemoFrame::EpiwxVulkanDemoFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxFrame(parent, id, title, pos, size, style)
{
    gfxAttachment attachment;
    attachment.SetFormat(gfxFormat::B8G8R8A8_SRGB);
    attachment.SetSampleCount(gfxSampleCount::Sample1);
    attachment.SetLoadOp(gfxAttachmentLoadOp::Clear);
    attachment.SetStoreOp(gfxAttachmentStoreOp::Store);
    attachment.SetStencilLoadOp(gfxAttachmentLoadOp::DontCare);
    attachment.SetStencilStoreOp(gfxAttachmentStoreOp::DontCare);
    attachment.SetInitialLayout(gfxImageLayout::Undefined);
    attachment.SetFinalLayout(gfxImageLayout::PresentSrc);

    gfxRenderSubPass renderSubPass;
    renderSubPass.SetBindPoint(gfxPipelineBindPoint::Graphics);
    renderSubPass.AddAttachment(attachment, 0, gfxImageLayout::ColorAttachmentOptimal);

    gfxRenderSubPassDependency renderSubPassDependency;
    renderSubPassDependency.SetIsSrcSubPassExternal(true);
    renderSubPassDependency.SetDstSubPass(0);
    renderSubPassDependency.SetSrcStageMask(gfxPipelineStage_ColorAttachmentOutput);
    renderSubPassDependency.SetSrcAccessMask(gfxAccess{0});
    renderSubPassDependency.SetDstStageMask(gfxPipelineStage_ColorAttachmentOutput);
    renderSubPassDependency.SetDstAccessMask(gfxAccess_ColorAttachmentWrite);

    gfxRenderPassCreateInfo renderPassCreateInfo;
    renderPassCreateInfo.AddSubPass(std::move(renderSubPass));
    renderPassCreateInfo.AddSubPassDependency(std::move(renderSubPassDependency));

    std::optional<gfxRenderPass> renderPass = device->CreateRenderPass(renderPassCreateInfo);
    epiAssert(renderPass.has_value());

    epiWXVulkanCanvasCreateInfo canvasCreateInfo{.PhysicalDevice = *physicalDevice};

    AddChild(new epiWXVulkanCanvas(canvasCreateInfo, this));

    gfxPipelineViewport viewport;
    viewport.SetViewportRect(epiRect2f(0.0f, 0.0f, extent.x, extent.y));
    viewport.SetViewportMinDepth(0.0f);
    viewport.SetViewportMaxDepth(1.0f);

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

    std::optional<gfxShader> vertexShader = device->CreateShaderFromSource(kVertexShaderModule.c_str(), gfxShaderType::Vertex);
    std::optional<gfxShader> fragmentShader = device->CreateShaderFromSource(kFragmentShaderModule.c_str(), gfxShaderType::Fragment);

    epiAssert(vertexShader.has_value());
    epiAssert(fragmentShader.has_value());

    gfxShaderProgramCreateInfo shaderProgramCreateInfo;
    shaderProgramCreateInfo.SetVertex(&*vertexShader);
    shaderProgramCreateInfo.SetFragment(&*fragmentShader);

    std::optional<gfxShaderProgram> shaderProgram = device->CreateShaderProgram(shaderProgramCreateInfo);
    epiAssert(shaderProgram.has_value());

    gfxPipelineCreateInfo pipelineCreateInfo;
    pipelineCreateInfo.SetInputAssemblyType(gfxPipelineInputAssemblyType::TriangleList);
    pipelineCreateInfo.AddViewport(viewport);
    pipelineCreateInfo.AddScissor(epiRect2s(0, 0, extent.x, extent.y));
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
    pipelineCreateInfo.SetShaderProgram(&*shaderProgram);

    std::optional<gfxPipeline> pipeline = device->CreatePipeline(pipelineCreateInfo);
    epiAssert(pipeline.has_value());

    SetSizeHints(wxDefaultSize, wxDefaultSize);
    Centre(wxBOTH);
}
