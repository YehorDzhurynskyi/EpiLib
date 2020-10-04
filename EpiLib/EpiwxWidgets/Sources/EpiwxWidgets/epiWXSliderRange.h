#pragma once

#include <wx/window.h>
#include <wx/panel.h>
#include <wx/colour.h>
#include <wx/slider.h>

class epiWXSliderRange;
class epiWXSliderRangeThumb
{
protected:
    static const wxColour kIdleColor;
    static const wxColour kIdleShadowColor;
    static const wxColour kDraggedColor;
    static const wxColour kDraggedShadowColor;
    static const wxColour kMouseOverColor;
    static const wxColour kMouseOverShadowColor;

public:
    epiWXSliderRangeThumb(epiWXSliderRange* parent, epiS32 value);

    wxPoint GetPosition() const;
    void SetPosition(const wxPoint& position);

    epiBool IsMouseOver(const wxPoint& mousePosition) const;

    epiBool GetDragged() const;
    void SetDragged(epiBool value);
    epiBool GetMouseOver() const;
    void SetMouseOver(epiBool value);

    void SetValue(epiS32 value);
    epiS32 GetValue() const;

    void OnPaint(wxDC& dc);

protected:
    wxSize GetSize() const;

    epiS32 GetMin() const;
    epiS32 GetMax() const;

    epiWXSliderRangeThumb& GetOtherThumb();
    epiBool IsThumbLower() const;
    epiBool IsThumbUpper() const;

protected:
    epiWXSliderRange* m_Parent{nullptr};

    wxSize m_Size{};

    epiS32 m_Value{};
    epiBool m_Dragged{false};
    epiBool m_MouseOver{false};

    wxPointList m_ThumbPointList;
    wxPointList m_ThumbShadowPointList;
};

class epiWXSliderRange : public wxPanel
{
public:
    using super = wxPanel;

protected:
    static const wxColour kRangeBackgroundColor;
    static const wxColour kRangeOutlineColor;
    static const wxColour kSelectedRangeColor;
    static const wxColour kSelectedRangeOutlineColor;

public:
    epiWXSliderRange(wxWindow* parent,
                     wxWindowID id,
                     epiS32 lowerValue,
                     epiS32 upperValue,
                     epiS32 minValue,
                     epiS32 maxValue,
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize,
                     epiS32 style = wxSL_HORIZONTAL,
                     const wxString& name = wxASCII_STR("epiWXSliderRange"));

public:
    epiU32 GetBorderWidth() const;
    void SetBorderWidth(epiU32 width);

    epiS32 GetValueLower() const;
    epiS32 GetValueUpper() const;

    epiS32 GetMin() const;
    epiS32 GetMax() const;

    epiWXSliderRangeThumb& GetThumbLower();
    epiWXSliderRangeThumb& GetThumbUpper();
    const epiWXSliderRangeThumb& GetThumbLower() const;
    const epiWXSliderRangeThumb& GetThumbUpper() const;

protected:
    void SetValueFromMousePosition(const wxPoint& mousePosition);

    void DoEnable(epiBool enable = true);
    void DoDisable();

    void OnMouseDown(wxMouseEvent& event);
    void OnMouseUp(wxMouseEvent& event);
    void OnMouseMotion(wxMouseEvent& event);
    void OnMouseLost(wxMouseCaptureLostEvent& event);
    void OnMouseEnter(wxMouseEvent& event);
    void OnMouseLeave(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    void OnResize(wxSizeEvent& event);

protected:
    epiU32 m_BorderWidth{};

    epiS32 m_ValueMin{};
    epiS32 m_ValueMax{};

    epiWXSliderRangeThumb m_ThumbLower;
    epiWXSliderRangeThumb m_ThumbUpper;
};
