#include "EpiwxWidgets/epiWXSliderRange.h"

#include <wx/dc.h>
#include <wx/dcbuffer.h>

namespace
{

epiS32 Fraction2Value(epiFloat fraction, epiS32 minValue, epiS32 maxValue)
{
    return (maxValue - minValue) * fraction + minValue;
}


epiFloat Value2Fraction(epiS32 value, epiS32 minValue, epiS32 maxValue)
{
    return epiFloat(value - minValue) / (maxValue - minValue);
}

}

const wxColour epiWXSliderRangeThumb::kIdleColor = wxColour(0, 120, 215);
const wxColour epiWXSliderRangeThumb::kIdleShadowColor = wxColour(120, 180, 228);
const wxColour epiWXSliderRangeThumb::kDraggedColor = wxColour(204, 204, 204);
const wxColour epiWXSliderRangeThumb::kDraggedShadowColor = wxColour(222, 222, 222);
const wxColour epiWXSliderRangeThumb::kMouseOverColor = wxColour(23, 23, 23);
const wxColour epiWXSliderRangeThumb::kMouseOverShadowColor = wxColour(132, 132, 132);

epiWXSliderRangeThumb::epiWXSliderRangeThumb(epiWXSliderRange* parent, epiS32 value)
    : m_Parent(parent)
    , m_Value(value)
{
    epiAssert(m_Parent != nullptr);

    m_ThumbPointList.Append(new wxPoint{0, 0});
    m_ThumbPointList.Append(new wxPoint{0, 13});
    m_ThumbPointList.Append(new wxPoint{5, 18});
    m_ThumbPointList.Append(new wxPoint{10, 13});
    m_ThumbPointList.Append(new wxPoint{10, 0});

    m_ThumbShadowPointList.Append(new wxPoint{0, 14});
    m_ThumbShadowPointList.Append(new wxPoint{4, 18});
    m_ThumbShadowPointList.Append(new wxPoint{6, 18});
    m_ThumbShadowPointList.Append(new wxPoint{10, 14});

    epiS32 minX = std::numeric_limits<epiS32>::max();
    epiS32 maxX = std::numeric_limits<epiS32>::min();
    epiS32 minY = std::numeric_limits<epiS32>::max();
    epiS32 maxY = std::numeric_limits<epiS32>::min();

    for (const auto& point : m_ThumbPointList)
    {
        minX = std::min(minX, point->x);
        minY = std::min(minY, point->y);
        maxX = std::max(maxX, point->x);
        maxY = std::max(maxY, point->y);
    }

    m_Size.x = maxX - minX;
    m_Size.y = maxY - minY;
}

wxPoint epiWXSliderRangeThumb::GetPosition() const
{
    const wxSize parentSize = m_Parent->GetSize();

    const epiFloat fraction = Value2Fraction(m_Value, m_Parent->GetMin(), m_Parent->GetMax());
    return wxPoint{Fraction2Value(fraction, GetMin(), GetMax()), parentSize.y / 2 + 1};
}

void epiWXSliderRangeThumb::SetPosition(const wxPoint& position)
{
    epiS32 positionX = position.x;

    epiWXSliderRangeThumb& other = GetOtherThumb();
    wxPoint otherPosition = other.GetPosition();

    if (other.IsThumbLower())
    {
        positionX = std::max(otherPosition.x + other.GetSize().x / 2 + GetSize().x / 2, positionX);
    }
    else
    {
        positionX = std::min(otherPosition.x - other.GetSize().x / 2 - GetSize().x / 2, positionX);
    }

    positionX = std::clamp(positionX, GetMin(), GetMax());
    const epiFloat fraction = Value2Fraction(positionX, GetMin(), GetMax());
    SetValue(Fraction2Value(fraction, m_Parent->GetMin(), m_Parent->GetMax()));
}

void epiWXSliderRangeThumb::SetValue(epiS32 value)
{
    m_Value = value;

    wxCommandEvent event(wxEVT_SLIDER, m_Parent->GetId());
    event.SetEventObject(m_Parent);

    wxPostEvent(m_Parent->GetEventHandler(), event);
}

epiS32 epiWXSliderRangeThumb::GetValue() const
{
    return m_Value;
}

epiBool epiWXSliderRangeThumb::IsMouseOver(const wxPoint& mousePosition) const
{
    const wxPoint position = GetPosition();

    return
        mousePosition.x >= position.x - GetSize().x / 2 &&
        mousePosition.x <= position.x + GetSize().x / 2 &&
        mousePosition.y >= position.y - GetSize().y / 2 &&
        mousePosition.y <= position.y + GetSize().y / 2;
}

