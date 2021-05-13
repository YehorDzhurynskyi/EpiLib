#include "EpiwxWidgets/Vulkan/epiWXVulkanCanvas.h"

#include "EpiGraphicsDriver/gfxDriver.h"
#include "EpiGraphicsDriverCommon/gfxDevice.h"
#include "EpiGraphicsDriverCommon/gfxWindow.h"
#include "EpiGraphicsDriverCommon/gfxEnum.h"
#include "EpiGraphicsDriverCommon/gfxQueueDescriptor.h"

#include <wx/app.h>

EPI_NAMESPACE_USING()

epiWXVulkanCanvas::epiWXVulkanCanvas(const epiWXVulkanCanvasCreateInfo& info,
                                     wxWindow* parent,
                                     wxWindowID id,
                                     const wxPoint& pos,
                                     const wxSize& size,
                                     long style,
                                     const wxString& name,
                                     const wxPalette& palette)
{
    Create(info, parent, id, pos, size, style, name, palette);
}

epiWXVulkanCanvas::~epiWXVulkanCanvas()
{
    ::ReleaseDC(GetHWND(), m_HDC);
}

epiBool epiWXVulkanCanvas::Create(const epiWXVulkanCanvasCreateInfo& info,
                                  wxWindow* parent,
                                  wxWindowID id,
                                  const wxPoint& pos,
                                  const wxSize& size,
                                  long style,
                                  const wxString& name,
                                  const wxPalette& palette)
{
    if (gfxDriver::GetInstance().GetBackend() == gfxDriverBackend::None)
    {
        epiLogError("Graphics driver backend isn't selected!");
        return false;
    }

    if (!gfxDriver::GetInstance().IsExtensionEnabled(gfxDriverExtension::Surface))
    {
        epiLogError("Graphics driver doesn't has Surface extension enabled!");
        return false;
    }

    if (!info.Device.IsExtensionEnabled(gfxPhysicalDeviceExtension::SwapChain))
    {
        epiLogError("Provided Device doesn't has SwapChain extension enabled!");
        return false;
    }

    if (parent == nullptr)
    {
        epiLogError("Can't create wxWindow without parent!");
        return false;
    }

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

    m_HDC = ::GetDC(GetHWND());
    if (!m_HDC)
    {
        epiLogError("Falied to GetDC!");
        return false;
    }

    // Choose a matching pixel format.
    // Need a PIXELFORMATDESCRIPTOR for SetPixelFormat()
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,                      // version
        PFD_DRAW_TO_WINDOW |    // must support windowed
        PFD_SUPPORT_OPENGL |    // must support OpenGL
        PFD_DOUBLEBUFFER,       // must support double buffering
        PFD_TYPE_RGBA,          // iPixelType
        32,                     // cColorBits
        0, 0,                   // cRedBits, cRedShift
        0, 0,                   // cGreenBits, cGreenShift
        0, 0,                   // cBlueBits, cBlueShift
        0, 0,                   // cAlphaBits, cAlphaShift
        0,                      // cAccumBits
        0,                      // cAccumRedBits
        0,                      // cAccumGreenBits
        0,                      // cAccumBlueBits
        0,                      // cAccumAlphaBits
        0,                      // cDepthBits
        0,                      // cStencilBits
        0,                      // cAuxBuffers
        PFD_MAIN_PLANE,         // iLayerType
        0,                      // bReserved
        0,                      // dwLayerMask
        0,                      // dwVisibleMask
        0                       // dwDamageMask
    };
    const int pixelFormat = ::ChoosePixelFormat(m_HDC, &pfd);
    if (!pixelFormat)
    {
        wxFAIL_MSG("Can't find a pixel format for the requested attributes");
        return false;
    }

    // From SetPixelFormat() docs, relating pfd parameter:
    // https://msdn.microsoft.com/en-us/library/dd369049%28v=vs.85%29.aspx
    //   "The system's metafile component uses this structure to record the
    //   logical pixel format specification."
    // If anybody understands this sentence, please explain.
    // Pass pfd just in case it's somehow needed. Passing NULL also works here.
    if (!::SetPixelFormat(m_HDC, pixelFormat, &pfd))
    {
        wxLogLastError("SetPixelFormat");
        return false;
    }

