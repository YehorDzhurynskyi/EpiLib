#pragma once

#include "EpiGraphicsDriver/gfxDriver.h"
#include "EpiGraphicsDriver/gfxPhysicalDevice.h"

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

    epi::gfxDriver::GetInstance().SetBackend(epi::gfxDriverBackend::Vulkan);
    epi::epiArray<epi::gfxPhysicalDevice>& physicalDevices = epi::gfxDriver::GetInstance().GetPhysicalDevices();
    auto devIt = std::find_if(physicalDevices.begin(), physicalDevices.end(), [](const epi::gfxPhysicalDevice& dev)
    {
        const epi::gfxQueueType requiredQueueTypes = epi::gfxQueueType_Graphics;

        // TODO: epi::gfxPhysicalDeviceExtension should be filtered here
        return dev.GetType() == epi::gfxPhysicalDeviceType::DiscreteGPU &&
               dev.IsQueueTypeSupported(requiredQueueTypes) &&
               dev.GetIsPresentSupported();
    });
    epiAssert(devIt != physicalDevices.end());
    epi::gfxPhysicalDevice& dev = *devIt;

    constexpr bool kIsPresentSupportRequired = true;
    epi::gfxDevice* device = dev.AddDevice(epi::gfxQueueType_Graphics, epi::gfxPhysicalDeviceExtension_SwapChain, kIsPresentSupportRequired);
    epiAssert(device != nullptr);

    epi::gfxQueue* queue = device->GetQueue(epi::gfxQueueType_Graphics, kIsPresentSupportRequired);
    epiAssert(queue != nullptr);

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
    SetSizeHints(wxDefaultSize, wxDefaultSize);
    Centre(wxBOTH);
}
