#pragma once

#include <wx/panel.h>
#include <wx/spinctrl.h>
#include <wx/slider.h>

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/ObjectModel/epiIPropertyChangedHandler.h"

wxDECLARE_EVENT(OBJECT_CONFIGURATION_DIALOG_OBJECT_UPDATED, wxCommandEvent);

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
    wxWindow* MakeControlFromProperty(const epi::MetaProperty& prty, epi::epiIPropertyChangedHandler& propertyChangedHandler);

    template<typename T>
    wxWindow* MakeControlSlider(epi::epiIPropertyChangedHandler& propertyChangedHandler,
                                epi::epiMetaPropertyID prtyID,
                                T min = std::numeric_limits<T>::min(),
                                T max = std::numeric_limits<T>::max());

    template<typename T, typename Inner>
    wxWindow* MakeControlSliderRange(epi::epiIPropertyChangedHandler& propertyChangedHandler,
                                     epi::epiMetaPropertyID prtyID,
                                     Inner min = std::numeric_limits<Inner>::min(),
                                     Inner max = std::numeric_limits<Inner>::max());

    void OnSliderRangeValueChanged(wxCommandEvent& event);
    void OnCheckboxValueChanged(wxCommandEvent& event);

protected:
    epi::Object& m_Object;
    std::vector<std::unique_ptr<epi::PropertyPointer>> m_PrtyPointers;
};

template<typename T>
wxWindow* epiWXObjectConfigurationPanel::MakeControlSlider(epi::epiIPropertyChangedHandler& propertyChangedHandler,
                                                           epi::epiMetaPropertyID prtyID,
                                                           T min,
                                                           T max)
{
    epiWXSlider<T>* slider = new epiWXSlider<T>(this, wxID_ANY, 0, min, max);

    //void (epi::PropertyPointer::*ptrSetter)(T) = &epi::PropertyPointer::Set<T>;
    //T (epi::PropertyPointer::*ptrGetter)() const = &epi::PropertyPointer::Get<T>;

    // TODO: figure out whether it should be unbonded
    slider->Bind(wxEVT_SLIDER, [slider](wxCommandEvent& event)
    {
        if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(slider->GetClientData()))
        {
            ptr->Set<T>(slider->GetValuePrimary());
        }
    });

    propertyChangedHandler.PropertyChangedRegister(prtyID, [this, slider]()
    {
        if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(slider->GetClientData()))
        {
            slider->SetValuePrimary(ptr->Get<T>());
            slider->Refresh();

            QueueEvent(new wxCommandEvent(OBJECT_CONFIGURATION_DIALOG_OBJECT_UPDATED));
        }
    });

    return slider;
}

template<typename T, typename Inner>
wxWindow* epiWXObjectConfigurationPanel::MakeControlSliderRange(epi::epiIPropertyChangedHandler& propertyChangedHandler,
                                                                epi::epiMetaPropertyID prtyID,
                                                                Inner min,
                                                                Inner max)
{
    epiWXSliderRange<Inner>* slider = new epiWXSliderRange<Inner>(this, wxID_ANY, 0, 0, min, max);
    slider->Bind(wxEVT_SLIDER, &epiWXObjectConfigurationPanel::OnSliderRangeValueChanged, this); // TODO: figure out whether it should be unbonded
    propertyChangedHandler.PropertyChangedRegister(prtyID, [this, slider]()
    {
        if (epi::PropertyPointer* ptr = static_cast<epi::PropertyPointer*>(slider->GetClientData()))
        {
            const T value = ptr->Get<T>();
            slider->SetValueLower(value.x);
            slider->SetValueUpper(value.y);
            slider->Refresh();

            QueueEvent(new wxCommandEvent(OBJECT_CONFIGURATION_DIALOG_OBJECT_UPDATED));
        }
    });

    return slider;
}
