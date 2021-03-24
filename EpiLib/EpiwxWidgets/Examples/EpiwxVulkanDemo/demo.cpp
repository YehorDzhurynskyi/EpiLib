#pragma once

#include "EpiGraphicsDriver/gfxDriver.h"
#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.h"
#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.h"

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/window.h>

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

    epi::gfxDriver::GetInstance().SetBackend(epi::gfxDriverBackend::Vulkan);
    std::optional<epi::gfxSurface> surface = epi::gfxDriver::GetInstance().CreateSurface(epi::gfxWindow());
    epiAssert(surface.has_value());

    std::optional<epi::gfxPhysicalDevice> physicalDevice = epi::gfxDriver::GetInstance().FindAppropriatePhysicalDevice([&surface](const epi::gfxPhysicalDevice& device)
    {
        if (device.GetType() != epi::gfxPhysicalDeviceType::DiscreteGPU ||
            !device.IsExtensionsSupported(epi::gfxPhysicalDeviceExtension_SwapChain) ||
            !device.IsQueueTypeSupported(epi::gfxQueueType_Graphics))
        {
            return false;
        }

        const epi::epiArray<epi::gfxSurfaceFormat> supportedFormats = surface->GetSupportedFormatsFor(device);
        const epiBool formatIsAppropriate = std::any_of(supportedFormats.begin(), supportedFormats.end(), [](const epi::gfxSurfaceFormat& format)
        {
            return format.GetFormat() == epi::gfxFormat::B8G8R8A8_SRGB && format.GetColorSpace() == epi::gfxSurfaceColorSpace::SRGB_NONLINEAR;
        });

        if (!formatIsAppropriate)
        {
            return false;
        }

        const epi::epiArray<epi::gfxSurfacePresentMode> supportedPresentModes = surface->GetSupportedPresentModesFor(device);
        const epiBool presentModeIsAppropriate = std::any_of(supportedPresentModes.begin(), supportedPresentModes.end(), [](const epi::gfxSurfacePresentMode& presentMode)
        {
            return presentMode == epi::gfxSurfacePresentMode::MAILBOX;
        });

        if (!presentModeIsAppropriate)
        {
            return false;
        }

        return surface->IsPresentSupportedFor(device);
    });

    epiAssert(physicalDevice.has_value());

    epi::gfxQueueDescriptorList queueDescriptorList;
    queueDescriptorList.Add(surface->CreateQueueDescriptor({1.0f}));

    std::optional<epi::gfxDevice> device = physicalDevice->CreateDevice(queueDescriptorList, epi::gfxPhysicalDeviceExtension_SwapChain);
    epiAssert(device.has_value());

    epi::gfxSurfaceFormat surfaceFormat;
    surfaceFormat.SetFormat(epi::gfxFormat::B8G8R8A8_SRGB);
    surfaceFormat.SetColorSpace(epi::gfxSurfaceColorSpace::SRGB_NONLINEAR);

    const epi::gfxSurfaceCapabilities surfaceCapabilities = surface->GetCapabilitiesFor(*physicalDevice);
    epiSize2u extent{};
    if (surfaceCapabilities.GetCurrentExtent().x != std::numeric_limits<epiU32>::max())
    {
        extent = surfaceCapabilities.GetCurrentExtent();
    }
    else
    {
        const wxSize frameSize = m_Frame->GetSize();

        extent.x = std::clamp(static_cast<epiU32>(frameSize.x), surfaceCapabilities.GetMinImageExtent().x, surfaceCapabilities.GetMaxImageExtent().x);
        extent.y = std::clamp(static_cast<epiU32>(frameSize.y), surfaceCapabilities.GetMinImageExtent().y, surfaceCapabilities.GetMaxImageExtent().y);
    }

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

    std::optional<epi::gfxShader> vertexShader = device->CreateShaderFromSource(kVertexShaderModule.c_str(), epi::gfxShaderType::Vertex);
    std::optional<epi::gfxShader> fragmentShader = device->CreateShaderFromSource(kFragmentShaderModule.c_str(), epi::gfxShaderType::Fragment);

    epiAssert(vertexShader.has_value());
    epiAssert(fragmentShader.has_value());

    epi::gfxShaderProgramCreateInfo shaderProgramCreateInfo;
    shaderProgramCreateInfo.SetVertex(&*vertexShader);
    shaderProgramCreateInfo.SetFragment(&*fragmentShader);

    std::optional<epi::gfxShaderProgram> shaderProgram = device->CreateShaderProgram(shaderProgramCreateInfo);

    epi::gfxAttachment attachment;
    attachment.SetFormat(surfaceFormat.GetFormat());
    attachment.SetSampleCount(epi::gfxSampleCount::Sample1);
    attachment.SetLoadOp(epi::gfxAttachmentLoadOp::Clear);
    attachment.SetStoreOp(epi::gfxAttachmentStoreOp::Store);
    attachment.SetStencilLoadOp(epi::gfxAttachmentLoadOp::DontCare);
    attachment.SetStencilStoreOp(epi::gfxAttachmentStoreOp::DontCare);
    attachment.SetInitialLayout(epi::gfxImageLayout::Undefined);
    attachment.SetFinalLayout(epi::gfxImageLayout::PresentSrc);

    epi::gfxRenderSubPass renderSubPass;
    renderSubPass.SetBindPoint(epi::gfxPipelineBindPoint::Graphics);
    renderSubPass.AddAttachment(attachment, 0, epi::gfxImageLayout::ColorAttachmentOptimal);

    epi::gfxRenderSubPassDependency renderSubPassDependency;
    renderSubPassDependency.SetIsSrcSubPassExternal(true);
    renderSubPassDependency.SetDstSubPass(0);
    renderSubPassDependency.SetSrcStageMask(epi::gfxPipelineStage_ColorAttachmentOutput);
    renderSubPassDependency.SetSrcAccessMask(epi::gfxAccess{0});
    renderSubPassDependency.SetDstStageMask(epi::gfxPipelineStage_ColorAttachmentOutput);
    renderSubPassDependency.SetDstAccessMask(epi::gfxAccess_ColorAttachmentWrite);

    epi::gfxRenderPassCreateInfo renderPassCreateInfo;
    renderPassCreateInfo.AddSubPass(std::move(renderSubPass));
    renderPassCreateInfo.AddSubPassDependency(std::move(renderSubPassDependency));

    std::optional<epi::gfxRenderPass> renderPass = device->CreateRenderPass(renderPassCreateInfo);
    epiAssert(renderPass.has_value());

    epi::gfxSwapChainCreateInfo swapChainCreateInfo;
    swapChainCreateInfo.SetCapabilities(surfaceCapabilities);
    swapChainCreateInfo.SetFormat(surfaceFormat);
    swapChainCreateInfo.SetPresentMode(epi::gfxSurfacePresentMode::MAILBOX);
    swapChainCreateInfo.SetExtent(extent);
    swapChainCreateInfo.SetSurface(&*surface);
    swapChainCreateInfo.SetRenderPass(&*renderPass);

    std::optional<epi::gfxSwapChain> swapChain = device->CreateSwapChain(swapChainCreateInfo);
    epiAssert(swapChain.has_value());

    epi::gfxPipelineViewport viewport;
    viewport.SetViewportRect(epiRect2f(0.0f, 0.0f, extent.x, extent.y));
    viewport.SetViewportMinDepth(0.0f);
    viewport.SetViewportMaxDepth(1.0f);

    epi::gfxPipelineColorBlendAttachment colorBlendAttachment;
    colorBlendAttachment.SetColorWriteMask(epi::gfxColorComponent_RGBA);
    colorBlendAttachment.SetBlendEnable(false);
    colorBlendAttachment.SetSrcColorBlendFactor(epi::gfxBlendFactor::One);
    colorBlendAttachment.SetDstColorBlendFactor(epi::gfxBlendFactor::Zero);
    colorBlendAttachment.SetColorBlendOp(epi::gfxBlendOp::Add);
    colorBlendAttachment.SetSrcAlphaBlendFactor(epi::gfxBlendFactor::One);
    colorBlendAttachment.SetDstAlphaBlendFactor(epi::gfxBlendFactor::Zero);
    colorBlendAttachment.SetAlphaBlendOp(epi::gfxBlendOp::Add);

    epi::gfxPipelineCreateInfo pipelineCreateInfo;
    pipelineCreateInfo.SetInputAssemblyType(epi::gfxPipelineInputAssemblyType::TriangleList);
    pipelineCreateInfo.AddViewport(viewport);
    pipelineCreateInfo.AddScissor(epiRect2s(0, 0, extent.x, extent.y));
    pipelineCreateInfo.SetDepthClampEnable(false);
    pipelineCreateInfo.SetRasterizerDiscardEnable(false);
    pipelineCreateInfo.SetPolygonMode(epi::gfxPolygonMode::Fill);
    pipelineCreateInfo.SetLineWidth(1.0f);
    pipelineCreateInfo.SetCullMode(epi::gfxCullMode::Back);
    pipelineCreateInfo.SetFrontFace(epi::gfxFrontFace::CW);
    pipelineCreateInfo.SetDepthClampEnable(false);
    pipelineCreateInfo.SetDepthBiasConstantFactor(0.0f);
    pipelineCreateInfo.SetDepthBiasClamp(0.0f);
    pipelineCreateInfo.SetDepthBiasSlopeFactor(0.0f);
    pipelineCreateInfo.AddColorBlendAttachment(colorBlendAttachment);
    pipelineCreateInfo.SetColorBlendLogicOpEnable(false);
    pipelineCreateInfo.SetColorBlendLogicOp(epi::gfxLogicOp::Copy);
    pipelineCreateInfo.SetColorBlendConstants(epiVec4f{0.0f, 0.0f, 0.0f, 0.0f});
    pipelineCreateInfo.SetRenderPass(&*renderPass);
    pipelineCreateInfo.SetRenderSubPassIndex(0);
    pipelineCreateInfo.SetShaderProgram(&*shaderProgram);

    std::optional<epi::gfxPipeline> pipeline = device->CreatePipeline(pipelineCreateInfo);
    epiAssert(pipeline.has_value());

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
    SetSizeHints(wxDefaultSize, wxDefaultSize);
    Centre(wxBOTH);
}
