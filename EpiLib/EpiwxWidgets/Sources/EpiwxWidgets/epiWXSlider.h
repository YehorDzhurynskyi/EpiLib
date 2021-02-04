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
                const epi::epiPropertyPointer& pptr,
                T minValue, // TODO: retrive these values from MetaProperty
                T maxValue,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                epiS32 style = wxSL_HORIZONTAL,
                const wxString& name = wxASCII_STR("epiWXSlider"));

public:
    void RefreshValue() override;

    std::any GetMinValueAny() const override;
    std::any GetMaxValueAny() const override;

    T GetMinValue() const;
    T GetMaxValue() const;

    T GetValue() const;

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

    epiString GetMinValueText() const;
    epiString GetMaxValueText() const;

protected:
    T m_MinValue{};
    T m_MaxValue{};

    epi::epiPropertyPointer m_PrtyPtr;
    epiWXSliderThumb<T> m_Thumb;
};

template<typename T>
epiWXSlider<T>::epiWXSlider(wxWindow* parent,
                            wxWindowID id,
                            const epi::epiPropertyPointer& pptr,
                            T minValue,
                            T maxValue,
                            const wxPoint& pos,
                            const wxSize& size,
                            epiS32 style,
                            const wxString& name)
    : super{parent, id, pos, size, style, name}
    , m_MinValue{minValue}
    , m_MaxValue{maxValue}
    , m_PrtyPtr{pptr}
    , m_Thumb{this, std::clamp(m_PrtyPtr.Get<T>(), minValue, maxValue)}
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
void epiWXSlider<T>::RefreshValue()
{
    m_Thumb.SetValue(std::clamp(m_PrtyPtr.Get<T>(), GetMinValue(), GetMaxValue()));
    Refresh();
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
T epiWXSlider<T>::GetValue() const
{
    return m_Thumb.GetValue();
}

template<typename T>
void epiWXSlider<T>::OnMouseDown_Internal(wxMouseEvent& event)
{
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
    m_PrtyPtr.Set<T>(m_Thumb.GetValue());

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

    m_Thumb.SetPosition(event.GetPosition());
    m_PrtyPtr.Set<T>(m_Thumb.GetValue());
    m_Thumb.SetDragged(false);

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
        m_Thumb.SetPosition(mousePosition);
        m_PrtyPtr.Set<T>(m_Thumb.GetValue());
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
}

template<typename T>
void epiWXSlider<T>::OnMouseLost_Internal(wxMouseCaptureLostEvent& event)
{
    m_Thumb.SetDragged(false);
    m_Thumb.SetMouseOver(false);

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
    if (m_Thumb.IsMouseOver(mousePosition))
    {
        m_Thumb.SetMouseOver(true);
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

    m_Thumb.SetMouseOver(false);

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

    const std::string minText = GetMinValueText();
    const std::string maxText = GetMaxValueText();

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
}

template<typename T>
epiString epiWXSlider<T>::GetMinValueText() const
{
    return fmt::format("{}", m_MinValue);
}

template<typename T>
epiString epiWXSlider<T>::GetMaxValueText() const
{
    return fmt::format("{}", m_MaxValue);
}

template<typename T>
wxSize epiWXSlider<T>::GetSizeSliderControl() const
{
    return wxSize{std::max(500, m_Thumb.GetSize().x), std::max(26, m_Thumb.GetSize().y)};
}

template<typename T>
void epiWXSlider<T>::GetSizeLabelMinMaxValue(wxSize& minLabelSize, wxSize& maxLabelSize)
{
    wxClientDC dc(this);

    minLabelSize = dc.GetTextExtent(GetMinValueText());
    maxLabelSize = dc.GetTextExtent(GetMaxValueText());
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