epiBool epiWXSliderRangeThumb::GetDragged() const
{
    return m_Dragged;
}

void epiWXSliderRangeThumb::SetDragged(epiBool value)
{
    m_Dragged = value;
}

epiBool epiWXSliderRangeThumb::GetMouseOver() const
{
    return m_MouseOver;
}

void epiWXSliderRangeThumb::SetMouseOver(epiBool value)
{
    m_MouseOver = value;
}

void epiWXSliderRangeThumb::OnPaint(wxDC& dc)
{
    wxColour colorThumb;
    wxColour colorThumbShadow;

    if (m_Dragged || !m_Parent->IsEnabled())
    {
        colorThumb = kDraggedColor;
        colorThumbShadow = kDraggedShadowColor;
    }
    else if (m_MouseOver)
    {
        colorThumb = kMouseOverColor;
        colorThumbShadow = kMouseOverShadowColor;
    }
    else
    {
        colorThumb = kIdleColor;
        colorThumbShadow = kIdleShadowColor;
    }

    const wxPoint position = GetPosition();

    dc.SetBrush(wxBrush(colorThumbShadow, wxBRUSHSTYLE_SOLID));
    dc.SetPen(wxPen(colorThumbShadow, 1, wxPENSTYLE_SOLID));

    wxPoint kThumbShadowPoly[] { wxPoint{0, 14}, wxPoint{4, 18}, wxPoint{6, 18}, wxPoint{10, 14} };
    wxPointList kThumbShadowPolyList;
    for (epiU32 i = 0; i < epiArrLen(kThumbShadowPoly); ++i)
    {
        kThumbShadowPolyList.Append(&kThumbShadowPoly[i]);
    }
    dc.DrawPolygon(&kThumbShadowPolyList, position.x - GetSize().x / 2, position.y - GetSize().y / 2);

    dc.SetBrush(wxBrush(colorThumb, wxBRUSHSTYLE_SOLID));
    dc.SetPen(wxPen(colorThumb, 1, wxPENSTYLE_SOLID));

    wxPoint kThumbPoly[]{ wxPoint{0, 0}, wxPoint{0, 13}, wxPoint{5, 18}, wxPoint{10, 13}, wxPoint{10, 0} };
    wxPointList kThumbPolyList;
    for (epiU32 i = 0; i < epiArrLen(kThumbPoly); ++i)
    {
        kThumbPolyList.Append(&kThumbPoly[i]);
    }
    dc.DrawPolygon(&kThumbPolyList, position.x - GetSize().x / 2, position.y - GetSize().y / 2);
}

wxSize epiWXSliderRangeThumb::GetSize() const
{
    return m_Size;
}

epiS32 epiWXSliderRangeThumb::GetMin() const
{
    return m_Parent->GetBorderWidth() + GetSize().x / 2;
}

epiS32 epiWXSliderRangeThumb::GetMax() const
{
    return m_Parent->GetSize().x - m_Parent->GetBorderWidth() - GetSize().x / 2;
}

epiWXSliderRangeThumb& epiWXSliderRangeThumb::GetOtherThumb()
{
    if (IsThumbLower())
    {
        return m_Parent->GetThumbUpper();
    }
    else
    {
        epiAssert(IsThumbUpper());
        return m_Parent->GetThumbLower();
    }
}

epiBool epiWXSliderRangeThumb::IsThumbLower() const
{
    return &m_Parent->GetThumbLower() == this;
}

epiBool epiWXSliderRangeThumb::IsThumbUpper() const
{
    return &m_Parent->GetThumbUpper() == this;
}

EPI_NAMESPACE_USING()

const wxColour epiWXSliderRange::kRangeBackgroundColor = wxColour(231, 234, 234);
const wxColour epiWXSliderRange::kRangeOutlineColor = wxColour(214, 214, 214);
const wxColour epiWXSliderRange::kSelectedRangeColor = wxColour(0, 120, 215);
const wxColour epiWXSliderRange::kSelectedRangeOutlineColor = wxColour(0, 120, 215);