#if wxUSE_PALETTE
    if (!SetupPalette(palette))
    {
        wxLogLastError("SetupPalette");
        return false;
    }
#endif // wxUSE_PALETTE

    gfxWindow window(GetHWND());
    std::optional<gfxSurface> surface = gfxDriver::GetInstance().CreateSurface(window);
    if (!surface.has_value())
    {
        epiLogError("Falied to create Surface!");
        return false;
    }

    // TODO: check whether device supports graphics queues
    if (!surface->IsCompatibleWith(info.PhysicalDevice, info.Format, info.PresentMode))
    {
        epiLogError("Surface isn't compatible with a provided PhysicalDevice={}!", info.PhysicalDevice.ToString());
        return false;
    }

    if (!surface->IsPresentSupportedFor(info.PhysicalDevice, info.QueueFamily))
    {
        epiLogError("Surface isn't compatible with a provided QueueFamily!");
        return false;
    }

    m_Surface = std::move(*surface);

    const gfxSurfaceCapabilities surfaceCapabilities = m_Surface.GetCapabilitiesFor(info.PhysicalDevice);

    epiSize2u extent{};
    if (surfaceCapabilities.GetCurrentExtent().x != std::numeric_limits<epiU32>::max())
    {
        extent = surfaceCapabilities.GetCurrentExtent();
    }
    else
    {
        extent.x = std::clamp(static_cast<epiU32>(GetSize().x), surfaceCapabilities.GetMinImageExtent().x, surfaceCapabilities.GetMaxImageExtent().x);
        extent.y = std::clamp(static_cast<epiU32>(GetSize().y), surfaceCapabilities.GetMinImageExtent().y, surfaceCapabilities.GetMaxImageExtent().y);
    }

    // TODO: submit RenderPass info to ensure compatibility only
    gfxSwapChainCreateInfo swapChainCreateInfo{};
    swapChainCreateInfo.SetSurface(m_Surface);
    swapChainCreateInfo.SetRenderPass(info.RenderPass);
    swapChainCreateInfo.SetQueueFamily(info.QueueFamily);
    swapChainCreateInfo.SetCapabilities(surfaceCapabilities);
    swapChainCreateInfo.SetFormat(info.Format);
    swapChainCreateInfo.SetPresentMode(info.PresentMode);
    swapChainCreateInfo.SetExtent(extent);

    std::optional<gfxSwapChain> swapChain = info.Device.CreateSwapChain(swapChainCreateInfo);
    if (!swapChain.has_value())
    {
        epiLogError("Falied to create SwapChain!");
        return false;
    }

    m_SwapChain = std::move(*swapChain);

    return true;
}

epiBool epiWXVulkanCanvas::SetupPalette(const wxPalette& palette)
{
    const int pixelFormat = ::GetPixelFormat(m_HDC);
    if (!pixelFormat)
    {
        epiLogError("GetPixelFormat");
        return false;
    }

    PIXELFORMATDESCRIPTOR pfd;
    if (!::DescribePixelFormat(m_HDC, pixelFormat, sizeof(pfd), &pfd))
    {
        epiLogError("DescribePixelFormat");
        return false;
    }

    if (!(pfd.dwFlags & PFD_NEED_PALETTE))
    {
        return true;
    }

    m_Palette = palette;

    if (!m_Palette.IsOk())
    {
        m_Palette = CreateDefaultPalette();
        if (!m_Palette.IsOk())
        {
            return false;
        }
    }

    if (!::SelectPalette(m_HDC, ((HPALETTE)(m_Palette).GetHPALETTE()), FALSE))
    {
        epiLogError("SelectPalette");
        return false;
    }

    if (::RealizePalette(m_HDC) == GDI_ERROR)
    {
        epiLogError("RealizePalette");
        return false;
    }

    return true;
}

epiBool epiWXVulkanCanvas::SwapBuffers()
{
    if (!::SwapBuffers(m_HDC))
    {
        epiLogError("SwapBuffers");
        return false;
    }

    return true;
}
