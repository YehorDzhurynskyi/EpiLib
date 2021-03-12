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
    spdlog::set_level(spdlog::level::trace);
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
    std::optional<epi::gfxPhysicalDevice> physicalDevice = epi::gfxDriver::GetInstance().FindAppropriatePhysicalDevice([&surface](const epi::gfxPhysicalDevice& device) {
        if (device.GetType() != epi::gfxPhysicalDeviceType::DiscreteGPU ||
            !device.IsExtensionsSupported(epi::gfxPhysicalDeviceExtension_SwapChain) ||
            !device.IsQueueTypeSupported(epi::gfxQueueType_Graphics))
        {
            return false;
        }

        const epi::epiArray<epi::gfxSurfaceFormat> supportedFormats = surface->GetSupportedFormatsFor(device);
        const epiBool formatIsAppropriate = std::any_of(supportedFormats.begin(), supportedFormats.end(), [](const epi::gfxSurfaceFormat& format) {
            return format.GetFormat() == epi::gfxFormat::R8G8B8_SRGB && format.GetColorSpace() == epi::gfxSurfaceColorSpace::SRGB_NONLINEAR;
        });

        return formatIsAppropriate && surface->IsPresentSupportedFor(device);
    });

    epiAssert(physicalDevice.has_value());

    epi::gfxQueueDescriptorList queueDescriptorList;
    queueDescriptorList.Add(surface->CreateQueueDescriptor({1.0f}));

    std::optional<epi::gfxDevice> device = physicalDevice->CreateDevice(queueDescriptorList, epi::gfxPhysicalDeviceExtension_SwapChain);
    epiAssert(device.has_value());

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
