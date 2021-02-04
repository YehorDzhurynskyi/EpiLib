#pragma once

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/ObjectModel/Property/epiIPropertyChangedHandler.h"

#include "EpiUI/ViewModel/uiVMPropertyBase.h"

#include <wx/panel.h>
#include <wx/spinctrl.h>
#include <wx/slider.h>

class epiWXObjectConfigurationPanel : public wxPanel
{
public:
    epiWXObjectConfigurationPanel(epi::epiIPropertyChangedHandler& dataContext,
                                  epi::epiArray<std::unique_ptr<epi::uiVMPropertyBase>>&& vmList,
                                  wxWindow* parent,
                                  wxWindowID id = wxID_ANY,
                                  const wxPoint& pos = wxDefaultPosition,
                                  const wxSize& size = wxDefaultSize,
                                  long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                                  const wxString& name = wxASCII_STR(wxPanelNameStr));

protected:
    wxWindow* MakeControlFromPropertyVM(epi::uiVMPropertyBase& vm);

    void OnCheckboxValueChanged(wxCommandEvent& event);

protected:
    epi::epiIPropertyChangedHandler& m_DataContext;
    epi::epiArray<std::unique_ptr<epi::uiVMPropertyBase>> m_VMList;
};

#if 0
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
#endif
