#pragma once

#include "EpiwxWidgets/epiWXSliderThumb.h"
#include "EpiwxWidgets/epiWXSliderBase.h"

template<typename T>
class epiWXSliderRange : public epiWXSliderBase
{
public:
    using super = epiWXSliderBase;

public:
    epiWXSliderRange(wxWindow* parent,
                     wxWindowID id,
                     epi::PropertyPointer&& pptr,
                     T minValue,
                     T maxValue,
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize,
                     epiS32 style = wxSL_HORIZONTAL,
                     const wxString& name = wxASCII_STR("epiWXSliderRange"));

public:
    std::any GetMinValueAny() const override;
    std::any GetMaxValueAny() const override;

    T GetMinValue() const;
    T GetMaxValue() const;

    void SetValueLower(T value);
    T GetValueLower() const;
    void SetValueUpper(T value);
    T GetValueUpper() const;

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

    epi::PropertyPointer m_PrtyPtr;
    epiWXSliderThumb<T> m_ThumbLower;
    epiWXSliderThumb<T> m_ThumbUpper;
};

namespace
{

const wxColour kRangeBackgroundColor = wxColour(231, 234, 234);
const wxColour kRangeOutlineColor = wxColour(214, 214, 214);
const wxColour kSelectedRangeColor = wxColour(0, 120, 215);
const wxColour kSelectedRangeOutlineColor = wxColour(0, 120, 215);

}

template<typename T>
epiWXSliderRange<T>::epiWXSliderRange(wxWindow* parent,
                                             wxWindowID id,
                                             epi::PropertyPointer&& pptr,
                                             T minValue,
                                             T maxValue,
                                             const wxPoint& pos,
                                             const wxSize& size,
                                             epiS32 style,
                                             const wxString& name)
    : super{parent, id, pos, size, style, name}
    , m_MinValue{minValue}
    , m_MaxValue{maxValue}
    , m_ThumbLower{this, std::clamp(m_PrtyPtr.Get<epiVec2<T>>().x, minValue, maxValue)}
    , m_ThumbUpper{this, std::clamp(m_PrtyPtr.Get<epiVec2<T>>().y, minValue, maxValue)}
{
    const epiVec2<T>& prty = m_PrtyPtr.Get<epiVec2<T>>();
    if (prty.x > prty.y)
    {
        epiLogError("lower value=`{}` should be less or equal to upper value=`{}`!", prty.x, prty.y);
        return;
    }
}

template<typename T>
std::any epiWXSliderRange<T>::GetMinValueAny() const
{
    return std::make_any<T>(GetMinValue());
}

template<typename T>
std::any epiWXSliderRange<T>::GetMaxValueAny() const
{
    return std::make_any<T>(GetMaxValue());
}

template<typename T>
T epiWXSliderRange<T>::GetMinValue() const
{
    return m_MinValue;
}

template<typename T>
T epiWXSliderRange<T>::GetMaxValue() const
{
    return m_MaxValue;
}

template<typename T>
void epiWXSliderRange<T>::SetValueLower(T value)
{
    m_ThumbLower.SetValue(value);
    m_PrtyPtr.Set<epiVec2<T>>(epiVec2<T>{value, GetValueUpper()});
}

template<typename T>
T epiWXSliderRange<T>::GetValueLower() const
{
    return m_ThumbLower.GetValue();
}

template<typename T>
void epiWXSliderRange<T>::SetValueUpper(T value)
{
    m_ThumbUpper.SetValue(value);
    m_PrtyPtr.Set<epiVec2<T>>(epiVec2<T>{GetValueLower(), value});
}

template<typename T>
T epiWXSliderRange<T>::GetValueUpper() const
{
    return m_ThumbUpper.GetValue();
}

template<typename T>
wxSize epiWXSliderRange<T>::GetSizeSliderControl() const
{
    return wxSize{std::max({500, m_ThumbLower.GetSize().x, m_ThumbUpper.GetSize().x}),
                  std::max({26, m_ThumbLower.GetSize().y, m_ThumbUpper.GetSize().y})};
}

