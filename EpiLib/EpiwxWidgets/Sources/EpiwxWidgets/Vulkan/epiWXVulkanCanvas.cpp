#include "EpiwxWidgets/Vulkan/epiWXVulkanCanvas.h"

#include "EpiGraphicsDriver/gfxDriver.h"
#include "EpiGraphicsDriverCommon/gfxDevice.h"
#include "EpiGraphicsDriverCommon/gfxWindow.h"
#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.h"

#include <Windows.h>
#include <WinUser.h>

#include <wx/app.h>

EPI_NAMESPACE_USING()

epiWXVulkanCanvas::epiWXVulkanCanvas(const epiWXVulkanCanvasCreateInfo& info,
                                     wxWindow* parent,
                                     wxWindowID id,
                                     const wxPoint& pos,
                                     const wxSize& size,
                                     long style,
                                     const wxString& name)
{
    Create(info, parent, id, pos, size, style, name);
}

bool epiWXVulkanCanvas::Create(const epiWXVulkanCanvasCreateInfo& info,
                               wxWindow* parent,
                               wxWindowID id,
                               const wxPoint& pos,
                               const wxSize& size,
                               long style,
                               const wxString& name)
{
    wxCHECK_MSG(parent, false, wxT("can't create wxWindow without parent"));

    if (!CreateBase(parent, id, pos, size, style, wxDefaultValidator, name))
    {
        epiLogError("Falied to CreateBase!");
        return false;
    }

    parent->AddChild(this);

    /*
       A general rule with OpenGL and Win32 is that any window that will have a
       HGLRC built for it must have two flags:  WS_CLIPCHILDREN & WS_CLIPSIBLINGS.
       You can find references about this within the knowledge base and most OpenGL
       books that contain the wgl function descriptions.
     */
    WXDWORD exStyle = 0;
    DWORD msflags = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    msflags |= MSWGetStyle(style, &exStyle);

    if (!MSWCreate(wxApp::GetRegisteredClassName(wxT("epiWXVulkanCanvas"), -1, CS_OWNDC), nullptr, pos, size, msflags, exStyle))
    {
        epiLogError("Falied to MSWCreate!");
        return false;
    }

    gfxWindow window(parent->GetHandle());
    std::optional<gfxSurface> surface = gfxDriver::GetInstance().CreateSurface(window);
    if (!surface.has_value())
    {
        epiLogError("Falied to create Surface!");
        return false;
    }

    m_Surface = std::move(*surface);

    gfxSwapChainCreateInfo swapChainCreateInfo = info.SwapChainCreateInfo;
    swapChainCreateInfo.SetSurface(&m_Surface);

    std::optional<gfxSwapChain> swapChain = info.Device->CreateSwapChain(swapChainCreateInfo);
    if (!swapChain.has_value())
    {
        epiLogError("Falied to create SwapChain!");
        return false;
    }

    m_SwapChain = std::move(*swapChain);

    return true;
}

bool epiWXVulkanCanvas::Present(const epi::gfxQueue& queue)
{
    return m_SwapChain.Present(queue);
}
