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
    const epi::gfxPhysicalDevice& PhysicalDevice;
    epi::gfxSurfaceFormat Format{};
    epi::gfxSurfacePresentMode PresentMode{};
};

class epiWXVulkanCanvas : public wxWindow
{
private:
    wxDECLARE_EVENT_TABLE();
    wxDECLARE_CLASS(epiWXVulkanCanvas);

public:
    epiBool Create(const epiWXVulkanCanvasCreateInfo& info,
                   wxWindow* parent,
                   wxWindowID id = wxID_ANY,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = 0,
                   const wxString& name = wxASCII_STR("epiWXVulkanCanvas"));

    epiBool CreateSwapChain(const epi::gfxPhysicalDevice& physicalDevice,
                            const epi::gfxDevice& device,
                            epi::gfxQueueFamily& queueFamily,
                            const epi::gfxRenderPassCreateInfo& renderPassContract);

    epiBool Present(const epi::gfxQueue& queue);

protected:
    epi::gfxSurface m_Surface;
    epi::gfxSwapChain m_SwapChain;
};
