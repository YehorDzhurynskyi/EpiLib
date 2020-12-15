#pragma once

#include "EpiwxWidgets/epiWXSlider.h"

#include <wx/window.h>
#include <wx/panel.h>
#include <wx/colour.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>

template<typename T>
class epiWXSliderRange : public epiWXSlider<T>
{
public:
    using super = epiWXSlider<T>;

public:
    epiWXSliderRange(wxWindow* parent,
                     wxWindowID id,
                     T lowerValue,
                     T upperValue,
                     T minValue,
                     T maxValue,
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize,
                     epiS32 style = wxSL_HORIZONTAL,
                     const wxString& name = wxASCII_STR("epiWXSliderRange"));

public:
    T GetValueLower() const;
    void SetValueLower(T value);
    T GetValueUpper() const;
    void SetValueUpper(T value);

protected:
    epiWXSliderThumb<T> m_ThumbSecondary;
};

template<typename T>
epiWXSliderRange<T>::epiWXSliderRange(wxWindow* parent,
                                      wxWindowID id,
                                      T lowerValue,
                                      T upperValue,
                                      T minValue,
                                      T maxValue,
                                      const wxPoint& pos,
                                      const wxSize& size,
                                      epiS32 style,
                                      const wxString& name)
    : super{parent, id, lowerValue, minValue, maxValue, pos, size, style, name}
    , m_ThumbSecondary{this, std::clamp(upperValue, minValue, maxValue)}
{
    if (lowerValue > upperValue)
    {
        epiLogError("lower value=`{}` should be less or equal to upper value=`{}`!", lowerValue, upperValue);
        return;
    }
}

template<typename T>
T epiWXSliderRange<T>::GetValueLower() const
{
    return m_ThumbPrimary.GetValue();
}

template<typename T>
void epiWXSliderRange<T>::SetValueLower(T value)
{
    m_ThumbPrimary.SetValue(value);
}

template<typename T>
T epiWXSliderRange<T>::GetValueUpper() const
{
    return m_ThumbSecondary.GetValue();
}

template<typename T>
void epiWXSliderRange<T>::SetValueUpper(T value)
{
    m_ThumbSecondary.SetValue(value);
}
