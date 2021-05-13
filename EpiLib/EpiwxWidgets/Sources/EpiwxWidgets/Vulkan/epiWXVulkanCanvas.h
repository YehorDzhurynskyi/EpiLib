#pragma once

#include "EpiGraphicsDriverCommon/gfxSurface.h"
#include "EpiGraphicsDriverCommon/gfxSwapChain.h"
#include "EpiGraphicsDriverCommon/gfxPhysicalDevice.h"
#include "EpiGraphicsDriverCommon/gfxDevice.h"
#include "EpiGraphicsDriverCommon/gfxRenderPass.h"
#include "EpiGraphicsDriverCommon/gfxQueueFamily.h"

#include <wx/defs.h>
#include <wx/app.h>
#include <wx/palette.h>
#include <wx/window.h>

struct epiWXVulkanCanvasCreateInfo
{
    epi::gfxPhysicalDevice PhysicalDevice;
    epi::gfxDevice Device;
    epi::gfxRenderPass RenderPass;
    epi::gfxQueueFamily QueueFamily;
    epi::gfxSurfaceFormat Format{};
    epi::gfxSurfacePresentMode PresentMode{};
};

class epiWXVulkanCanvas : public wxWindow
{
public:
    epiWXVulkanCanvas() = default;
    epiWXVulkanCanvas(const epiWXVulkanCanvasCreateInfo& info,
                      wxWindow* parent,
                      wxWindowID id = wxID_ANY,
                      const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxDefaultSize,
                      long style = 0,
                      const wxString& name = wxASCII_STR("epiWXVulkanCanvas"),
                      const wxPalette& palette = wxNullPalette);
    virtual ~epiWXVulkanCanvas();

    epiBool Create(const epiWXVulkanCanvasCreateInfo& info,
                   wxWindow* parent,
                   wxWindowID id = wxID_ANY,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = 0,
                   const wxString& name = wxASCII_STR("epiWXVulkanCanvas"),
                   const wxPalette& palette = wxNullPalette);

    epiBool SwapBuffers();

protected:
    epiBool SetupPalette(const wxPalette& palette);

    virtual wxPalette CreateDefaultPalette() { return wxNullPalette; }

protected:
    HDC m_HDC{nullptr};

    wxPalette m_Palette;

    epi::gfxSurface m_Surface;
    epi::gfxSwapChain m_SwapChain;
};
