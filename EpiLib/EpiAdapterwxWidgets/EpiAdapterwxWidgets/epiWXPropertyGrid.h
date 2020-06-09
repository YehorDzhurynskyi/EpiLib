#pragma once

#include <wx/propgrid/propgrid.h>
#include <EpiCore/ObjectModel/Object.h>

class epiWXPropertyGrid : public wxPropertyGrid
{
public:
    wxDECLARE_EVENT_TABLE();

public:
    epiWXPropertyGrid(wxWindow* parent,
                      wxWindowID id = wxID_ANY,
                      const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxDefaultSize,
                      long style = wxPG_DEFAULT_STYLE,
                      const wxString& name = wxPropertyGridNameStr);

    void SetObject(epi::Object& object);

protected:
    void FillCompound(epi::Object& object, wxPGProperty* prty);
    void FillMultiDimensional(epi::epiBaseArray& array, epi::MetaTypeID nestedTypeID, wxPGProperty* prty);
    void FillFundamental(epi::PropertyPointer& ptr, const epiChar* label, wxPGProperty* prty);
    void FillString(epi::PropertyPointer& ptr, const epiChar* label, wxPGProperty* prty);
    void FillProperties(epi::Object& object, const epi::MetaClassData& meta, wxPGProperty* prty);

    void OnPropertyGridChanged(wxPropertyGridEvent& event);
};
