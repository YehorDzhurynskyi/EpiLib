#pragma once

#include <wx/window.h>
#include <wx/panel.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>
#include <wx/slider.h>

#include <any>

class epiWXSliderBase : public wxPanel
{
public:
    using super = wxPanel;

protected:
    static const wxColour kRangeBackgroundColor;
    static const wxColour kRangeOutlineColor;
    static const wxColour kSelectedRangeColor;
    static const wxColour kSelectedRangeOutlineColor;

public:
    epiWXSliderBase(wxWindow* parent,
                    wxWindowID id,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    epiS32 style = wxSL_HORIZONTAL,
                    const wxString& name = wxASCII_STR("epiWXSliderBase"));

public:
    virtual void RefreshValue() = 0;

    epiU32 GetBorderWidth() const;
    void SetBorderWidth(epiU32 width);
    epiU32 GetMinMaxLabelPadding() const;
    void SetMinMaxLabelPadding(epiU32 padding);

    virtual std::any GetMinValueAny() const = 0;
    virtual std::any GetMaxValueAny() const = 0;

    virtual wxSize GetSizeSliderControl() const = 0;
    virtual void GetSizeLabelMinMaxValue(wxSize& minLabelSize, wxSize& maxLabelSize) = 0;
    virtual wxSize GetSizeBBox() = 0;

protected:
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

    virtual void OnMouseDown_Internal(wxMouseEvent& event) = 0;
    virtual void OnMouseUp_Internal(wxMouseEvent& event) = 0;
    virtual void OnMouseMotion_Internal(wxMouseEvent& event) = 0;
    virtual void OnMouseLost_Internal(wxMouseCaptureLostEvent& event) = 0;
    virtual void OnMouseEnter_Internal(wxMouseEvent& event) = 0;
    virtual void OnMouseLeave_Internal(wxMouseEvent& event) = 0;
    virtual void OnPaint_Internal(wxPaintEvent& event) = 0;

protected:
    epiU32 m_BorderWidth{};
    epiU32 m_MinMaxLabelPadding{};
};
