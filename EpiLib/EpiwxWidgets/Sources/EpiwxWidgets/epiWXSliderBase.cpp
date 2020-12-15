#include "EpiwxWidgets/epiWXSliderBase.h"

namespace
{

const wxColour kRangeBackgroundColor = wxColour(231, 234, 234);
const wxColour kRangeOutlineColor = wxColour(214, 214, 214);
const wxColour kSelectedRangeColor = wxColour(0, 120, 215);
const wxColour kSelectedRangeOutlineColor = wxColour(0, 120, 215);

}

epiWXSliderBase::epiWXSliderBase(wxWindow* parent,
                                 wxWindowID id,
                                 const wxPoint& pos,
                                 const wxSize& size,
                                 epiS32 style,
                                 const wxString& name)
    : super{parent, id, pos, size, style, name}
{
    if (style != wxSL_HORIZONTAL)
    {
        epiLogError("Non-horizontal slider is not implemented!");
        return;
    }

    SetMinSize(wxSize{std::max(500, size.x), std::max(26, size.y)});
    SetBorderWidth(8);

    Bind(wxEVT_LEFT_DOWN, &epiWXSliderBase::OnMouseDown, this);
    Bind(wxEVT_LEFT_UP, &epiWXSliderBase::OnMouseUp, this);
    Bind(wxEVT_MOTION, &epiWXSliderBase::OnMouseMotion, this);
    Bind(wxEVT_MOUSE_CAPTURE_LOST, &epiWXSliderBase::OnMouseLost, this);
    Bind(wxEVT_ENTER_WINDOW, &epiWXSliderBase::OnMouseEnter, this);
    Bind(wxEVT_LEAVE_WINDOW, &epiWXSliderBase::OnMouseLeave, this);
    Bind(wxEVT_PAINT, &epiWXSliderBase::OnPaint, this);
    Bind(wxEVT_ERASE_BACKGROUND, &epiWXSliderBase::OnEraseBackground, this);
    Bind(wxEVT_SIZE, &epiWXSliderBase::OnResize, this);
}

epiU32 epiWXSliderBase::GetBorderWidth() const
{
    return m_BorderWidth;
}

void epiWXSliderBase::SetBorderWidth(epiU32 width)
{
    m_BorderWidth = width;
}

void epiWXSliderBase::DoEnable(epiBool enable)
{
    super::Enable(enable);
    Refresh();
}

void epiWXSliderBase::DoDisable()
{
    super::Disable();
    Refresh();
}

void epiWXSliderBase::OnMouseDown(wxMouseEvent& event)
{
    OnMouseDown_Internal(event);
}

void epiWXSliderBase::OnMouseUp(wxMouseEvent& event)
{
    OnMouseUp_Internal(event);
}

void epiWXSliderBase::OnMouseMotion(wxMouseEvent& event)
{
    OnMouseMotion_Internal(event);
}

void epiWXSliderBase::OnMouseLost(wxMouseCaptureLostEvent& event)
{
    OnMouseLost_Internal(event);
}

void epiWXSliderBase::OnMouseEnter(wxMouseEvent& event)
{
    OnMouseEnter_Internal(event);
}

void epiWXSliderBase::OnMouseLeave(wxMouseEvent& event)
{
    OnMouseLeave_Internal(event);
}

void epiWXSliderBase::OnPaint(wxPaintEvent& event)
{
    OnPaint_Internal(event);
}

void epiWXSliderBase::OnEraseBackground(wxEraseEvent& event)
{
    // NOTE: should reduce flickering
}

void epiWXSliderBase::OnResize(wxSizeEvent& event)
{
    Refresh();
}
