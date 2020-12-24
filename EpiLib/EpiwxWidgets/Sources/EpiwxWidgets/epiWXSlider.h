#pragma once

#include "EpiwxWidgets/epiWXSliderThumb.h"
#include "EpiwxWidgets/epiWXSliderBase.h"

template<typename T>
class epiWXSlider : public epiWXSliderBase
{
public:
    using super = epiWXSliderBase;

public:
    epiWXSlider(wxWindow* parent,
                wxWindowID id,
                T value,
                T minValue,
                T maxValue,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                epiS32 style = wxSL_HORIZONTAL,
                const wxString& name = wxASCII_STR("epiWXSlider"));

public:
    std::any GetMinValueAny() const override;
    std::any GetMaxValueAny() const override;

    T GetMinValue() const;
    T GetMaxValue() const;

    void SetValuePrimary(T value);
    T GetValuePrimary() const;

    wxSize GetSizeSliderControl() const override;
    void GetSizeLabelMinMaxValue(wxSize& minLabelSize, wxSize& maxLabelSize) override;
    wxSize GetSizeBBox() override;

protected:
    void OnMouseDown_Internal(wxMouseEvent& event) override;
    void OnMouseUp_Internal(wxMouseEvent& event) override;
    void OnMouseMotion_Internal(wxMouseEvent& event) override;
    void OnMouseLost_Internal(wxMouseCaptureLostEvent& event) override;
    void OnMouseEnter_Internal(wxMouseEvent& event) override;
    void OnMouseLeave_Internal(wxMouseEvent& event) override;
    void OnPaint_Internal(wxPaintEvent& event) override;

protected:
    T m_MinValue{};
    T m_MaxValue{};

    epiWXSliderThumb<T> m_ThumbPrimary;
};

namespace
{

const wxColour kRangeBackgroundColor = wxColour(231, 234, 234);
const wxColour kRangeOutlineColor = wxColour(214, 214, 214);
const wxColour kSelectedRangeColor = wxColour(0, 120, 215);
const wxColour kSelectedRangeOutlineColor = wxColour(0, 120, 215);

}

template<typename T>
epiWXSlider<T>::epiWXSlider(wxWindow* parent,
                            wxWindowID id,
                            T value,
                            T minValue,
                            T maxValue,
                            const wxPoint& pos,
                            const wxSize& size,
                            epiS32 style,
                            const wxString& name)
    : super{parent, id, pos, size, style, name}
    , m_MinValue{minValue}
    , m_MaxValue{maxValue}
    , m_ThumbPrimary{this, std::clamp(value, minValue, maxValue)}
{
    if (minValue > maxValue)
    {
        epiLogError("min value=`{}` should be less or equal to max value=`{}`!", minValue, maxValue);
        return;
    }

    const wxSize bboxSize = GetSizeBBox();
    SetMinSize(wxSize{std::max(500, bboxSize.x), std::max(30, bboxSize.y)});
}

template<typename T>
std::any epiWXSlider<T>::GetMinValueAny() const
{
    return std::make_any<T>(GetMinValue());
}

template<typename T>
std::any epiWXSlider<T>::GetMaxValueAny() const
{
    return std::make_any<T>(GetMaxValue());
}

template<typename T>
T epiWXSlider<T>::GetMinValue() const
{
    return m_MinValue;
}

template<typename T>
T epiWXSlider<T>::GetMaxValue() const
{
    return m_MaxValue;
}

template<typename T>
void epiWXSlider<T>::SetValuePrimary(T value)
{
    m_ThumbPrimary.SetValue(value);
}

template<typename T>
T epiWXSlider<T>::GetValuePrimary() const
{
    return m_ThumbPrimary.GetValue();
}

template<typename T>
void epiWXSlider<T>::OnMouseDown_Internal(wxMouseEvent& event)
{
    if (!IsEnabled())
    {
        return;
    }

    const wxPoint mousePosition = event.GetPosition();
    if (m_ThumbPrimary.IsMouseOver(mousePosition))
    {
        m_ThumbPrimary.SetDragged(true);
        m_ThumbPrimary.SetMouseOver(false);
    }

    m_ThumbPrimary.SetPosition(mousePosition);

    CaptureMouse();

    Refresh();
}

template<typename T>
void epiWXSlider<T>::OnMouseUp_Internal(wxMouseEvent& event)
{
    if (!IsEnabled())
    {
        return;
    }

    m_ThumbPrimary.SetPosition(event.GetPosition());
    m_ThumbPrimary.SetDragged(false);

    if (HasCapture())
    {
        ReleaseMouse();
    }

    Refresh();
}

