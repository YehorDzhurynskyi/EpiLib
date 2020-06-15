#pragma once

#include "EpiUI/uiContext.h"

#include "EpiGraphics/gfxContext.h"
#include "EpiGraphics/gfxShaderProgram.h"
#include "EpiGraphics/Text/gfxTextManager.h"
#include "EpiGraphics/Text/gfxTextRenderedAtlas.h"

#include "EpiDataVisualization/Plot/dvPlot.h"
#include "EpiDataVisualization/Plot/Series/dvSeriesY.h"

#include <wx/glcanvas.h>

namespace epi
{
class dvViewPlot;
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

    epi::gfxTextManager m_TextManager;

    epi::dvViewPlot* m_ViewPlot;
    epi::dvPlot m_Plot;
};