#pragma once

#include <wx/panel.h>
#include <wx/spinctrl.h>
#include <wx/slider.h>

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/ObjectModel/epiPropertyGrouping.h"

wxDECLARE_EVENT(OBJECT_CONFIGURATION_DIALOG_OBJECT_UPDATED, wxCommandEvent);

class epiWXObjectConfigurationPanel : public wxPanel
{
public:
    epiWXObjectConfigurationPanel(epi::Object& object, // TODO: ensure lifetime
                                  const epi::epiPropertyGrouping& grouping,
                                  wxWindow* parent,
                                  wxWindowID id = wxID_ANY,
                                  const wxPoint& pos = wxDefaultPosition,
                                  const wxSize& size = wxDefaultSize,
                                  long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                                  const wxString& name = wxASCII_STR(wxPanelNameStr));

    void OnSpinValueChanged(wxSpinEvent& event);
    void OnSpinTextValueChanged(wxCommandEvent& event);
    void OnSpinDoubleValueChanged(wxSpinDoubleEvent& event);
    void OnSliderValueChanged(wxCommandEvent& event);
    void OnSliderRangeValueChanged(wxCommandEvent& event);

protected:
    void OnSpinValueChanged_Internal(const wxSpinCtrl& spin);

protected:
    epi::Object& m_Object;
    std::vector<epi::PropertyPointer*> m_PrtyPointers;
};
