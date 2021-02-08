#include "EpiwxWidgets/Vulkan/epiWXVulkanCanvas.h"

#include <vulkan/vulkan.hpp>

epiWXVulkanCanvas::epiWXVulkanCanvas(wxWindow* parent,
                                     wxWindowID id,
                                     const wxPoint& pos,
                                     const wxSize& size,
                                     long style,
                                     const wxString& name,
                                     const wxPalette& palette)
{
    Create(parent, id, pos, size, style, name, palette);
}

epiWXVulkanCanvas::~epiWXVulkanCanvas()
{
    // TODO: implement
    // ::ReleaseDC(GetHwnd(), m_hDC);
}

#if 0
// Replaces wxWindow::Create functionality, since we need to use a different
// window class
bool epiWXVulkanCanvas::CreateWindow(wxWindow* parent,
                              wxWindowID id,
                              const wxPoint& pos,
                              const wxSize& size,
                              long style,
                              const wxString& name)
{
    wxCHECK_MSG(parent, false, wxT("can't create wxWindow without parent"));

    if (!CreateBase(parent, id, pos, size, style, wxDefaultValidator, name))
        return false;

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

    if (!MSWCreate(wxApp::GetRegisteredClassName(wxT("epiWXVulkanCanvas"), -1, CS_OWNDC),
        NULL, pos, size, msflags, exStyle))
        return false;

    m_hDC = ::GetDC(GetHwnd());
    if (!m_hDC)
        return false;

    return true;
}
#endif

bool epiWXVulkanCanvas::Create(wxWindow* parent,
                               wxWindowID id,
                               const wxPoint& pos,
                               const wxSize& size,
                               long style,
                               const wxString& name,
                               const wxPalette& palette)
{
#if 0
    if (!CreateWindow(parent, id, pos, size, style, name))
        return false;

    // Choose a matching pixel format.
    // Need a PIXELFORMATDESCRIPTOR for SetPixelFormat()
    PIXELFORMATDESCRIPTOR pfd;
    int pixelFormat = FindMatchingPixelFormat(dispAttrs, &pfd);
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
    if (!::SetPixelFormat(m_hDC, pixelFormat, &pfd))
    {
        wxLogLastError("SetPixelFormat");
        return false;
    }

#if wxUSE_PALETTE
    if (!SetupPalette(palette))
        return false;
#else // !wxUSE_PALETTE
    wxUnusedVar(palette);
#endif // wxUSE_PALETTE/!wxUSE_PALETTE
#endif

    return true;
}

// ----------------------------------------------------------------------------
// operations
// ----------------------------------------------------------------------------

bool epiWXVulkanCanvas::SwapBuffers()
{
#if 0
    if (!::SwapBuffers(m_hDC))
    {
        wxLogLastError(wxT("SwapBuffers"));
        return false;
    }
#endif

    return true;
}