epiWXSliderRange::epiWXSliderRange(wxWindow* parent,
                                   wxWindowID id,
                                   epiS32 lowerValue,
                                   epiS32 upperValue,
                                   epiS32 minValue,
                                   epiS32 maxValue,
                                   const wxPoint& pos,
                                   const wxSize& size,
                                   epiS32 style,
                                   const wxString& name)
    : super{parent, id, pos, size, style, name}
    , m_ValueMin{minValue}
    , m_ValueMax{maxValue}
    , m_ThumbLower{this, std::max(minValue, lowerValue)}
    , m_ThumbUpper{this, std::min(maxValue, upperValue)}
{
    if (style != wxSL_HORIZONTAL)
    {
        epiLogError("Non-horizontal slider is not implemented!");
        return;
    }

    if (minValue > maxValue)
    {
        epiLogError("min value=`{}` should be less or equal to max value=`{}`!", minValue, maxValue);
        return;
    }

    if (lowerValue > upperValue)
    {
        epiLogError("lower value=`{}` should be less or equal to upper value=`{}`!", lowerValue, upperValue);
        return;
    }

    SetMinSize(wxSize{std::max(50, size.x), std::max(26, size.y)});
    SetBorderWidth(8);

    Bind(wxEVT_LEFT_DOWN, &epiWXSliderRange::OnMouseDown, this);
    Bind(wxEVT_LEFT_UP, &epiWXSliderRange::OnMouseUp, this);
    Bind(wxEVT_MOTION, &epiWXSliderRange::OnMouseMotion, this);
    Bind(wxEVT_MOUSE_CAPTURE_LOST, &epiWXSliderRange::OnMouseLost, this);
    Bind(wxEVT_ENTER_WINDOW, &epiWXSliderRange::OnMouseEnter, this);
    Bind(wxEVT_LEAVE_WINDOW, &epiWXSliderRange::OnMouseLeave, this);
    Bind(wxEVT_PAINT, &epiWXSliderRange::OnPaint, this);
    Bind(wxEVT_ERASE_BACKGROUND, &epiWXSliderRange::OnEraseBackground, this);
    Bind(wxEVT_SIZE, &epiWXSliderRange::OnResize, this);
}

void epiWXSliderRange::DoEnable(epiBool enable)
{
    super::Enable(enable);
    Refresh();
}

void epiWXSliderRange::DoDisable()
{
    super::Disable();
    Refresh();
}

void epiWXSliderRange::SetValueFromMousePosition(const wxPoint& mousePosition)
{
    if (epiWXSliderRangeThumb& thumb = GetThumbLower(); thumb.GetDragged())
    {
        thumb.SetPosition(mousePosition);
    }

    // TODO: check whether they are exclusive
    if (epiWXSliderRangeThumb& thumb = GetThumbUpper(); thumb.GetDragged())
    {
        thumb.SetPosition(mousePosition);
    }
}

void epiWXSliderRange::OnMouseDown(wxMouseEvent& event)
{
    if (!IsEnabled())
    {
        return;
    }

    const wxPoint mousePosition = event.GetPosition();
    if (epiWXSliderRangeThumb& thumbUpper = GetThumbUpper(); thumbUpper.IsMouseOver(mousePosition))
    {
        thumbUpper.SetDragged(true);
        thumbUpper.SetMouseOver(false);
    }
    else if (epiWXSliderRangeThumb& thumbLower = GetThumbLower(); thumbLower.IsMouseOver(mousePosition))
    {
        thumbLower.SetDragged(true);
        thumbLower.SetMouseOver(false);
    }

    SetValueFromMousePosition(mousePosition);

    CaptureMouse();

    Refresh();
}

void epiWXSliderRange::OnMouseUp(wxMouseEvent& event)
{
    if (!IsEnabled())
    {
        return;
    }

    SetValueFromMousePosition(event.GetPosition());

    GetThumbLower().SetDragged(false);
    GetThumbUpper().SetDragged(false);

    if (HasCapture())
    {
        ReleaseMouse();
    }

    Refresh();
}

void epiWXSliderRange::OnMouseMotion(wxMouseEvent& event)
{
    if (!IsEnabled())
    {
        return;
    }

    epiBool refreshNeeded = false;

    const wxPoint mousePosition = event.GetPosition();
    if (event.Dragging() && event.LeftIsDown())
    {
        SetValueFromMousePosition(mousePosition);
        refreshNeeded = true;
    }
    else
    {
        {
            epiWXSliderRangeThumb& thumb = GetThumbLower();
            const epiBool prevMouseOver = thumb.GetMouseOver();
            thumb.SetMouseOver(thumb.IsMouseOver(mousePosition));
            if (prevMouseOver != thumb.GetMouseOver())
            {
                refreshNeeded = true;
            }
        }

        {
            epiWXSliderRangeThumb& thumb = GetThumbUpper();
            const epiBool prevMouseOver = thumb.GetMouseOver();
            thumb.SetMouseOver(thumb.IsMouseOver(mousePosition));
            if (prevMouseOver != thumb.GetMouseOver())
            {
                refreshNeeded = true;
            }
        }
    }

    if (refreshNeeded)
    {
        Refresh();
    }
}

