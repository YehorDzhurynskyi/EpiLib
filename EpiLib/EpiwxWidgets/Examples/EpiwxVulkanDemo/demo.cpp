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
    const std::unique_ptr<epi::gfxSurface> surface = epi::gfxDriver::GetInstance().CreateSurface(epi::gfxWindow());
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

    std::optional<epi::gfxSwapChain> swapChain = surface->CreateSwapChain(*device,
                                                                          surfaceCapabilities,
                                                                          surfaceFormat,
                                                                          epi::gfxSurfacePresentMode::MAILBOX,
                                                                          extent);
    epiAssert(swapChain.has_value());

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