template<typename T>
void epiWXSlider<T>::OnMouseMotion_Internal(wxMouseEvent& event)
{
    if (!IsEnabled())
    {
        return;
    }

    epiBool refreshNeeded = false;

    const wxPoint mousePosition = event.GetPosition();
    if (event.Dragging() && event.LeftIsDown())
    {
        m_ThumbPrimary.SetPosition(mousePosition);
        refreshNeeded = true;
    }
    else
    {
        const epiBool prevMouseOver = m_ThumbPrimary.GetMouseOver();
        m_ThumbPrimary.SetMouseOver(m_ThumbPrimary.IsMouseOver(mousePosition));
        if (prevMouseOver != m_ThumbPrimary.GetMouseOver())
        {
            refreshNeeded = true;
        }
    }

    if (refreshNeeded)
    {
        Refresh();
    }
}

template<typename T>
void epiWXSlider<T>::OnMouseLost_Internal(wxMouseCaptureLostEvent& event)
{
    m_ThumbPrimary.SetDragged(false);
    m_ThumbPrimary.SetMouseOver(false);

    Refresh();
}

template<typename T>
void epiWXSlider<T>::OnMouseEnter_Internal(wxMouseEvent& event)
{
    if (!IsEnabled())
    {
        return;
    }

    const wxPoint mousePosition = event.GetPosition();
    if (m_ThumbPrimary.IsMouseOver(mousePosition))
    {
        m_ThumbPrimary.SetMouseOver(true);
        Refresh();
    }
}

template<typename T>
void epiWXSlider<T>::OnMouseLeave_Internal(wxMouseEvent& event)
{
    if (!IsEnabled())
    {
        return;
    }

    m_ThumbPrimary.SetMouseOver(false);

    Refresh();
}

template<typename T>
void epiWXSlider<T>::OnPaint_Internal(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(this);

    dc.SetBackground(wxBrush(kRangeBackgroundColor, wxBRUSHSTYLE_SOLID));
    dc.Clear();

    constexpr epiU32 trackHeight = 12;
    dc.SetPen(wxPen(kRangeOutlineColor, 1, wxPENSTYLE_SOLID));
    dc.SetBrush(wxBrush(kRangeBackgroundColor, wxBRUSHSTYLE_SOLID));

    const wxSize bboxSize = GetSizeBBox();
    const wxSize sliderControlSize = GetSizeSliderControl();

    const std::string minText = std::to_string(m_MinValue);
    const std::string maxText = std::to_string(m_MaxValue);

    wxCoord minTextX;
    wxCoord minTextY;
    wxCoord minTextDescent;
    dc.GetTextExtent(minText, &minTextX, &minTextY, &minTextDescent);

    wxCoord maxTextX;
    wxCoord maxTextY;
    wxCoord maxTextDescent;
    dc.GetTextExtent(maxText, &maxTextX, &maxTextY, &maxTextDescent);

    dc.DrawRectangle(minTextX + GetBorderWidth() + GetMinMaxLabelPadding(),
                     bboxSize.y / 2 - trackHeight / 2,
                     GetSizeSliderControl().x,
                     trackHeight);

    dc.DrawText(minText, GetBorderWidth(), minTextDescent);
    dc.DrawText(maxText, bboxSize.x - maxTextX - GetBorderWidth(), maxTextDescent);

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

#if 0
    const epiS32 positionLower = GetThumbLower().GetPosition().x;
    const epiS32 positionUpper = GetThumbUpper().GetPosition().x;

    dc.DrawRectangle(positionLower, size.y / 2 - trackHeight / 4, positionUpper - positionLower, trackHeight / 2);
#endif

    m_ThumbPrimary.OnPaint(dc);

    event.Skip();
}

template<typename T>
wxSize epiWXSlider<T>::GetSizeSliderControl() const
{
    return wxSize{std::max(500, m_ThumbPrimary.GetSize().x), std::max(26, m_ThumbPrimary.GetSize().y)};
}

template<typename T>
void epiWXSlider<T>::GetSizeLabelMinMaxValue(wxSize& minLabelSize, wxSize& maxLabelSize)
{
    wxClientDC dc(this);

    minLabelSize = dc.GetTextExtent(std::to_string(m_MinValue));
    maxLabelSize = dc.GetTextExtent(std::to_string(m_MaxValue));
}

template<typename T>
wxSize epiWXSlider<T>::GetSizeBBox()
{
    const wxSize sliderControlSize = GetSizeSliderControl();
    const epiS32 border = GetBorderWidth();

    wxSize minLabelSize;
    wxSize maxLabelSize;
    GetSizeLabelMinMaxValue(minLabelSize, maxLabelSize);

    return wxSize{2 * border + sliderControlSize.x + minLabelSize.x + maxLabelSize.x + 2 * static_cast<epiS32>(GetMinMaxLabelPadding()), 2 * border + std::max({sliderControlSize.y, minLabelSize.y, maxLabelSize.y})};
}
