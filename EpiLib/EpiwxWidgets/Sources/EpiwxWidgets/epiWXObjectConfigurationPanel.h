#pragma once

#include <wx/panel.h>
#include <wx/spinctrl.h>
#include <wx/slider.h>

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/ObjectModel/Property/epiIPropertyChangedHandler.h"

class epiWXObjectConfigurationPanel : public wxPanel
{
public:
    epiWXObjectConfigurationPanel(epi::Object& object, // TODO: ensure lifetime
                                  wxWindow* parent,
                                  wxWindowID id = wxID_ANY,
                                  const wxPoint& pos = wxDefaultPosition,
                                  const wxSize& size = wxDefaultSize,
                                  long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                                  const wxString& name = wxASCII_STR(wxPanelNameStr));

protected:
    wxWindow* MakeControlFromProperty(const epi::MetaProperty& prty);

    template<typename T>
    wxWindow* MakeControlSlider(const epi::MetaProperty& prty,
                                T min = std::numeric_limits<T>::min(),
                                T max = std::numeric_limits<T>::max());

    template<typename T>
    wxWindow* MakeControlSliderRange(const epi::MetaProperty& prty,
                                     T min = std::numeric_limits<T>::min(),
                                     T max = std::numeric_limits<T>::max());

    void OnSliderRangeValueChanged(wxCommandEvent& event);
    void OnCheckboxValueChanged(wxCommandEvent& event);

protected:
    epi::Object& m_Object;
};

template<typename T>
wxWindow* epiWXObjectConfigurationPanel::MakeControlSlider(const epi::MetaProperty& prty,
                                                           T min,
                                                           T max)
{
    epi::epiPropertyPointer ptr = epi::epiPropertyPointer::CreateFromProperty(m_Object, &prty);
    epiWXSlider<T>* slider = new epiWXSlider<T>(this, wxID_ANY, std::move(ptr), min, max);

    // TODO: check whether interface is supported
    epi::epiIPropertyChangedHandler& propertyChangedHandler = dynamic_cast<epi::epiIPropertyChangedHandler&>(m_Object);

    propertyChangedHandler.PropertyChangedRegister(prty.GetPID(), [slider]()
    {
        slider->RefreshValue();
    });

    return slider;
}

template<typename T>
wxWindow* epiWXObjectConfigurationPanel::MakeControlSliderRange(const epi::MetaProperty& prty,
                                                                T min,
                                                                T max)
{
    epi::epiPropertyPointer ptr = epi::epiPropertyPointer::CreateFromProperty(m_Object, &prty);
    epiWXSliderRange<T>* slider = new epiWXSliderRange<T>(this, wxID_ANY, std::move(ptr), min, max);

    // TODO: check whether interface is supported
    epi::epiIPropertyChangedHandler& propertyChangedHandler = dynamic_cast<epi::epiIPropertyChangedHandler&>(m_Object);

    propertyChangedHandler.PropertyChangedRegister(prty.GetPID(), [this, slider]()
    {
        if (epi::epiPropertyPointer* ptr = static_cast<epi::epiPropertyPointer*>(slider->GetClientData()))
        {
            const epiVec2<T>& value = ptr->Get<epiVec2<T>>();
            slider->SetValueLower(value.x);
            slider->SetValueUpper(value.y);
            slider->Refresh();
        }
    });

    return slider;
}
