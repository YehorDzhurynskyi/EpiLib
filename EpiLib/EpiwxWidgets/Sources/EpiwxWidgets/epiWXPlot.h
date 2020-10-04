#pragma once

#include <wx/glcanvas.h>

#include "EpiDataVisualization/Plot/ViewModel/dvVMPlot.h"

EPI_NAMESPACE_BEGIN()

class uiPlot;
class uiContext;

EPI_NAMESPACE_END()

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
    void OnEraseBackground(wxEraseEvent& event);
    void OnIdle(wxIdleEvent& event);
    void OnMouse(wxMouseEvent& event);

    epi::dvVMPlot& GetViewModel();

protected:
    wxGLContext* m_GLContext;
    epi::uiContext* m_UIContext;
    epi::uiPlot* m_Plot;
};
