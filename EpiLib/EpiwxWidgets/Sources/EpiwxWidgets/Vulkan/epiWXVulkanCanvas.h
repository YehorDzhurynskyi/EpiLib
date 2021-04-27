#pragma once

#include <wx/window.h>

#include "EpiGraphicsDriverCommon/gfxSurface.h"

EPI_NAMESPACE_BEGIN()

class gfxPhysicalDevice;
class gfxDevice;
class gfxQueueFamily;
class gfxRenderPassCreateInfo;

EPI_NAMESPACE_END()

struct epiWXVulkanCanvasCreateInfo
{
    epi::gfxPhysicalDevice PhysicalDevice;
    epi::gfxDevice Device;
    epi::gfxRenderPassSchema RenderPassSchema;
    epi::gfxQueueFamily QueueFamily;
    epi::gfxSurfaceFormat Format{};
    epi::gfxSurfacePresentMode PresentMode{};
};

class epiWXVulkanCanvas : public wxWindow
{
private:
    wxDECLARE_EVENT_TABLE();
    wxDECLARE_CLASS(epiWXVulkanCanvas);

public:
    epiWXVulkanCanvas() = default;
    epiWXVulkanCanvas(const epiWXVulkanCanvasCreateInfo& info,
                      wxWindow* parent,
                      wxWindowID id = wxID_ANY,
                      const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxDefaultSize,
                      long style = 0,
                      const wxString& name = wxASCII_STR("epiWXVulkanCanvas"));

    epiBool Create(const epiWXVulkanCanvasCreateInfo& info,
                   wxWindow* parent,
                   wxWindowID id = wxID_ANY,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = 0,
                   const wxString& name = wxASCII_STR("epiWXVulkanCanvas"));

    epiBool Present(const epi::gfxQueue& queue);

protected:
    epi::gfxSurface m_Surface;
    epi::gfxSwapChain m_SwapChain;
};
