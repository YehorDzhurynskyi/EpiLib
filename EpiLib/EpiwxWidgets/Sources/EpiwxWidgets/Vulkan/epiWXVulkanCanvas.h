#pragma once

#include "EpiGraphics/gfxSurface.h"
#include "EpiGraphics/gfxSwapChain.h"
#include "EpiGraphics/gfxPhysicalDevice.h"
#include "EpiGraphics/gfxDevice.h"
#include "EpiGraphics/gfxQueueFamily.h"

#include <wx/window.h>

struct epiWXVulkanCanvasCreateInfo
{
    epi::gfxPhysicalDevice PhysicalDevice;
    epi::gfxDevice Device;
    epi::gfxQueueFamily QueueFamily;
    epi::gfxSurfaceFormat Format{};
    epi::gfxSurfacePresentMode PresentMode{};
};

class epiWXVulkanCanvas : public wxWindow
{
public:
    epiWXVulkanCanvas() = default;
    epiWXVulkanCanvas(epiWXVulkanCanvasCreateInfo& info,
                      wxWindow* parent,
                      wxWindowID id = wxID_ANY,
                      const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxDefaultSize,
                      long style = 0,
                      const wxString& name = wxASCII_STR("epiWXVulkanCanvas"));

    epiBool Create(epiWXVulkanCanvasCreateInfo& info,
                   wxWindow* parent,
                   wxWindowID id = wxID_ANY,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = 0,
                   const wxString& name = wxASCII_STR("epiWXVulkanCanvas"));

protected: // TODO: make it private
    epi::gfxSurface m_Surface;
    epi::gfxSwapChain m_SwapChain;
};
