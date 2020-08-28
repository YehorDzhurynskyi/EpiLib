#include "EpiwxWidgets/epiWXPlot.h"

#include "EpiDataVisualization/ViewModel/dvViewModelSeriesBase.h"
#include "EpiDataVisualization/Plot/Series/dvSeriesY.h"
#include "EpiDataVisualization/View/dvViewPlot.h"
#include "EpiDataVisualization/View/dvViewPlotDrawArea.h"
#include "EpiDataVisualization/View/dvViewPlotTimeline.h"

#include "EpiGraphics/gfxDrawerPrimitive.h"
#include "EpiGraphics/gfxDrawerText.h"

#include "EpiUI/Layout/uiLayoutBox.h"

#include "EpiCore/ObjectModel/PropertyPointer.h"

#include <glad/glad.h>
#include <wx/wx.h>

using namespace epi;

wxBEGIN_EVENT_TABLE(epiWXPlot, wxGLCanvas)
    EVT_SIZE(epiWXPlot::OnResize)
    EVT_PAINT(epiWXPlot::OnPaint)
    EVT_IDLE(epiWXPlot::OnIdle)
    EVT_MOUSE_EVENTS(epiWXPlot::OnMouse)
wxEND_EVENT_TABLE()

epiWXPlot::epiWXPlot(wxWindow* parent, const wxGLAttributes& attribList)
    : wxGLCanvas(parent,
                 attribList,
                 -1,
                 wxDefaultPosition,
                 wxDefaultSize,
                 wxFULL_REPAINT_ON_RESIZE)
{
    wxGLContextAttrs contextAttr;
    contextAttr.PlatformDefaults().CoreProfile().OGLVersion(4, 0).EndList();

    m_GLContext = new wxGLContext(this, nullptr, &contextAttr);
    if (!m_GLContext->IsOK())
    {
        wxMessageBox(wxT("Failed to set OpenGL 4.0"), wxT("Error"));
    }
    SetCurrent(*m_GLContext);

    if (!gladLoadGL())
    {
        wxMessageBox(wxT("Failed on OpenGL GetProcAddress"), wxT("Error"));
    }

    m_UIContext = new uiContext();
    gfxCamera& camera = m_UIContext->GetCamera();
    camera.SetPosition({ 0.0f, 0.0f, 1.0f });
    camera.SetLookAtPosition({ 0.0f, 0.0f, 0.0f });
    camera.SetUpDirection({ 0.0f, 1.0f, 0.0f });
    camera.SetPlaneNear(0.1f);
    camera.SetPlaneFar(1000.0f);

    m_TextManager.GetDefaultFace();
    glClearColor(0.97f, 0.97f, 0.97f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    m_ViewPlot = &m_UIContext->GetPage().Add<dvViewPlot>();
    m_UIContext->GetPage().SetUIContext(m_UIContext); // TODO: fix
    uiLayoutBox* layout = new uiLayoutBox();
    m_ViewPlot->SetLayout(layout); // TODO: fix

    dvViewModelPlot& vm = m_ViewPlot->GetViewModel();

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

    {
        dvViewPlotDrawArea& drawArea = m_ViewPlot->Add<dvViewPlotDrawArea>();
        drawArea.SetViewModel(&vm);
        uiSizePolicyInfo& policy = drawArea.GetSizePolicyInfo();
        policy.SetSizePolicyVertical(uiSizePolicy_Expanding);
    }

    {
        dvViewPlotTimeline& timeline = m_ViewPlot->Add<dvViewPlotTimeline>();
        timeline.SetViewModel(&vm);
        uiSizePolicyInfo& policy = timeline.GetSizePolicyInfo();
        policy.SetSizePolicyVertical(uiSizePolicy_Fixed);
        timeline.SetSizeHint(epiVec2f{ 0.0f, 100.0f });
    }

    m_UIContext->GetDrawerText().CreateAtlas(m_TextManager.GetDefaultFace(), L"0123456789-+eE,.", 18);
}

void epiWXPlot::Update()
{
    for (auto& bind : m_PropertyBinds)
    {
        const epiFloat value = bind.PrtyPtr->Get<epiFloat>();
        bind.Series->Add(value);
    }
}

void epiWXPlot::OnResize(wxSizeEvent& event)
{
    const wxSize& size = event.GetSize();

    uiCamera& camera = m_UIContext->GetCamera();
    camera.SetAspectRatio(size.x / static_cast<epiFloat>(size.y));

    epiRect2f rectPhysical;
    rectPhysical.Left = 0.0f;
    rectPhysical.Bottom = 0.0f;
    rectPhysical.Top = size.y;
    rectPhysical.Right = size.x;

    m_UIContext->GetCamera().SetFrameDimensionPhysical(rectPhysical);

    epiRect2f rectVirtual;
    rectVirtual.Left = -(1920 / 2);
    rectVirtual.Top = +((1920 / camera.GetAspectRatio()) / 2);
    rectVirtual.Right = +(1920 / 2);
    rectVirtual.Bottom = -((1920 / camera.GetAspectRatio()) / 2);

    camera.SetFrameDimensionVirtual(rectVirtual);

    m_UIContext->OnResize(rectVirtual);

    glViewport(0, 0, size.x, size.y);
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
    Refresh(false);

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
    }

    if (event.Entering() || event.Leaving())
    {
        m_UIContext->OnMouseFocus(event.Entering());
    }
}

void epiWXPlot::AddPropertyBind(const epi::PropertyPointer* ptr)
{
    dvSeriesY& series = m_Plot.Add<dvSeriesY>();
    series.SetStepX(0.0001f); // TODO: set in other place

    dvViewModelPlot& vm = m_ViewPlot->GetViewModel();
    dvViewModelSeriesBase& seriesVM = vm.Add<dvViewModelSeriesBase>();
    seriesVM.SetModel(&series);

    Color colors[] {
        Color::kLightBlue,
        Color::kLightRed
    };

    seriesVM.SetColor(colors[m_Plot.Size() % epiArrLen(colors)]);

    PropertyBind& bind = m_PropertyBinds.emplace_back();
    bind.Series = &series;
    bind.PrtyPtr = ptr;
}