void epiWXSliderRange::OnMouseLost(wxMouseCaptureLostEvent& event)
{
    GetThumbLower().SetDragged(false);
    GetThumbLower().SetMouseOver(false);
    GetThumbUpper().SetDragged(false);
    GetThumbUpper().SetMouseOver(false);

    Refresh();
}

void epiWXSliderRange::OnMouseEnter(wxMouseEvent& event)
{
    if (!IsEnabled())
    {
        return;
    }

    const wxPoint mousePosition = event.GetPosition();
    if (epiWXSliderRangeThumb& thumbUpper = GetThumbUpper(); thumbUpper.IsMouseOver(mousePosition))
    {
        thumbUpper.SetMouseOver(true);
        Refresh();
    }
    else if (epiWXSliderRangeThumb& thumbLower = GetThumbLower(); thumbLower.IsMouseOver(mousePosition))
    {
        thumbLower.SetMouseOver(true);
        Refresh();
    }
}

void epiWXSliderRange::OnMouseLeave(wxMouseEvent& event)
{
    if (!IsEnabled())
    {
        return;
    }

    GetThumbLower().SetMouseOver(false);
    GetThumbUpper().SetMouseOver(false);

    Refresh();
}

void epiWXSliderRange::OnPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(this);
    const wxSize size = GetSize();

    dc.SetBackground(wxBrush(kRangeBackgroundColor, wxBRUSHSTYLE_SOLID));
    dc.Clear();

    constexpr epiU32 trackHeight = 12;
    dc.SetPen(wxPen(kRangeOutlineColor, 1, wxPENSTYLE_SOLID));
    dc.SetBrush(wxBrush(kRangeBackgroundColor, wxBRUSHSTYLE_SOLID));
    dc.DrawRectangle(GetBorderWidth(), size.y / 2 - trackHeight / 2, size.x - 2 * GetBorderWidth(), trackHeight);

    if (IsEnabled())
    {
        dc.SetPen(wxPen(kSelectedRangeOutlineColor, 1, wxPENSTYLE_SOLID));
        dc.SetBrush(wxBrush(kSelectedRangeColor, wxBRUSHSTYLE_SOLID));
    }
    else
    {
        dc.SetPen(wxPen(kRangeOutlineColor, 1, wxPENSTYLE_SOLID));
        dc.SetBrush(wxBrush(kRangeOutlineColor, wxBRUSHSTYLE_SOLID));
    }

    const epiS32 positionLower = GetThumbLower().GetPosition().x;
    const epiS32 positionUpper = GetThumbUpper().GetPosition().x;

    dc.DrawRectangle(positionLower, size.y / 2 - trackHeight / 4, positionUpper - positionLower, trackHeight / 2);

    GetThumbLower().OnPaint(dc);
    GetThumbUpper().OnPaint(dc);

    event.Skip();
}

void epiWXSliderRange::OnEraseBackground(wxEraseEvent& event)
{
    // NOTE: should reduce flickering
}

void epiWXSliderRange::OnResize(wxSizeEvent& event)
{
    Refresh();
}

epiU32 epiWXSliderRange::GetBorderWidth() const
{
    return m_BorderWidth;
}

void epiWXSliderRange::SetBorderWidth(epiU32 width)
{
    m_BorderWidth = width;
}

epiWXSliderRangeThumb& epiWXSliderRange::GetThumbLower()
{
    return m_ThumbLower;
}

epiWXSliderRangeThumb& epiWXSliderRange::GetThumbUpper()
{
    return m_ThumbUpper;
}

const epiWXSliderRangeThumb& epiWXSliderRange::GetThumbLower() const
{
    return m_ThumbLower;
}

const epiWXSliderRangeThumb& epiWXSliderRange::GetThumbUpper() const
{
    return m_ThumbUpper;
}

epiS32 epiWXSliderRange::GetValueLower() const
{
    return GetThumbLower().GetValue();
}

void epiWXSliderRange::SetValueLower(epiS32 value)
{
    GetThumbLower().SetValue(value);
}

epiS32 epiWXSliderRange::GetValueUpper() const
{
    return GetThumbUpper().GetValue();
}

void epiWXSliderRange::SetValueUpper(epiS32 value)
{
    GetThumbUpper().SetValue(value);
}

epiS32 epiWXSliderRange::GetMin() const
{
    return m_ValueMin;
}

epiS32 epiWXSliderRange::GetMax() const
{
    return m_ValueMax;
}