template<typename T>
void epiWXSliderRange<T>::GetSizeLabelMinMaxValue(wxSize& minLabelSize, wxSize& maxLabelSize)
{
    wxClientDC dc(this);

    minLabelSize = dc.GetTextExtent(std::to_string(m_MinValue));
    maxLabelSize = dc.GetTextExtent(std::to_string(m_MaxValue));
}

template<typename T>
wxSize epiWXSliderRange<T>::GetSizeBBox()
{
    const wxSize sliderControlSize = GetSizeSliderControl();
    const epiS32 border = GetBorderWidth();

    wxSize minLabelSize;
    wxSize maxLabelSize;
    GetSizeLabelMinMaxValue(minLabelSize, maxLabelSize);

    return wxSize{2 * border + sliderControlSize.x + minLabelSize.x + maxLabelSize.x + 2 * static_cast<epiS32>(GetMinMaxLabelPadding()), 2 * border + std::max({sliderControlSize.y, minLabelSize.y, maxLabelSize.y})};
}

template<typename T>
void epiWXSliderRange<T>::OnMouseDown_Internal(wxMouseEvent& event)
{
#if 0
    if (!IsEnabled())
    {
        return;
    }

    const wxPoint mousePosition = event.GetPosition();
    if (m_Thumb.IsMouseOver(mousePosition))
    {
        m_Thumb.SetDragged(true);
        m_Thumb.SetMouseOver(false);
    }

    m_Thumb.SetPosition(mousePosition);

    CaptureMouse();

    Refresh();
#endif
}

template<typename T>
void epiWXSliderRange<T>::OnMouseUp_Internal(wxMouseEvent& event)
{
#if 0
    if (!IsEnabled())
    {
        return;
    }

    m_Thumb.SetPosition(event.GetPosition());
    m_Thumb.SetDragged(false);

    if (HasCapture())
    {
        ReleaseMouse();
    }

    Refresh();
#endif
}

template<typename T>
void epiWXSliderRange<T>::OnMouseMotion_Internal(wxMouseEvent& event)
{
#if 0
    if (!IsEnabled())
    {
        return;
    }

    epiBool refreshNeeded = false;

    const wxPoint mousePosition = event.GetPosition();
    if (event.Dragging() && event.LeftIsDown())
    {
        m_Thumb.SetPosition(mousePosition);
        refreshNeeded = true;
    }
    else
    {
        const epiBool prevMouseOver = m_Thumb.GetMouseOver();
        m_Thumb.SetMouseOver(m_Thumb.IsMouseOver(mousePosition));
        if (prevMouseOver != m_Thumb.GetMouseOver())
        {
            refreshNeeded = true;
        }
    }

    if (refreshNeeded)
    {
        Refresh();
    }
#endif
}

template<typename T>
void epiWXSliderRange<T>::OnMouseLost_Internal(wxMouseCaptureLostEvent& event)
{
#if 0
    m_Thumb.SetDragged(false);
    m_Thumb.SetMouseOver(false);

    Refresh();
#endif
}

template<typename T>
void epiWXSliderRange<T>::OnMouseEnter_Internal(wxMouseEvent& event)
{
#if 0
    if (!IsEnabled())
    {
        return;
    }

    const wxPoint mousePosition = event.GetPosition();
    if (m_Thumb.IsMouseOver(mousePosition))
    {
        m_Thumb.SetMouseOver(true);
        Refresh();
    }
#endif
}

template<typename T>
void epiWXSliderRange<T>::OnMouseLeave_Internal(wxMouseEvent& event)
{
#if 0
    if (!IsEnabled())
    {
        return;
    }

    m_Thumb.SetMouseOver(false);

    Refresh();
#endif
}

template<typename T>
void epiWXSliderRange<T>::OnPaint_Internal(wxPaintEvent& event)
{
#if 0
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

    m_Thumb.OnPaint(dc);

    event.Skip();
#endif
}
