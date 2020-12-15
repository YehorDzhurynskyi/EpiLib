#pragma once

#include "EpiwxWidgets/epiWXSliderBase.h"

#include <wx/colour.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>

template<typename T>
class epiWXSliderThumb
{
public:
    epiWXSliderThumb(epiWXSliderBase* parent, T value);

    wxPoint GetPosition() const;
    void SetPosition(const wxPoint& position);

    epiBool IsMouseOver(const wxPoint& mousePosition) const;

    epiBool GetDragged() const;
    void SetDragged(epiBool value);
    epiBool GetMouseOver() const;
    void SetMouseOver(epiBool value);

    void SetValue(T value);
    T GetValue() const;

    void OnPaint(wxDC& dc);

protected:
    T Fraction2Value(epiFloat fraction, T minValue, T maxValue) const;
    epiFloat Value2Fraction(T value, T minValue, T maxValue) const;

    epiS32 GetMinPosition() const;
    epiS32 GetMaxPosition() const;

    wxSize GetSize() const;

protected:
    epiWXSliderBase* m_Parent{nullptr};

    wxSize m_Size{};

    T m_Value{};
    epiBool m_Dragged{false};
    epiBool m_MouseOver{false};

    wxPointList m_ThumbPointList;
    wxPointList m_ThumbShadowPointList;
};

namespace
{

const wxColour kIdleColor = wxColour(0, 120, 215);
const wxColour kIdleShadowColor = wxColour(120, 180, 228);
const wxColour kDraggedColor = wxColour(204, 204, 204);
const wxColour kDraggedShadowColor = wxColour(222, 222, 222);
const wxColour kMouseOverColor = wxColour(23, 23, 23);
const wxColour kMouseOverShadowColor = wxColour(132, 132, 132);

}

template<typename T>
epiWXSliderThumb<T>::epiWXSliderThumb(epiWXSliderBase* parent, T value)
    : m_Parent{parent}
    , m_Value{value}
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

template<typename T>
wxPoint epiWXSliderThumb<T>::GetPosition() const
{
    const wxSize parentSize = m_Parent->GetSize();

    const T minValue = std::any_cast<T>(m_Parent->GetMinValueAny());
    const T maxValue = std::any_cast<T>(m_Parent->GetMaxValueAny());

    const epiFloat fraction = Value2Fraction(m_Value, minValue, maxValue);
    return wxPoint{Fraction2Value(fraction, GetMinPosition(), GetMaxPosition()), parentSize.y / 2 + 1};
}

template<typename T>
void epiWXSliderThumb<T>::SetPosition(const wxPoint& position)
{
    epiS32 positionX = position.x;

#if 0
    epiWXSliderThumb<T>& other = GetOtherThumb();
    wxPoint otherPosition = other.GetPosition();

    if (other.IsThumbLower())
    {
        positionX = std::max(otherPosition.x + other.GetSize().x / 2 + GetSize().x / 2, positionX);
    }
    else
    {
        positionX = std::min(otherPosition.x - other.GetSize().x / 2 - GetSize().x / 2, positionX);
    }
#endif

    const T minValue = std::any_cast<T>(m_Parent->GetMinValueAny());
    const T maxValue = std::any_cast<T>(m_Parent->GetMaxValueAny());

    positionX = std::clamp(positionX, GetMinPosition(), GetMaxPosition());
    const epiFloat fraction = Value2Fraction(positionX, GetMinPosition(), GetMaxPosition());
    SetValue(Fraction2Value(fraction, minValue, maxValue));
}

template<typename T>
void epiWXSliderThumb<T>::SetValue(T value)
{
    m_Value = value;

    wxCommandEvent event(wxEVT_SLIDER, m_Parent->GetId());
    event.SetEventObject(m_Parent);

    wxPostEvent(m_Parent->GetEventHandler(), event);
}

template<typename T>
T epiWXSliderThumb<T>::GetValue() const
{
    return m_Value;
}

template<typename T>
epiBool epiWXSliderThumb<T>::IsMouseOver(const wxPoint& mousePosition) const
{
    const wxPoint position = GetPosition();

    return
        mousePosition.x >= position.x - GetSize().x / 2 &&
        mousePosition.x <= position.x + GetSize().x / 2 &&
        mousePosition.y >= position.y - GetSize().y / 2 &&
        mousePosition.y <= position.y + GetSize().y / 2;
}

template<typename T>
epiBool epiWXSliderThumb<T>::GetDragged() const
{
    return m_Dragged;
}

template<typename T>
void epiWXSliderThumb<T>::SetDragged(epiBool value)
{
    m_Dragged = value;
}

template<typename T>
epiBool epiWXSliderThumb<T>::GetMouseOver() const
{
    return m_MouseOver;
}

template<typename T>
void epiWXSliderThumb<T>::SetMouseOver(epiBool value)
{
    m_MouseOver = value;
}

template<typename T>
void epiWXSliderThumb<T>::OnPaint(wxDC& dc)
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

    wxPoint kThumbShadowPoly[]{wxPoint{0, 14}, wxPoint{4, 18}, wxPoint{6, 18}, wxPoint{10, 14}};
    wxPointList kThumbShadowPolyList;
    for (epiU32 i = 0; i < epiArrLen(kThumbShadowPoly); ++i)
    {
        kThumbShadowPolyList.Append(&kThumbShadowPoly[i]);
    }
    dc.DrawPolygon(&kThumbShadowPolyList, position.x - GetSize().x / 2, position.y - GetSize().y / 2);

    dc.SetBrush(wxBrush(colorThumb, wxBRUSHSTYLE_SOLID));
    dc.SetPen(wxPen(colorThumb, 1, wxPENSTYLE_SOLID));

    wxPoint kThumbPoly[]{wxPoint{0, 0}, wxPoint{0, 13}, wxPoint{5, 18}, wxPoint{10, 13}, wxPoint{10, 0}};
    wxPointList kThumbPolyList;
    for (epiU32 i = 0; i < epiArrLen(kThumbPoly); ++i)
    {
        kThumbPolyList.Append(&kThumbPoly[i]);
    }
    dc.DrawPolygon(&kThumbPolyList, position.x - GetSize().x / 2, position.y - GetSize().y / 2);
}

template<typename T>
T epiWXSliderThumb<T>::Fraction2Value(epiFloat fraction, T minValue, T maxValue) const
{
    return (maxValue - minValue) * fraction + minValue;
}

template<typename T>
epiFloat epiWXSliderThumb<T>::Value2Fraction(T value, T minValue, T maxValue) const
{
    return epiFloat(value - minValue) / (maxValue - minValue);
}

template<typename T>
wxSize epiWXSliderThumb<T>::GetSize() const
{
    return m_Size;
}

template<typename T>
epiS32 epiWXSliderThumb<T>::GetMinPosition() const
{
    return m_Parent->GetBorderWidth() + GetSize().x / 2;
}

template<typename T>
epiS32 epiWXSliderThumb<T>::GetMaxPosition() const
{
    return m_Parent->GetSize().x - m_Parent->GetBorderWidth() - GetSize().x / 2;
}
