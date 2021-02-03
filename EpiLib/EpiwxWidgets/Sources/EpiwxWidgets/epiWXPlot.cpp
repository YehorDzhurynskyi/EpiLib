#include "EpiwxWidgets/epiWXPlot.h"

#include "EpiGraphics/gfxDrawerPrimitive.h"
#include "EpiGraphics/gfxDrawerText.h"

#include "EpiDataVisualization/Plot/ViewModel/dvVMSeriesBase.h"

#include "EpiUI/uiContext.h"
#include "EpiUI/Plot/uiPlot.h"
#include "EpiUI/Plot/uiPlotDrawArea.h"
#include "EpiUI/Plot/uiPlotTimeline.h"

#include "EpiCore/ObjectModel/Property/epiPropertyPointer.h"

#include <glad/glad.h>
#include <wx/wx.h>

EPI_NAMESPACE_USING()

wxBEGIN_EVENT_TABLE(epiWXPlot, wxGLCanvas)
    EVT_SIZE(epiWXPlot::OnResize)
    EVT_PAINT(epiWXPlot::OnPaint)
    EVT_ERASE_BACKGROUND(epiWXPlot::OnEraseBackground)
    EVT_IDLE(epiWXPlot::OnIdle)
    EVT_MOUSE_EVENTS(epiWXPlot::OnMouse)
wxEND_EVENT_TABLE()

epiWXPlot::epiWXPlot(wxWindow* parent,
                     const wxGLAttributes& attribList,
                     wxWindowID id,
                     const wxPoint& pos,
                     const wxSize& size,
                     long style,
                     const wxString& name,
                     const wxPalette& palette)
    : wxGLCanvas(parent, attribList, id, pos, size, style, name, palette)
{
    wxGLContextAttrs contextAttr;
    contextAttr.PlatformDefaults().CoreProfile().OGLVersion(4, 0).EndList();

    m_GLContext = new wxGLContext(this, nullptr, &contextAttr);
    if (!m_GLContext->IsOK())
    {
        epiLogFatal("OpenGL Failed to setup OpenGL 4.0!");
    }
    SetCurrent(*m_GLContext);

    if (!gladLoadGL())
    {
        epiLogFatal("OpenGL Failed to `GetProcAddress`!");
    }

    m_UIContext = new uiContext();
    m_UIContext->GetGFXContext().SetCamera(new uiCamera());
    if (gfxCamera* camera = m_UIContext->GetGFXContext().GetCamera())
    {
        camera->SetPosition({ 0.0f, 0.0f, 1.0f });
        camera->SetLookAtPosition({ 0.0f, 0.0f, 0.0f });
        camera->SetUpDirection({ 0.0f, 1.0f, 0.0f });
        camera->SetPlaneNear(0.1f);
        camera->SetPlaneFar(1000.0f);
    }

    glClearColor(0.97f, 0.97f, 0.97f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    m_Plot = &m_UIContext->GetPage().Add<uiPlot>();
    m_UIContext->GetPage().SetUIContext(m_UIContext); // TODO: fix

    dvVMPlot& vm = m_Plot->GetViewModel();

    epiRect2f bbox;
    bbox.Left = 0.0f;
    bbox.Right = 10.0f;
    bbox.Top = 1.5f;
    bbox.Bottom = -1.5f;
    vm.SetBBox(bbox);

    epiRect2f clipbox;
    clipbox.Left = 0.0f;
    clipbox.Right = 2.0f;
    clipbox.Top = 1.5f;
    clipbox.Bottom = -1.5f;
    vm.SetClipBox(clipbox);
}

void epiWXPlot::OnResize(wxSizeEvent& event)
{
    const wxSize& size = event.GetSize();

    if (uiCamera* camera = epiAs<uiCamera>(m_UIContext->GetGFXContext().GetCamera()))
    {
        camera->SetAspectRatio(size.x / static_cast<epiFloat>(size.y));

        epiRect2f rectPhysical;
        rectPhysical.Left = 0.0f;
        rectPhysical.Bottom = 0.0f;
        rectPhysical.Top = size.y;
        rectPhysical.Right = size.x;

        camera->SetFrameDimensionPhysical(rectPhysical);

        epiRect2f rectVirtual;
        rectVirtual.Left = -(1920 / 2);
        rectVirtual.Top = +((1920 / camera->GetAspectRatio()) / 2);
        rectVirtual.Right = +(1920 / 2);
        rectVirtual.Bottom = -((1920 / camera->GetAspectRatio()) / 2);

        camera->SetFrameDimensionVirtual(rectVirtual);

        m_UIContext->OnResize(rectVirtual);
    }

    SetCurrent(*m_GLContext);
    glViewport(0, 0, size.x, size.y);
    Refresh(false);
}

void epiWXPlot::OnEraseBackground(wxEraseEvent& event)
{
    // NOTE: should reduce flickering
}

void epiWXPlot::OnPaint(wxPaintEvent& event)
{
    wxPaintDC paint(this);
    SetCurrent(*m_GLContext);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_UIContext->Draw();

    SwapBuffers();
}

void epiWXPlot::OnIdle(wxIdleEvent& event)
{
    m_UIContext->Update();
}

void epiWXPlot::OnMouse(wxMouseEvent& event)
{
    // TODO: make scrolling FPS independent

    const wxSize size = GetSize();

    epiVec2f ndc(event.GetX(), event.GetY());
    ndc.x /= size.x;
    ndc.y /= size.y;
    ndc *= 2.0f;
    ndc -= 1.0f;
    ndc.y = -ndc.y;

    m_UIContext->OnMouseMove(ndc);

    if (const epiFloat dZoom = event.GetWheelRotation() / 120.0f; dZoom != 0.0f)
    {
        m_UIContext->OnMouseWheel(dZoom);
        Refresh(false);
    }

    if (event.LeftUp() || event.LeftDown() || event.LeftDClick())
    {
        uiMouseAction action;
        if (event.LeftDClick())
        {
            action = uiMouseAction::DClick;
        }
        else if (event.LeftUp())
        {
            action = uiMouseAction::Release;
        }
        else if (event.LeftDown())
        {
            action = uiMouseAction::Click;
        }

        m_UIContext->OnMousePrimary(action);
        Refresh(false);
    }

    if (event.Entering() || event.Leaving())
    {
        m_UIContext->OnMouseFocus(event.Entering());
    }
}

dvVMPlot& epiWXPlot::GetViewModel()
{
    epiAssert(m_Plot != nullptr);
    return m_Plot->GetViewModel();
}
