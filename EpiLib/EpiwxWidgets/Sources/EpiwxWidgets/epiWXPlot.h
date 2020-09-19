#pragma once

#include "EpiUI/uiContext.h"

#include "EpiGraphics/gfxContext.h"

#include <wx/glcanvas.h>

namespace epi
{
class uiPlot;
}

class epiWXPlot : public wxGLCanvas
{
public:
    wxDECLARE_EVENT_TABLE();

public:
    epiWXPlot(wxWindow *parent,
              const wxGLAttributes& attribList,
              wxWindowID id = wxID_ANY,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize,
              long style = 0,
              const wxString& name = wxGLCanvasName,
              const wxPalette& palette = wxNullPalette);

    void OnResize(wxSizeEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnIdle(wxIdleEvent& event);
    void OnMouse(wxMouseEvent& event);

protected:
    wxGLContext* m_GLContext;
    epi::uiContext* m_UIContext;

    epi::uiPlot* m_PlotView;
};