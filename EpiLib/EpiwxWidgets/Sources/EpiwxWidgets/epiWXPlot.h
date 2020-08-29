#pragma once

#include "EpiUI/uiContext.h"

#include "EpiGraphics/gfxContext.h"

#include "EpiDataVisualization/Plot/dvPlot.h"

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
    epiWXPlot(wxWindow* parent, const wxGLAttributes& attribList);

    void OnResize(wxSizeEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnIdle(wxIdleEvent& event);
    void OnMouse(wxMouseEvent& event);

protected:
    wxGLContext* m_GLContext;
    epi::uiContext* m_UIContext;

    epi::uiPlot* m_PlotView;
    epi::dvPlot m_PlotModel;
};