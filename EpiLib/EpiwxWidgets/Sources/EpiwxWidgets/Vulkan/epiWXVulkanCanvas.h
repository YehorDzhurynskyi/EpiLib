#pragma once

#include <wx/window.h>

#include "EpiGraphicsDriverCommon/gfxSurface.h"

EPI_NAMESPACE_BEGIN()

class gfxWindow;
class gfxDevice;
class gfxSwapChainCreateInfo;

EPI_NAMESPACE_END()

class epiWXVulkanCanvas : public wxWindow
{
private:
    wxDECLARE_EVENT_TABLE();
    wxDECLARE_CLASS(epiWXVulkanCanvas);

public:
    epiWXVulkanCanvas() = default;

    epiWXVulkanCanvas(gfxSurface&& surface,
                      gfxSwapChain&& swapChain,
                      wxWindow* parent,
                      wxWindowID id = wxID_ANY,
                      const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxDefaultSize,
                      long style = 0,
                      const wxString& name = wxASCII_STR("epiWXVulkanCanvas"));

public:
    bool Create(const epiWXVulkanCanvasCreateInfo& info,
                wxWindow* parent,
                wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxString& name = wxASCII_STR("epiWXVulkanCanvas"));

    bool Present(const epi::gfxQueue& queue);

protected:
    epi::gfxSurface m_Surface;
    epi::gfxSwapChain m_SwapChain;
};
