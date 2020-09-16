#pragma once

#include <wx/propgrid/propgrid.h>

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/ObjectModel/PropertyPointer.h"

class epiWXPlot;
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
    void Clear() override;

protected:
    void FillCompound(epi::Object& object, wxPGProperty* parentPrty);
    void FillMultiDimensional(epi::epiBaseArray& array, epi::epiMetaTypeID nestedTypeID, wxPGProperty* parentPrty);
    void FillMultiDimensionalPtr(epi::epiBaseArray& array, epi::epiMetaTypeID nestedTypeID, wxPGProperty* parentPrty);
    void FillProperties(epi::Object& object, const epi::MetaClassData& meta, wxPGProperty* parentPrty);

    void AddFundamental(epi::PropertyPointer& ptr, const epiChar* label, wxPGProperty* parentPrty, epiBool editable);
    void AddString(epi::PropertyPointer& ptr, const epiChar* label, wxPGProperty* parentPrty, epiBool editable);
    void AddProperty(epi::PropertyPointer& ptr, wxPGProperty* prty, wxPGProperty* parentPrty, epiBool editable);

    void OnPropertyGridChanged(wxPropertyGridEvent& event);
    void OnPropertyGridRightClick(wxPropertyGridEvent& event);

protected:
    std::vector<epi::PropertyPointer*> m_PropertyPointers;
};
