#pragma once

#include <wx/window.h>

#include "EpiGraphicsDriverCommon/gfxSurface.h"
#include "EpiGraphicsDriverCommon/gfxSwapChain.h"
#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.h"
#include "EpiGraphicsDriverCommon/gfxDevice.h"
#include "EpiGraphicsDriverCommon/gfxRenderPass.h"
#include "EpiGraphicsDriverCommon/gfxQueueFamily.h"

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

protected:
    epi::gfxSurface m_Surface;
    epi::gfxSwapChain m_SwapChain;
};
